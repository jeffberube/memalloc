/*
 * @Author:	Jeff Berube
 * @Title:	memalloc.h
 *
 * @Description:	Simulates memory allocation inside a kernel.
 *
 */

#include <stdio.h>

#include "nodes.h"

/* Memory space  parameters */
#define MIN_LEASE 	40
#define MAX_LEASE 	70
#define MIN_SIZE	50
#define MAX_SIZE	350
#define MEMORY_SIZE	1000

/* Allocation schemes */
typedef enum {BEST_FIT, WORST_FIT, FIRST_FIT} allocScheme;

/* Prototypes */
void init_memory_arena();
void generate_memory_request(int current_time, allocScheme scheme);
void request_memory(int size, int lease, allocScheme scheme);
void release_memory(allocNode *node);
freeNode *find_free_node(int size, allocScheme scheme);
void clean_expired_leases(int current_time);
