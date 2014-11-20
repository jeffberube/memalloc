/*
 * @Author:	Jeff Berube
 * @Title:	memalloc.c
 *
 * @Description:	Simulates memory allocation inside a kernel.
 *
 */

#include <stdlib.h>
#include <time.h>

#include "memalloc.h"

void init_memory_arena() {

	init_free_list();
	init_alloc_list();	

}

void generate_memory_request(int current_time, allocScheme scheme) {

	/* Seed random number generator */
	srand(time(NULL));

	int size = (rand() % (MAX_SIZE - MIN_SIZE)) + MIN_SIZE;
	int lease = (rand() % (MAX_LEASE - MIN_LEASE)) + MIN_LEASE;

	request_memory(size, lease, scheme);

}

int request_memory(int size, int lease, allocScheme scheme) {

	/* Try to find a block to accomodate the request */
	freeNode *block = find_free_node(size, scheme);

	/* If no block found, merge adjacent nodes in free list and try again */
	if (!block) {
	
		merge_free_list();
		block = find_free_node(size, scheme);

	}

	/* If block found, split and create new node */
	if (block) {

			allocNode *node = create_new_alloc_node(block->hole->start, size, lease);
			insert_alloc_node_in_list(node);

			block->hole->start += size;
	
	}

	/* Returns 1 if request was fulfilled, 0 otherwise */
	return block ? 1 : 0;

}

void release_memory(allocNode *node) {



}

freeNode *find_free_node(int size, allocScheme scheme) {

	freeNode *p = freeList;
	freeNode *block = NULL;

	if (scheme == FIRST_FIT) {
		
		while (p->next && p->next->hole->length < size) p = p->next;

		block = p->next;

	} else {

		/* Iterate through whole list */	
		while (p->next) {
		
			if (p->next->hole->length >= size) {
			
				if (!block) 
					block = p->next;
				
				else if ((scheme == BEST_FIT && p->next->hole->length < block->hole->length)
						|| (scheme == WORST_FIT && p->next->hole->length > block->hole->length))
					block = p->next;

			}

			p = p->next;

		}

	} 
	
	return block;

}

void clean_expired_leases(int current_time) {


}
