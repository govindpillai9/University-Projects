#include "bubble.h"
#include "misc.h"
#include "quick.h"
#include "set.h"
#include "shell.h"

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define OPTIONS "absqQr:n:p:"
//enumerator gives number values to these elements
typedef enum Sort { BUBBLE, SHELL, QUICKS, QUICKQ } Sort;
int moves;
int comps;
uint32_t max_stack_size;
uint32_t max_queue_size;
int main(int argc, char **argv) {
    //setting default values
    int opt = 0;
    int seed = 13371453;
    int size = 100;
    int elements = 100;
    Set sorts = set_empty();
    //creating a function table
    void (*sort_funcs[4])(uint32_t *, uint32_t)
        = { bubble_sort, shell_sort, quick_sort_stack, quick_sort_queue };
    //option switch statement
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'a':
            sorts = set_insert(sorts, BUBBLE);
            sorts = set_insert(sorts, SHELL);
            sorts = set_insert(sorts, QUICKS);
            sorts = set_insert(sorts, QUICKQ);
            break;
        case 'b': sorts = set_insert(sorts, BUBBLE); break;
        case 's': sorts = set_insert(sorts, SHELL); break;
        case 'q': sorts = set_insert(sorts, QUICKS); break;
        case 'Q': sorts = set_insert(sorts, QUICKQ); break;
        case 'r': seed = (int) atoi(optarg); break;
        case 'n': size = (int) atoi(optarg); break;
        case 'p': elements = (int) atoi(optarg); break;
        default: printf("invalid input\n"); break;
        }
    }
    srandom(seed);
    uint32_t arr[size];
    uint32_t copy[size];
    uint32_t *b;
    b = arr;
    //generates random array and keeps a copy
    for (int i = 0; i < size; i++) {
        arr[i] = (uint32_t) random();
        copy[i] = arr[i];
    }
    //if proposed number of elements to print is bigger than size
    //set elements to size
    if (elements > size) {
        elements = size;
    }
    //checks if each sort has been called on and prints appropriately
    for (Sort i = BUBBLE; i <= QUICKQ; i++) {
        if (set_member(sorts, i)) {
            if (i == BUBBLE) {
                printf("Bubble Sort\n");
            } else if (i == SHELL) {
                printf("Shell Sort\n");
            } else if (i == QUICKS) {
                printf("Quick Sort (Stack)\n");
            } else if (i == QUICKQ) {
                printf("Quick Sort (Queue)\n");
            }
            sort_funcs[i](b, size);
            printf("%d elements, %d moves, %d compares", size, moves, comps);
            if (i == QUICKS) {
                printf("\nMax stack size: %d", max_stack_size);
            } else if (i == QUICKQ) {
                printf("\nMax queue size: %d", max_queue_size);
            }
            for (int x = 0; x < elements; x++) {
                if (x % 5 == 0) {
                    printf("\n");
                }
                printf("%13" PRIu32, arr[x]);
            }
            printf("\n");
            for (int f = 0; f < size; f++) {
                arr[f] = copy[f];
            }
        }
    }
    return 0;
}
