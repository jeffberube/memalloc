/*
 * @Author:	Jeff Berube
 * @Title:	main.c
 *
 * @Description:	Simulates memory allocation inside a kernel.
 *
 */

#include <stdio.h>
#include "memalloc.h"

int main() {

	long long clock = 0;

	while (++clock != TIME_LIMIT) {
	
		if (clock % REQUEST_INTERVAL == 0)
			request_memory(clock);

		clean_expired_leases(clock);
	
	}	

	return 0;
}
