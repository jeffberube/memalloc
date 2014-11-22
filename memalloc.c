/*
 * @Author:		Jeff Berube
 * @Title:		memalloc.c
 *
 * @Description:	Memory allocation and freeing functions.	
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

	int size = (rand() % (MAX_SIZE - MIN_SIZE)) + MIN_SIZE;
	int lease = (rand() % (MAX_LEASE - MIN_LEASE)) + MIN_LEASE;

	int success = request_memory(size, lease + current_time, scheme);

	update_request_stats(size, lease, success);		

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

		allocNode *node = create_alloc_node(block->hole.start, size, lease);
		insert_alloc_node_in_list(node);

		block->hole.start += size;
		block->hole.length -= size;

	}

	/* Returns 1 if request was fulfilled, 0 otherwise */

	return block ? 1 : 0;

}

void release_memory(allocNode *node) {

	freeNode *block = create_free_node(node->allocated.start, 
										node->allocated.length);
	insert_free_node_in_list(block);

	remove_alloc_node_from_list(node);
	
	destroy_alloc_node(node);

}

freeNode *find_free_node(int size, allocScheme scheme) {

	freeNode *p = freeList;
	freeNode *block = NULL;

	if (scheme == FIRST_FIT) {
		
		while (p->next && p->next->hole.length < size) p = p->next;

		block = p->next;

	} else {

		/* Iterate through whole list */	
		while (p->next) {
		
			if (p->next->hole.length >= size) {
			
				if (!block) 
					block = p->next;
				
				else if ((scheme == BEST_FIT && p->next->hole.length < block->hole.length)
						|| (scheme == WORST_FIT && p->next->hole.length > block->hole.length))
					block = p->next;

			}

			p = p->next;

		}

	} 

	return block;

}

void merge_free_list() {

	freeNode *p = freeList;

	while (p->next && p->next->next) {
	
		/* If two holes are adjacent */
		if (p->next->next->hole.start == p->next->hole.start + p->next->hole.length) {
			
			/* Merge the holes then restart from start of list */
			merge_free_nodes(p->next, p->next->next);
			p = freeList;

		} else p = p->next;

	}

}

void sort_alloc_list_on_start() {

	allocNode *p = allocList;
	allocNode *q = allocList;
	allocNode *tmp, *tmp_prev;

	/* If there's more than one element in the alloc list, sort */
	if (p->next && p->next->next) {

		while (q->next) {
			
			p = q->next;
			tmp = p;
			tmp_prev = q;

			while (p->next) {
				
				if (p->next->allocated.start < tmp->allocated.start) {
					tmp = p->next;
					tmp_prev = p;
				}
				p = p->next;

			}

			tmp_prev->next = tmp->next;
			tmp->next = q->next;
			q->next = tmp;

			q = q->next;

		}

	}

}

void clean_expired_leases(int current_time) {

	allocNode *p = allocList->next;

	if (p && p->leaseExpiry <= current_time) {

		while (p && p->leaseExpiry <= current_time) {

			allocNode *tmp = p;
			p = p->next;

			release_memory(tmp);
		
		}

		allocList->next = p;

	}

}
