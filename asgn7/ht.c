#include "ht.h"

#include "bf.h"
#include "bv.h"
#include "ll.h"
#include "node.h"
#include "speck.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//defines a hash table
typedef struct HashTable {
    uint64_t salt[2];
    uint32_t size;
    bool mtf;
    LinkedList **lists;
} HashTable;
//creates a hash table
HashTable *ht_create(uint32_t size, bool mtf) {
    HashTable *ht = (HashTable *) malloc(sizeof(HashTable));
    if (ht) {
        ht->salt[0] = 0x9846e4f157fe8840;
        ht->salt[1] = 0xc5f318d7e055afb8;
        ht->size = size;
        ht->mtf = mtf;
        ht->lists = (LinkedList **) calloc(size, sizeof(LinkedList *));
        if (!ht->lists) {
            free(ht);
            ht = NULL;
        }
    }
    return ht;
}
//deletes the hash table
void ht_delete(HashTable **ht) {
    if (*ht && (*ht)->lists) {
        for (uint32_t i = 0; i < (*ht)->size; i++) {
            ll_delete(&(((*ht)->lists)[i]));
        }
        free((*ht)->lists);
        free(*ht);
        *ht = NULL;
    }
    return;
}
//returns the size of the hash table
uint32_t ht_size(HashTable *ht) {
    return ht->size;
}
//look if an item is in the hash table
//if the item was found it returns the node
//if it was not found it returns NULL
Node *ht_lookup(HashTable *ht, char *oldspeak) {
    uint32_t index = hash(ht->salt, oldspeak) % ht->size;
    if (!ht->lists[index]) {
        return NULL;
    }
    return ll_lookup(ht->lists[index], oldspeak);
}
//inserts an item into the hashtable
void ht_insert(HashTable *ht, char *oldspeak, char *newspeak) {
    uint32_t index = hash(ht->salt, oldspeak) % ht->size;
    if (!ht->lists[index]) {
        ht->lists[index] = ll_create(ht->mtf);
    }
    ll_insert(ht->lists[index], oldspeak, newspeak);
}
//counts the number of linked lists in the hash table
uint32_t ht_count(HashTable *ht) {
    uint32_t count = 0;
    for (uint32_t i = 0; i < ht->size; i++) {
        if (ht->lists[i] != NULL) {
            count++;
        }
    }
    return count;
}
//prints the hash table
void ht_print(HashTable *ht) {
    for (uint32_t i = 0; i < ht->size; i++) {
        printf("%d: ", i + 1);
        if (!ht->lists[i]) {
            printf("EMPTY\n");
        } else {
            ll_print(ht->lists[i]);
        }
    }
}
