#include "bv.h"
#include "bf.h"
#include "node.h"
#include "ll.h"
#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "speck.h"
#include <string.h>

typedef struct LinkedList {
    uint32_t length;
    Node *head;
    Node *tail;
    bool mtf;
} LinkedList;

LinkedList *ll_create(bool mtf) {
	LinkedList *ll = (LinkedList *) malloc(sizeof(LinkedList));
	if(ll) {
		ll->length = 0;
		ll->mtf = mtf;
		ll->head = node_create(NULL, NULL);
		ll->tail = node_create(NULL, NULL);
		ll->head->next = ll->tail;
		ll->head->prev = NULL;
		ll->tail->next = NULL;
		ll->tail->prev = ll->head;	
	}
	return ll;

}

void ll_delete(LinkedList **ll) {
	if(*ll) {
		Node *n = (*ll)->head;
		Node *p = NULL;
		while(n) {
			p = n->next;
			node_delete(&n);
			n = p;
		}
		free(*ll);
		*ll = NULL;	
	}
	return;
}

uint32_t ll_length(LinkedList *ll) {
	return ll->length;
}

Node *ll_lookup(LinkedList *ll, char *oldspeak) {
	bool found = false;
	Node *n = ll->head->next;
	while(n) {
		if(n->next == NULL) {
			break;
		}
		if(strcmp(n->oldspeak,oldspeak) == 0) {
			found = true;
			break;
		}
		n = n->next;
	}
	if(!found) {
		return NULL;
	}
	if(ll->mtf) {
		n->prev->next = n->next;
		n->next->prev = n->prev;
		n->prev = ll->head;
		n->next = ll->head->next;
		ll->head->next = n;
		n->next->prev = n;
	}
	return n;
}

void ll_insert(LinkedList *ll, char *oldspeak, char *newspeak) {
	if(!ll_lookup(ll, oldspeak)) {
		Node *n = node_create(oldspeak, newspeak);
		ll->length++;
		n->prev = ll->head;
		n->next = ll->head->next;
		ll->head->next = n;
		n->next->prev = n;
	}
}

void ll_print(LinkedList *ll) {
	Node *n = ll->head->next;
        while(n) {
		if(n->next == NULL) {
                        break;
                }
        	node_print(n);
		n=n->next;
        }

}

