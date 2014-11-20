/*
 * @Author:	Jeff Berube
 * @Title:	nodes.c
 *
 * @Description: Contains all the functions related to node manipulation
 *
 */

#include "nodes.h"

void init_free_list() {

	/* Create sentinel node */
	freeList = create_free_node(0, 0);

	/* Create memory space */
	freeList->next = create_free_node(0, 1000);

}

void init_alloc_list() {

	/* Create sentinel node */
	allocList = create_alloc_node(0, 0, 0);

}

freeNode *create_free_node(int start, int length) {

	freeNode *node = malloc(sizeof(freeNode));
	node->hole.start = start;
	node->hole.length = length;
	node->next = NULL;

	return node;

}

void destroy_free_node(freeNode *node) {

	free(node);

}

void insert_free_node_in_list(freeNode *node) {

	freeNode *p = freeList;
	
	while (p->next && node->hole.start < p->next->hole.start) p = p->next;	
		
	node->next = p->next;
	p->next = node;

}

void remove_free_node_from_list(freeNode *node) {

	freeNode *p = freeList;

	while (p->next && p->next != node) p = p->next;

	if (p && p->next == node) p->next = p->next->next;	

}

void merge_free_nodes(freeNode *leftNode, freeNode *rightNode) {

	int start = leftNode->hole.start;
	int length = leftNode->hole.length + rightNode->hole.length;

	printf("Bug here ...");
	remove_free_node_from_list(leftNode);
	destroy_free_node(leftNode);

	remove_free_node_from_list(rightNode);
	destroy_free_node(rightNode);
	printf(" or here\n");

	freeNode *merged = create_free_node(start, length);
	insert_free_node_in_list(merged);

}

allocNode *create_alloc_node(int start, int length, int expiry) {

	allocNode *node = malloc(sizeof(allocNode));
	node->allocated.start = start;
	node->allocated.length = length;
	node->leaseExpiry = expiry;
	node->next = NULL;

	return node;

}

void destroy_alloc_node(allocNode *node) {

	free(node);

}

void insert_alloc_node_in_list(allocNode *node) {

	allocNode *p = allocList;

	while (p->next && node->leaseExpiry >= p->next->leaseExpiry) p = p->next;

	node->next = p->next;
	p->next = node;

}

void remove_alloc_node_from_list(allocNode *node) {

	allocNode *p = allocList;

	while (p->next && p->next != node) p = p->next;

	if (p && p->next == node) p->next = p->next->next;
	
}
