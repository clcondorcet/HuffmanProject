#ifndef HUFFMAN_H
#define HUFFMAN_H

#include "structures.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Create a huffman tree object.
 * 
 * @param occurrencesList 
 * @return Tree 
 */
Tree create_huffman_tree(List * occurrencesList);

/**
 * @brief A recursive function used by createDico to print the huffman tree in a file.
 * 
 * @param tree 
 * @param file 
 * @param chars 
 */
void printDico(Node * tree, FILE * file, char * chars);

/**
 * @brief Print a huffman tree in dico.txt.
 * 
 * @param huffmanTree 
 * @return 0 if error, 1 if all is good
 */
int createDico(Tree huffmanTree);

/**
 * @brief Function that translates a text into a binary sequence based on a Huffman dictionary
 * 
 */
void translate_texte_with_huffman();


#endif /* HUFFMAN_H */
