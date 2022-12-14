#include "graph.h"
#include "stack.h"
#include "vertices.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
typedef struct Path {
    Stack *vertices;
    uint32_t length;
} Path;
//creates the path
Path *path_create(void) {
    Path *p = (Path *) malloc(sizeof(Path));
    if (p) {
        p->length = 0;
        p->vertices = stack_create(VERTICES + 1);
        if (!p->vertices) {
            free(p);
            p = NULL;
        }
    }
    return p;
}
//deletes the path
void path_delete(Path **p) {
    if (*p && (*p)->vertices) {
        stack_delete(&(*p)->vertices);
        free(*p);
        *p = NULL;
    }
    return;
}
//pushes a vertex onto the path
bool path_push_vertex(Path *p, uint32_t v, Graph *G) {
    uint32_t x = 0;
    uint32_t *j;
    j = &x;
    if (stack_peek(p->vertices, j)) {
        if (graph_has_edge(G, x, v)) {
            if (stack_push(p->vertices, v)) {
                p->length += graph_edge_weight(G, x, v);
                return true;
            }
        }
    }
    return stack_push(p->vertices, v);
}
//pops a vertex off the path
bool path_pop_vertex(Path *p, uint32_t *v, Graph *G) {
    uint32_t x = 0;
    uint32_t *j;
    j = &x;
    if (stack_size(p->vertices) == 1) {
        return stack_pop(p->vertices, v);
    } else if (stack_pop(p->vertices, v)) {
        if (stack_peek(p->vertices, j)) {
            p->length -= graph_edge_weight(G, x, *v);
            return true;
        }
    }
    return false;
}
//returns the number of vertices in the path
uint32_t path_vertices(Path *p) {
    return stack_size(p->vertices);
}
//returns the sum of the weights of the path
uint32_t path_length(Path *p) {
    return p->length;
}
//copies a source path into a destination path
void path_copy(Path *dst, Path *src) {
    stack_copy(dst->vertices, src->vertices);
    dst->length = src->length;
}
//prints the path
void path_print(Path *p, FILE *outfile, char *cities[]) {
    stack_print(p->vertices, outfile, cities);
}
