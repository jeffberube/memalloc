/*
 * @Author:	Jeff Berube
 * @Title:	memalloc.c
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

int main() {

	long clock = 0;

	while (++clock != TIME_LIMIT) {
		
		if (clock % REQUEST_INTERVAL == 0) 
			request_memory(clock);

		check_expired_leases(clock);

	}

	return 0;
}
