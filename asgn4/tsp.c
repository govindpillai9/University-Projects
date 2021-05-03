#include "graph.h"
#include "path.h"
#include "stack.h"
#include "vertices.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define OPTIONS "hvui:o:"
uint32_t calls = 0;
uint32_t *caller = &calls;
bool verbose = false;
bool *verbpoint = &verbose;
bool und = false;
bool *undd = &und;
void dfs(Graph *G, uint32_t v, Path *curr, Path *shortest, char *cities[], FILE *outfile) {
    uint32_t poppers = 0;
    uint32_t *ptr;
    ptr = &poppers;
    bool isHamiltonian = true;
    graph_mark_visited(G, v);
    if (path_push_vertex(curr, v, G)) {
        for (uint32_t i = 0; i < graph_vertices(G); i++) {
            if (graph_has_edge(G, v, i) && (!graph_visited(G, i))) {
                (*caller)++;
                dfs(G, i, curr, shortest, cities, outfile);
            }
        }
        for (uint32_t j = 0; j < graph_vertices(G); j++) {
            if (!graph_visited(G, j)) {
                isHamiltonian = false;
                break;
            }
        }
        if (isHamiltonian && (!graph_has_edge(G, v, START_VERTEX))) {
            isHamiltonian = false;
        }
        if (isHamiltonian
            && ((path_length(curr) < path_length(shortest)) || ((path_length(shortest) == 0)))) {
            path_push_vertex(curr, START_VERTEX, G);
            path_copy(shortest, curr);
            if (verbose) {
                printf("Path Length: %d\n", path_length(curr));
                printf("Path: ");
                path_print(curr, outfile, cities);
            }
            path_pop_vertex(curr, ptr, G);
        }
        if (path_pop_vertex(curr, ptr, G)) {
            graph_mark_unvisited(G, v);
        } else {
            printf("WRONG");
        }

    } else {
        printf("INCORRECT");
    }
}
int main(int argc, char **argv) {
    int opt = 0;
    bool help = false;
    FILE *fp = stdout;
    FILE *inputp = stdin;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'h': help = true; break;
        case 'v': *verbpoint = true; break;
        case 'u': *undd = true; break;
        case 'i': inputp = fopen(optarg, "r"); break;
        case 'o': fp = fopen(optarg, "w"); break;
        }
    }
    if (help) {
        printf("SUMMARY\n");
        printf("\tFinding Hamiltonian Paths using Depth-First Search\n");
        printf("MANUAL\n");
        printf("\t.tsp [-u] [-v] [-h] [-i infile] [-o outfile]\n");
        printf("OPTIONS\n");
        printf("-u: creates undirected version of graph\n");
        printf("-v: enables verbose mode\n");
        printf("-h: help menu to use program\n");
        printf("-i: specify which file to be receive data from (default is stdin)\n");
        printf("-o: specify which file to print to (default is stdout)\n");
        return false;
    }
    char **arr = NULL;
    arr = malloc((6 * sizeof(char *)));
    uint32_t num_verts = 0;
    uint32_t a = 0;
    uint32_t b = 0;
    uint32_t c = 0;
    int r = 0;
    char bar[1024];
    fscanf(inputp, "%d", &num_verts);
    fgets(bar, 1024, inputp);
    for (uint32_t g = 0; g < num_verts; g++) {
        fgets(bar, 1024, inputp);
        arr[g] = strdup(bar);
        //removing newline character from Jerry Coffin on Stack Overflow
        arr[g][strcspn(arr[g], "\n")] = 0;
    }
    Graph *big = graph_create(num_verts, *undd);
    while ((r = fscanf(inputp, "%d %d %d", &a, &b, &c)) != EOF) {
        if (r != 3) {
            printf("malformed edge\n");
            return false;
        }
        graph_add_edge(big, a, b, c);
    }
    Path *current = path_create();
    Path *shortpath = path_create();
    (*caller)++;
    dfs(big, START_VERTEX, current, shortpath, arr, fp);
    printf("Path Length: %d\n", path_length(shortpath));
    printf("Path: ");
    path_print(shortpath, fp, arr);
    printf("Total recursive calls: %d\n", calls);
    path_delete(&shortpath);
    path_delete(&current);
    graph_delete(&big);
    for (uint32_t g = 0; g < num_verts; g++) {
        free(arr[g]);
    }

    free(arr);
}
