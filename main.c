/*
 * @Author:	Jeff Berube
 * @Title:	main.c
 *
 * @Description:	Simulates memory allocation inside a kernel.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "memalloc.h"

/* Simulation parameters */
#define TIME_LIMIT		1000
#define REQUEST_INTERVAL	20

int main(int argc, char *argv[]) {

	long long clock = 0;
	allocScheme scheme;

	/* Handle command line arguments */
	if (argc < 2) scheme = BEST_FIT;

	else if (!strcmp(argv[1], "BEST_FIT")) scheme = BEST_FIT;
	else if (!strcmp(argv[1], "WORST_FIT")) scheme = WORST_FIT;
	else if (!strcmp(argv[1], "FIRST_FIT")) scheme = FIRST_FIT;
	
	else printf("Invalid argument: %s\nAccepted: BEST_FIT, WORST_FIT, FIRST_FIT\n", 
			argv[1]), exit(0);

	/* Seed random number generator */
	srand(time(NULL));

	/* Setup procedure */
	init_memory_arena();
	init_stats_table();

	while (++clock != TIME_LIMIT) {
	
		if (clock % REQUEST_INTERVAL == 0)
			generate_memory_request(clock, scheme);

		clean_expired_leases(clock);
	
	}	

	dump_stats(TIME_LIMIT, scheme);

	return 0;

}
