#include "bv.h"
#include "bf.h"
#include "node.h"
#include "ll.h"
#include "ht.h"
#include "parser.h"
#include <regex.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "speck.h"
#include <string.h>
#include <ctype.h>

#define WORD "[_a-zA-Z0-9]+(('|-)[_a-zA-Z0-9]+)*"

int main(void) {
	uint32_t t_size = 10000;
	uint32_t f_size = 1048576;
	bool m = false;
	BloomFilter *bf = bf_create(f_size);
	HashTable *ht = ht_create(t_size, m);
	LinkedList *bad_list = ll_create(false);
	LinkedList *old_list = ll_create(false);
    	char buffer[4096];
	FILE * fp;
	fp = fopen("badspeak.txt", "r");
    	while(fscanf(fp, "%s", buffer) != EOF) {
		bf_insert(bf, buffer);
		ht_insert(ht, buffer, NULL);
	}

	char old[4096];
	char new[4096];
	FILE *optr;
	optr = fopen("newspeak.txt", "r");
	while(fscanf(optr, "%s", old) != EOF) {
		fscanf(optr, "%s", new);
		bf_insert(bf, old);
		ht_insert(ht, old, new);
	}
	regex_t re;
	if(regcomp(&re, WORD, REG_EXTENDED)) {
		fprintf(stderr, "Failed to compile regex.\n");
		return 1;
	}

	char *word = NULL; 
	while((word = next_word(stdin, &re)) != NULL) {
		char new_word[strlen(word)+1];
		for(uint32_t i = 0; i < strlen(word); i++) {
			if(isalpha(word[i])) {
				new_word[i] = tolower(word[i]);
			}else{
				new_word[i] = word[i];
			}
		}
		new_word[strlen(word)] = 0;	
		if(bf_probe(bf, new_word)) {
			if(ht_lookup(ht, new_word)) {
				Node *n = ht_lookup(ht, new_word);
				if(n->newspeak == NULL) {					
					ll_insert(bad_list, new_word, NULL);
				}else{
					ll_insert(old_list, new_word, n->newspeak);
				}
			}
		}
	}
	ll_print(old_list);
	
	clear_words();
	regfree(&re);
	return 0; 
}

