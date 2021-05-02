#include "graph.h"
#include "stack.h"
#include <stdbool.h>
#include <stdio.h>
#include "vertices.h"
#include <stdlib.h>
#include <stdint.h>
typedef struct Path Path {
        Stack *vertices;
        uint32_t length;
}

Path *path_create(void) {
        Path *p = (Path *) malloc(sizeof(Path));
        if(p) {
                p->length = length;
                p->vertices = stack_create(VERTICES+1);
                if(!p->vertices) {
                        free(p);
                        p = NULL;
                }
        }
        return p;
}

void path_delete(Path **p) {
        if(*p && (*p)->vertices) {
                stack_delete(&p->vertices);
                free(*p);
                *p = NULL;
        }
        return;
}

bool path_push_vertex(Path *p, uint32_t v, Graph *G) {
	uint32_t x = 0;
	uint32_t *j;
	j = &x;
        if(stack_peek(p->vertices,j)) {
		if(graph_has_edge(G,x,v)) {
			if(stack_push(p->vertices, v)) {
				s->length += graph_edge_weight(G,x,v);
				return true;
			}
		}
	}else{
		return stack_push(p->vertices, v);
	}

}

bool path_pop_vertex(Path *p, uint32_t *v, Graph *G) {
	uint32_t x = 0;
	uint32_t *j;
	j = &x;
	if(stack_size(p->vertices) == 1) {
		return stack_pop(p->vertices, v);
	}
	else if(stack_pop(p->vertices, v)) {
		if(stack_peek(p->vertices, j)) {
			s->length -= graph_edge_weight(G,x,*v);
			return true;
		}
	}
	return false;
}

uint32_t path_vertices(Path *p) {
	return stack_size(p->vertices);
}

uint32_t path_length(Path *p) {
	return s->length;
}

void path_copy(Path *dst, Path *src) {
	stack_copy(dst->vertices,src->vertices);
}
void path_print(Path *p, FILE *outfile, char *cities[]) {
	stack_print(p->vertices,outfile,cities[]);
}

