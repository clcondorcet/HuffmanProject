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

int createDicoOptimised(Tree huffmanTree);

/**
 * @brief Function that translates a text into a binary sequence based on a Huffman dictionary
 * 
 */
void translate_texte_with_huffman();

/**
 * @brief Sort an array of nodes based on occurrences with selection sort algorithm.
 * 
 * @param array 
 * @param size 
 */
void selection_sort(Node ** array, int size);

/**
 * @brief Debug function to print an array of nodes.
 * 
 * @param array 
 * @param size 
 */
void printList(Node ** array, int size);

/**
 * @brief Function used in create_huffman_tree_Optimised(), to get the minimum node from two queues with sourceQueue in priority.
 * 
 * @param sourceQueue 
 * @param newNodeQueue 
 * @return Node* or NULL
 */
Node * getMin(Queue * sourceQueue, Queue * newNodeQueue);

/**
 * @brief Create a optimised Huffman Tree.
 * 
 * @param arrayNodes 
 * @param size 
 * @return Tree 
 */
Tree create_huffman_tree_Optimised(Node ** arrayNodes, int size);

#endif /* HUFFMAN_H */
