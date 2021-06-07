#include "node.h"

#include "bf.h"
#include "bv.h"
#include "speck.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//string duplicate given by Prof. Long
#define strdup(s) strcpy(malloc(strlen(s) + 1), s)
//creates a node
Node *node_create(char *oldspeak, char *newspeak) {
    Node *n = (Node *) malloc(sizeof(Node));
    if (n) {
        if (oldspeak) {
            n->oldspeak = strdup(oldspeak);
        } else {
            n->oldspeak = NULL;
        }
        if (newspeak) {
            n->newspeak = strdup(newspeak);
        } else {
            n->newspeak = NULL;
        }
        n->next = NULL;
        n->prev = NULL;
    }
    return n;
}
//deletes the node
void node_delete(Node **n) {
    if ((*n)->newspeak) {
        free((*n)->newspeak);
        (*n)->newspeak = NULL;
    }
    if ((*n)->oldspeak) {
        free((*n)->oldspeak);
        (*n)->oldspeak = NULL;
    }
    if (*n) {
        free(*n);
        *n = NULL;
    }
    return;
}
//prints the node
void node_print(Node *n) {
    if (n->newspeak) {
        printf("%s -> %s\n", n->oldspeak, n->newspeak);
    } else {
        printf("%s\n", n->oldspeak);
    }
}
