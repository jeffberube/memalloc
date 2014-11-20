/*
 * @Author:	Jeff Berube
 * @Title:	main.c
 *
 * @Description:	Simulates memory allocation inside a kernel.
 *
 */

#include <stdio.h>
#include "memalloc.h"

/* Simulation parameters */
#define TIME_LIMIT		1000
#define REQUEST_INTERVAL	20

int main() {

	long long clock = 0;

	while (++clock != TIME_LIMIT) {
	
		if (clock % REQUEST_INTERVAL == 0)
			generate_memory_request(clock);

		clean_expired_leases(clock);
	
	}	

	return 0;
}
