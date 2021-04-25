#include "set.h"
#include <stdio.h>
#include <unistd.h>
#include "bubble.h"
#include "shell.h"
#include "quick.h"
#include <inttypes.h>
#include "misc.h"
#include <stdlib.h>

#define OPTIONS "absqQr:n:p:"

typedef enum Sort {BUBBLE, SHELL, QUICKS, QUICKQ} Sort;
int moves;
int comps;
int main(int argc, char **argv) {
	int opt = 0;
	int seed = 13371453;
	int size = 100;
	int elements = 100;
	Set sorts = set_empty();
	void (*sort_funcs[4])(uint32_t*, uint32_t) = {bubble_sort, shell_sort, quick_sort_stack, quick_sort_queue};

	while((opt = getopt(argc, argv, OPTIONS)) != -1) {
		switch(opt) {
		case 'a':
			sorts = set_insert(sorts, BUBBLE);
			sorts = set_insert(sorts, SHELL);
			sorts = set_insert(sorts, QUICKS);
			sorts = set_insert(sorts, QUICKQ);
			break;
		case 'b':
			sorts = set_insert(sorts, BUBBLE);
			break;
		case 's':
			sorts = set_insert(sorts, SHELL);
			break;
		case 'q':
			sorts = set_insert(sorts, QUICKS);
			break;
		case 'Q':
			sorts = set_insert(sorts,QUICKQ);
			break;
		case 'r':
			seed =(int) atoi(optarg);
			break;
		case 'n':
			size = (int)atoi(optarg);
			break;
		case 'p':
			elements = (int)atoi(optarg);
			break;
		default:
			printf("invalid input\n");
			break;
		}

	}
	srandom(seed);
	uint32_t arr[size];
	uint32_t *b;
	b = arr;
	for(int i = 0; i < size; i++) {
		arr[i] = (uint32_t)random();
	}
	if(elements > size) {
		elements = size;
	}

	for(Sort i = BUBBLE; i <= QUICKQ; i++) {
		if(set_member(sorts, i)) {
			if(i == BUBBLE) {
				printf("Bubble Sort\n");
			}
			else if(i == SHELL) {
				printf("Shell Sort\n");
			}
			else if(i == QUICKS) {
				printf("Quick Sort (Stack)\n");
			}
			else if(i == QUICKQ) {
				printf("Quick Sort (Queue)\n");
			}
			sort_funcs[i](b, size);
			printf("%d elements, %d moves, %d compares",size,moves,comps);
			for(int x = 0; x < elements; x++) {
				if(x % 5 == 0) {
					printf("\n");
				}
				printf("%13" PRIu32, arr[x]);
			}
			printf("\n");

		}
	}
	return 0;

}


