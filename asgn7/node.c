#include "bv.h"
#include "bf.h"
#include "node.h"
#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "speck.h"
#include <string.h>
#define strdup(s) strcpy(malloc(strlen(s) + 1), s)
Node *node_create(char *oldspeak, char *newspeak) {
	Node *n = (Node *) malloc(sizeof(Node));
	if(n) {
		if(oldspeak) {
			n->oldspeak = strdup(oldspeak);
		}
		if(newspeak) {
			n->newspeak = strdup(newspeak);
		}
		n->next = NULL;
		n->prev = NULL;
	}
	return n;
}

void node_delete(Node **n) {
    if ((*n)->newspeak) {
        free((*n)->newspeak);
	(*n)->newspeak = NULL;
    }
    if((*n)->oldspeak) {
	free((*n)->oldspeak);
	(*n)->oldspeak = NULL;
    }
    if(*n) {
        free(*n);
        *n = NULL;
    }
    return;
}

void node_print(Node *n) {
	if(n->newspeak) {
		printf("%s -> %s\n", n->oldspeak, n->newspeak);
	}else{
		printf("%s\n", n->oldspeak);
	}

}

