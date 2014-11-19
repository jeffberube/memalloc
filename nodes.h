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

#endif
