#include "code.h"
#include "defines.h"
#include "header.h"
#include "huffman.h"
#include "io.h"
#include "node.h"
#include "pq.h"
#include "stack.h"

#include <fcntl.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define OPTIONS "hi:o:v"
static uint32_t treeindex = 0;
void post_tree(Node *root, uint8_t *treedump);
int main(int argc, char **argv) {
    //variables that will be used throughout program
    uint64_t histogram[ALPHABET];
    Code code_table[ALPHABET];
    int opt = 0;
    int infile_d = 0;
    int outfile_d = 1;
    bool help = false;
    bool verbose = false;
    Node *n = NULL;
    //options
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'h': help = true; break;
        case 'i': infile_d = open(optarg, O_RDONLY); break;
        case 'o': outfile_d = open(optarg, O_WRONLY | O_CREAT, S_IRWXU); break;
        case 'v': verbose = true; break;
        }
    }
    //shows help menu
    if (help) {
        printf("SYNOPSIS\n");
        printf("A Huffman encoder\n");
        printf("Compresses file using Huffman coding\n");
        printf("USAGE\n");
        printf("./encode [-h] [-i infile] [-o outfile] [-v]\n");
        printf("OPTIONS\n");
        printf("-h: help menu\n");
        printf("-v: prints statistics\n");
        printf("-i infile: Input file\n");
        printf("-o outfile: Output file\n");
        return 1;
    }
    //uses statbuf in order to get the size of the file
    struct stat statbuf;
    fstat(infile_d, &statbuf);
    fchmod(outfile_d, statbuf.st_mode);
    uint8_t buffer[statbuf.st_size];
    //reads the bytes from the input into the buffer
    read_bytes(infile_d, buffer, statbuf.st_size);
    //zeros out the histogram
    for (uint32_t i = 0; i < ALPHABET; i++) {
        histogram[i] = 0;
    }
    //loads the histogram
    for (uint32_t i = 0; i < statbuf.st_size; i++) {
        histogram[buffer[i]] += 1;
    }
    //increments both ends of the histogram by 1
    histogram[0] += 1;
    histogram[255] += 1;
    //builds the tree based on the histogram
    n = build_tree(histogram);
    //builds the codes based on our tree
    build_codes(n, code_table);
    //creates the header
    Header h;
    h.magic = MAGIC;
    h.permissions = statbuf.st_mode;
    h.file_size = statbuf.st_size;
    uint32_t unique = 0;
    for (uint32_t j = 0; j < 256; j++) {
        if (histogram[j] > 0) {
            unique++;
        }
    }
    h.tree_size = (3 * unique) - 1;
    //creates ans zeros out our treedump
    uint8_t treedump[(3 * unique) - 1];
    for (uint32_t i = 0; i < (3 * unique) - 1; i++) {
        treedump[i] = 0;
    }
    //loads our treedump
    post_tree(n, treedump);
    //writes the header to the outfile
    write_bytes(outfile_d, (uint8_t *) &h, sizeof(Header));
    //writes the treedump to the outfile
    write_bytes(outfile_d, treedump, (3 * unique) - 1);
    //writes the codes to the outfile
    for (uint32_t x = 0; x < statbuf.st_size; x++) {
        write_code(outfile_d, &(code_table[buffer[x]]));
    }
    //flush anything remaining in the buffer
    flush_codes(outfile_d);
    //close the infile
    close(infile_d);
    //prints verbose statistics
    if (verbose) {
        printf("Original File Size: %ld\n", statbuf.st_size);
        printf("New File Size: %lu\n", bytes_written);
        printf(
            "Space Saving: %.2lf\n", (1 - (double) bytes_written / (double) statbuf.st_size) * 100);
    }
}
//takes in a root and loads the given treedump
void post_tree(Node *root, uint8_t *treedump) {
    if (root->left == NULL || root->right == NULL) {
        treedump[treeindex] = 'L';
        treeindex++;
        treedump[treeindex] = root->symbol;
        treeindex++;
    } else {
        post_tree(root->left, treedump);
        post_tree(root->right, treedump);
        treedump[treeindex] = 'I';
        treeindex++;
    }
}
