/*
 * @Author:	Jeff Berube
 * @Title:	nodes.h
 * 
 * @Description: 	Contains structure definitions for memory nodes and related
 *			functions.
 *
 */

#ifndef __nodes_h__
#define __nodes_h__

#include <stdio.h>
#include <unistd.h>

typedef struct freeNode freeNode;
typedef struct allocNode allocNode;
typedef	struct range range;

struct freeNode {
	range hole;
	freeNode *next;
};

struct allocNode {
	range allocated;
	allocNode *next;
	int leaseExpiry;
};

struct range {
	int start;
	int length;
};

freeNode *freeList;
allocNode *allocList;

void init_free_list();
void init_alloc_list();

/* Free list nodes manipulation function prototypes */
freeNode *create_free_node(int start, int length);
void destroy_free_node(freeNode *node);
void insert_free_node_in_list(freeNode *node);
void remove_free_node_from_list(freeNode *node);
void merge_free_nodes(freeNode *leftNode, freeNode *rightNode);

/* Alloc list nodes manipulation function prototypes */
allocNode *create_alloc_node(int start, int length, int expiry);
void destroy_alloc_node(allocNode *node);
void insert_alloc_node_in_list(allocNode *node);
void remove_alloc_node_from_list(allocNode *node);

#endif
