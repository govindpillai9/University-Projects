#include "node.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
//function creates a node
Node *node_create(uint8_t symbol, uint64_t frequency) {
    Node *n = (Node *) malloc(sizeof(Node));
    if (n) {
        n->symbol = symbol;
        n->frequency = frequency;
        n->left = NULL;
        n->right = NULL;
    }
    return n;
}
//function deletes a node
void node_delete(Node **n) {
    if (*n) {
        free(*n);
        *n = NULL;
    }
    return;
}
//function joins two nodes together to create parent node
Node *node_join(Node *left, Node *right) {
    uint64_t freq = left->frequency + right->frequency;
    Node *new_node = node_create('$', freq);
    new_node->left = left;
    new_node->right = right;
    return new_node;
}
//function prints node
void node_print(Node *n) {
    printf("-----------------------\n");
    printf("Node: (%d, %lu)\n", n->symbol, n->frequency);
    if (n->left) {
        printf("left node: (%d, %lu)\n", n->left->symbol, n->left->frequency);
    } else {
        printf("left node: None\n");
    }
    if (n->right) {
        printf("right node: (%d, %lu)\n", n->right->symbol, n->right->frequency);
    } else {
        printf("right node: None\n");
    }
}
