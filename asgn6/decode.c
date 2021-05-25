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

int main(int argc, char **argv) {
    //variables that will be used throughout the program
    int opt = 0;
    int infile_d = 0;
    int outfile_d = 1;
    bool help = false;
    bool verbose = false;
    Node *tree;
    //options
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'h': help = true; break;
        case 'i': infile_d = open(optarg, O_RDONLY); break;
        case 'o': outfile_d = open(optarg, O_WRONLY | O_CREAT, S_IRWXU); break;
        case 'v': verbose = true; break;
        }
    }
    //prints help menu
    if (help) {
        printf("SYNOPSIS\n");
        printf("A Huffman decoder\n");
        printf("Decodes file encoded with Huffman codes\n");
        printf("USAGE\n");
        printf("./decode [-h] [-i infile] [-o outfile] [-v]\n");
        printf("OPTIONS\n");
        printf("-h: help menu\n");
        printf("-v: prints statistics\n");
        printf("-i infile: Input file\n");
        printf("-o outfile: Output file\n");
        return 1;
    }
    //creates a buffer that will read in magic number
    //then checks if that magic number is equal to the MACRO
    //magic. Depending on the check, we continue with our decoding.
    uint8_t buffer_magic[4];
    uint32_t m = 0;
    read_bytes(infile_d, buffer_magic, 4);
    m = ((uint32_t *) (buffer_magic))[0];
    if (m != MAGIC) {
        printf("invalid file");
        return 1;
    }
    //creates a buffer that will read permissions and
    //add them to the outfile.
    uint8_t buffer_permissions[2];
    uint16_t p = 0;
    read_bytes(infile_d, buffer_permissions, 2);
    p = ((uint16_t *) (buffer_permissions))[0];
    fchmod(outfile_d, p);
    //creates a buffer that reads in treedump size
    uint8_t buffer_tree[2];
    uint16_t t = 0;
    read_bytes(infile_d, buffer_tree, 2);
    t = ((uint16_t *) (buffer_tree))[0];
    //creates a buffer that reads in file size
    uint8_t buffer_file[8];
    uint64_t f = 0;
    read_bytes(infile_d, buffer_file, 8);
    f = ((uint64_t *) (buffer_file))[0];
    //creates buffer that reads the treedump.
    //Then rebuilds the tree using the treedump
    uint8_t buffer_reb[t];
    read_bytes(infile_d, buffer_reb, t);
    tree = rebuild_tree(t, buffer_reb);
    //traverses through the tree and writes the characters
    //found on leaf nodes in the tree using the codes in
    //the file.
    Node *hold = tree;
    uint8_t bit = 0;
    uint64_t bits_read = 0;
    uint8_t buffer_reading[f];
    while (bits_read < f) {
        read_bit(infile_d, &bit);
        if (bit == 0) {
            hold = hold->left;
        } else if (bit == 1) {
            hold = hold->right;
        }
        if (hold->left == NULL && hold->right == NULL) {
            buffer_reading[bits_read] = hold->symbol;
            bits_read++;
            hold = tree;
        }
    }
    //write whatever we loaded into the buffer after traversing
    //the tree.
    write_bytes(outfile_d, buffer_reading, f);
    close(infile_d);
    //prints statistics
    if (verbose) {
        printf("Original File Size: %ld\n", f);
        printf("New File Size: %lu\n", bytes_read);
        printf("Space Saving: %.2lf\n", (1 - (double) bytes_read / (double) f) * 100);
    }
}
