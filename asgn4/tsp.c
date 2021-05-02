#include "graph.h"
#include "stack.h"
#include <stdbool.h>
#include <stdio.h>
#include "vertices.h"
#include "path.h"
#include <stdlib.h>
#include <stdint.h>
void dfs(Graph *G, uint32_t v, Path *curr, Path *shortest, char *cities[], FILE *outfile);

void dfs(Graph *G, uint32_t v, Path *curr, Path *shortest, char *cities[], FILE *outfile) {
	bool isHamiltonian = true;
	graph_mark_visited(G, v);
	if (path_push_vertex(curr, v, G)) {
		for(uint32_t i = 0; i < graph_vertices(G); i++) {
			if(graph_has_edge(G, v, i) && (!graph_visited(G,v))) {
				dfs(G, i, curr, shortest, cities, outfile);
			}	
		}
		for(uint32_t j = 0; j < graph_vertices(G);j++) {
			if(!graph_visited(G,j)) {
				isHamiltonian = false;
				break;
			}
		}
		if(isHamiltonian && (!graph_has_edge(G, graph_vertices(G)-1,START_VERTEX))) {
			isHamiltonian = false;
		}
		if(isHamiltonian && (path_length(curr) < path_length(shortest))) {
			path_copy(shortest, curr);
			path_print(curr, outfile, cities);
		}
		if(path_pop_vertex(curr,v,G)) {
			graph_mark_unvisited(G, v);
		}else{
			printf("WRONG");
		}

	}else{
		printf("INCORRECT");
	}
 }

