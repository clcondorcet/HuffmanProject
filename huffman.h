#ifndef HUFFMAN_H
#define HUFFMAN_H

#include "structures.h"
#include <stdio.h>
#include <stdlib.h>

Tree create_huffman_tree(List * occurrencesList);
void printDico(Node * tree, FILE * file, char * chars);
int createDico(Tree huffmanTree);

#endif /* HUFFMAN_H */
