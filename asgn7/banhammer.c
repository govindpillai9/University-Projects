#include "bf.h"
#include "bv.h"
#include "ht.h"
#include "ll.h"
#include "messages.h"
#include "node.h"
#include "parser.h"
#include "speck.h"

#include <ctype.h>
#include <inttypes.h>
#include <regex.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define WORD    "[_a-zA-Z0-9]+(('|-)[_a-zA-Z0-9]+)*"
#define OPTIONS "ht:f:ms"
int main(int argc, char **argv) {
    int opt = 0;
    uint32_t t_size = 10000;
    uint32_t f_size = 1048576;
    bool m = false;
    bool stats = false;
    bool help = false;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'h': help = true; break;
        case 't': t_size = (uint32_t) atoi(optarg); break;
        case 'f': f_size = (uint32_t) atoi(optarg); break;
        case 'm': m = true; break;
        case 's': stats = true; break;
        }
    }
    if (help) {
        printf("SYNOPSIS\n");
        printf("   A word filter program for the GPRSC.\n");
        printf("   Filters and reports bad words from input file.\n");
        printf("USAGE\n");
        printf("   ./banhammer [-h] [-t] [-f] [-m] [-s]\n");
        printf("OPTIONS\n");
        printf("   h: shows help menu\n");
        printf("   t: specify hash table size (default: 10000)\n");
        printf("   f: specify bloom filter size (default: 1048576)\n");
        printf("   m: enables move-to-front option\n");
        printf("   s: prints program statistics\n");
        return 0;
    }

    BloomFilter *bf = bf_create(f_size);
    HashTable *ht = ht_create(t_size, m);
    LinkedList *bad_list = ll_create(m);
    LinkedList *old_list = ll_create(m);
    char buffer[4096];
    FILE *fp;
    fp = fopen("badspeak.txt", "r");
    while (fscanf(fp, "%s", buffer) != EOF) {
        bf_insert(bf, buffer);
        ht_insert(ht, buffer, NULL);
    }

    char old[4096];
    char new[4096];
    FILE *optr;
    optr = fopen("newspeak.txt", "r");
    while (fscanf(optr, "%s", old) != EOF) {
        fscanf(optr, "%s", new);
        bf_insert(bf, old);
        ht_insert(ht, old, new);
    }
    regex_t re;
    if (regcomp(&re, WORD, REG_EXTENDED)) {
        fprintf(stderr, "Failed to compile regex.\n");
        return 1;
    }

    char *word = NULL;
    while ((word = next_word(stdin, &re)) != NULL) {
        char new_word[strlen(word) + 1];
        for (uint32_t i = 0; i < strlen(word); i++) {
            if (isalpha(word[i])) {
                new_word[i] = tolower(word[i]);
            } else {
                new_word[i] = word[i];
            }
        }
        new_word[strlen(word)] = 0;
        if (bf_probe(bf, new_word)) {
            Node *n = ht_lookup(ht, new_word);
            if (n) {
                if (n->newspeak == NULL) {
                    ll_insert(bad_list, new_word, NULL);
                } else {
                    ll_insert(old_list, new_word, n->newspeak);
                }
            }
        }
    }
    if (stats) {
        printf("Seeks: %lu\n", seeks);
        printf("Average seek length: %.6f\n", ((float) (links)) / seeks);
        printf("Hash table load: %.6f%%\n", 100 * ((float) (ht_count(ht))) / ht_size(ht));
        printf("Bloom filter load: %.6f%%\n", 100 * ((float) (bf_count(bf))) / bf_size(bf));
        return 0;
    }
    if (ll_length(bad_list) == 0) {
        printf("%s", goodspeak_message);
        ll_print(old_list);
    } else {
        if (ll_length(old_list) == 0) {
            printf("%s", badspeak_message);
            ll_print(bad_list);
        } else {
            printf("%s", mixspeak_message);
            ll_print(bad_list);
            ll_print(old_list);
        }
    }
    clear_words();
    regfree(&re);
    fclose(optr);
    fclose(fp);
    ll_delete(&old_list);
    ll_delete(&bad_list);
    ht_delete(&ht);
    bf_delete(&bf);
    return 0;
}
