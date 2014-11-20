/*
 * @Author:		Jeff Berube
 * @Title:		stats.h
 *
 * @Description: Statistic function prototypes and variables
 *
 */

#ifndef __stats_h__
#define __stats_h__

#include <stdio.h>
#include "memalloc.h"

typedef struct {

	int totalRequests;
	int successfulRequests;
	
	int totalBlocks;
	int smallestBlock;
	int largestBlock;

	int totalLeases;
	int shortestLease;
	int longestLease;

	int totalMerges;

} statsTable;

statsTable stats;

void init_stats_table();
void update_request_stats(int size, int lease, int success);
void dump_stats();

#endif
