/*
 * @Author:	Jeff Berube
 * @Title:	memalloc.h
 *
 * @Description:	Simulates memory allocation inside a kernel.
 *
 */

#include <stdio.h>

#include "nodes.h"

/* Simulation parameters */
#define MIN_LEASE 	40
#define MAX_LEASE 	70
#define MIN_SIZE	50
#define MAX_SIZE	350
#define TIME_LIMIT	1000
#define MEMORY_SIZE	1000
#define REQUEST_INTERVAL	20

void request_memory(int);
void clean_expired_leases(int);
