/*
 * @Author:		Jeff Berube
 * @Title:		stats.c
 *
 * @Description: Statistics related function
 *
 */

#include "stats.h"

void init_stats_table() {

	stats.totalRequests = 0;
	stats.successfulRequests = 0;

	stats.totalBlocks = 0;
	stats.smallestBlock = MAX_SIZE;
	stats.largestBlock = MIN_SIZE;

	stats.totalLeases = 0;
	stats.shortestLease = MAX_LEASE;
	stats.longestLease = MIN_LEASE;

	stats.totalMerges = 0;

}

void update_request_stats(int size, int lease, int success) {

	stats.totalRequests++;

	stats.successfulRequests += success;

	stats.totalBlocks += size;
	if (size < stats.smallestBlock) stats.smallestBlock = size;
	if (size > stats.largestBlock) stats.largestBlock = size;

	stats.totalLeases += lease;
	if (lease < stats.shortestLease) stats.shortestLease = lease;
	if (lease > stats.longestLease) stats.longestLease = lease;

}

void dump_stats(int cycles, allocScheme scheme) {

	printf("\nRan: %d CYCLES\n", cycles);

	printf("Memory Allocation Scheme: ");

	switch (scheme) {
	
		case FIRST_FIT: 
			
			printf("FIRST FIT\n");
			
			break;

		case BEST_FIT:	

			printf("BEST FIT\n");
						
			break;

		case WORST_FIT:	
			
			printf("WORST FIT\n");
			
			break;
	
	}

	printf("\nTotal Requests: %d\n", stats.totalRequests);
	printf("Successful: %d\n", stats.successfulRequests);
	printf("Unsuccessful: %d\n\n", stats.totalRequests - stats.successfulRequests);

	printf("\nAverage Block Size: %.1f\n", (float)(stats.totalBlocks / stats.totalRequests));
	printf("Smallest Block: %d\n", stats.smallestBlock);
	printf("Largest Block: %d\n\n", stats.largestBlock);

	printf("Average Lease Duration: %.1f CYCLES\n", 
								(float)(stats.totalLeases / stats.totalRequests));
	printf("Shortest Lease: %d\n", stats.shortestLease);
	printf("Longest Lease: %d\n\n", stats.longestLease);

	printf("Total Merges: %d\n\n", stats.totalMerges);

	merge_free_list();
	sort_alloc_list_on_start();

	freeNode *f = freeList->next;
	allocNode *a = allocList->next;

	while (f || a) {


		if (f && a) {
		
			if (f->hole.start < a->allocated.start) {

				printf("     FREE| \tStart: %3d \tLength: %3d\n", 
						f->hole.start, f->hole.length);
				f = f->next;

			} else {
			
				printf("ALLOCATED| \tStart: %3d \tLength: %3d \tExpiry: %d\n",
						a->allocated.start, a->allocated.length,
						a->leaseExpiry);
				a = a->next;

			}

		} else if (f) {
		
			printf("     FREE| \tStart: %3d \tLength: %3d\n", 
					f->hole.start, f->hole.length);
			f = f->next;

		} else {
		
			printf("ALLOCATED| \tStart: %3d \tLength: %3d \tExpiry: %d\n",
					a->allocated.start, a->allocated.length,
						a->leaseExpiry);
			a = a->next;

		}		
	
	}

	printf("\n");

}
