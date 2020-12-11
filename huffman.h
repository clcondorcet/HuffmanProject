#ifndef HUFFMAN_H
#define HUFFMAN_H

#include "structures.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Create a list of occurences
 *
 * @param none
 * @return the list of occurences
 */
Element_occur* list_occurence();

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
 * @brief Create a huffman tree object.
 *
 * @param occurrencesList
 * @return Tree
 */
Tree create_huffman_tree(List * occurrencesList);

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

/**
 * @brief calculate the balance factor.
 * 
 * @param Node_newType* 
 * @return int
 */
int balance_factor(Node_newType* tree);

/**
 * @brief right rotation to balance the tree.
 * 
 * @param Node_newType** 
 * @return Element_occur* 
 */
void right_rotation(Node_newType** tree);

/**
 * @brief left rotation to balance the tree.
 * 
 * @param Node_newType** 
 */
void left_rotation(Node_newType** tree);

/**
 * @brief balance a tree;
 * 
 * @param Node_newType** 
 */
void balance(Node_newType** tree);

#endif /* HUFFMAN_H */
