/*
 * @Author:	Jeff Berube
 * @Title:	memalloc.c
 *
 * @Description:	Simulates memory allocation inside a kernel.
 *
 */

#include <stdio.h>

struct freeNode {
	struct range hole;
	struct freeNode *next;
};

struct allocNode {
	struct range allocated;
	int leaseExpiry;
	struct allocNode *next;

}

int main() {

	

	return 0;
}
