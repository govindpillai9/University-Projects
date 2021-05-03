#include "graph.h"
#include "stack.h"
#include <stdbool.h>
#include <stdio.h>
#include "vertices.h"
#include "path.h"
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
uint32_t calls = 0;
uint32_t *caller = &calls;
void dfs(Graph *G, uint32_t v, Path *curr, Path *shortest, char *cities[], FILE *outfile) {
	uint32_t poppers = 0;
	uint32_t *ptr;
	ptr = &poppers;
	bool isHamiltonian = true;
	graph_mark_visited(G, v);
	if (path_push_vertex(curr, v, G)) {
		for(uint32_t i = 0; i < graph_vertices(G); i++) {
			if(graph_has_edge(G, v, i) && (!graph_visited(G,i))) {
				(*caller)++;			
				dfs(G, i, curr, shortest, cities, outfile);
			}	
		}
		for(uint32_t j = 0; j < graph_vertices(G);j++) {
			if(!graph_visited(G,j)) {
				isHamiltonian = false;
				break;
			}
		}
		if(isHamiltonian && (!graph_has_edge(G, v,START_VERTEX))) {
			isHamiltonian = false;
		}
		if(isHamiltonian && ((path_length(curr) < path_length(shortest)) || ((path_length(shortest) == 0)))) {
			path_push_vertex(curr, START_VERTEX, G);
			path_copy(shortest, curr);
			printf("Path Length: %d\n",path_length(curr));
			printf("Path: ");
			path_print(curr, outfile, cities);
			printf("Total recursive calls: %d\n",calls);
		}
		if(path_pop_vertex(curr,ptr,G)) {
			graph_mark_unvisited(G, v);
		}else{
			printf("WRONG");
		}

	}else{
		printf("INCORRECT");
	}
}
int main(void) {
	char **arr = NULL;
        arr = malloc((6*sizeof(char*)));
	uint32_t num_verts = 0;
	uint32_t a = 0;
	uint32_t b = 0;
	uint32_t c = 0;
	char bar[1024];
	fscanf(stdin, "%d", &num_verts);
	fgets(bar,1024,stdin);
	for(uint32_t g = 0; g < num_verts; g++) {
		fgets(bar,1024,stdin);
		arr[g] = strdup(bar);
		//removing newline character from Jerry Coffin on Stack Overflow
		arr[g][strcspn(arr[g], "\n")] = 0;
	}
        Graph *big = graph_create(num_verts,false);
	while(fscanf(stdin, "%d %d %d",&a,&b,&c) != EOF) {
		graph_add_edge(big,a,b,c);
	}
	Path *current = path_create();
	Path *shortpath = path_create();
	FILE* fp = stdout;
	(*caller)++;
	dfs(big,START_VERTEX,current,shortpath,arr,fp);
	path_delete(&shortpath);
	path_delete(&current);
	graph_delete(&big);
	for(uint32_t g = 0; g < num_verts; g++) {
        	free(arr[g]);
        }

	free(arr);

}

