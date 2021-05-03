#include "graph.h"

#include "vertices.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Graph {
    uint32_t vertices;
    bool undirected;
    bool visited[VERTICES];
    uint32_t matrix[VERTICES][VERTICES];
} Graph;
//create graph
Graph *graph_create(uint32_t vertices, bool undirected) {
    Graph *G = (Graph *) malloc(sizeof(Graph));
    if (G) {
        G->vertices = vertices;
        G->undirected = undirected;
        for (uint32_t i = 0; i < VERTICES; i++) {
            G->visited[i] = false;
        }
        for (uint32_t x = 0; x < VERTICES; x++) {
            for (uint32_t y = 0; y < VERTICES; y++) {
                G->matrix[x][y] = 0;
            }
        }
    }
    return G;
}
//deletes graph
void graph_delete(Graph **G) {
    if (*G) {
        free(*G);
        *G = NULL;
    }
    return;
}
//returns the number of vertices in the graph
uint32_t graph_vertices(Graph *G) {
    return G->vertices;
}
//takes in three parameters and sets k as the weight to edge i,j
bool graph_add_edge(Graph *G, uint32_t i, uint32_t j, uint32_t k) {
    G->matrix[i][j] = k;
    if (G->undirected) {
        G->matrix[j][i] = k;
    }
    return true;
}
//checks if there is an edge at i,j
bool graph_has_edge(Graph *G, uint32_t i, uint32_t j) {
    return G->matrix[i][j] != 0;
}
//returns the weight of the edge at i,j
uint32_t graph_edge_weight(Graph *G, uint32_t i, uint32_t j) {
    return G->matrix[i][j];
}
//checks if specified vertex has been visited
bool graph_visited(Graph *G, uint32_t v) {
    return G->visited[v];
}
//marks specified vertex as visited
void graph_mark_visited(Graph *G, uint32_t v) {
    G->visited[v] = true;
}
//marks specified vertex as unvisited
void graph_mark_unvisited(Graph *G, uint32_t v) {
    G->visited[v] = false;
}
//prints the graph
void graph_print(Graph *G) {
    for (uint32_t x = 0; x < VERTICES; x++) {
        for (uint32_t y = 0; y < VERTICES; y++) {
            printf("%d ", G->matrix[x][y]);
            if (y == VERTICES - 1) {
                printf("\n");
            }
        }
    }
}
