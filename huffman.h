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
 * @brief create a dynamic array with the new node placed.
 * 
 * @param array, size_array, position_letter, letter 
 * @param size_array
 * @param position_letter
 * @param letter 
 * @return Node**
 */
Node** add_two_array(Node** array, int size_array, int position_letter, char letter);

/**
 * @brief build an array of node containing letters
 *  Use the search by dichotomous
 * @param none 
 * @return Node** 
 */
Node** array_of_occurences();

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

/**
 * @brief Adding a new leaf to an AVL tree.
 * 
 * @param Node_newType**
 * @param Node_newType*
 */
void add_on_AVL(Node_newType** avl, Node_newType* node_for_AVL);

/**
 * @brief creation of the avl which contains the dico.
 * 
 * @param Node*
 * @param char**
 * @param char**
 * @param Node_newType**
 */
void search_code_to_createAVL(Node* tree, char** list1, int size, Node_newType** avl);

/**
 * @brief create the huffman dictionary.
 * 
 * @param Node* 
 * @return Node_newType*
 */
Node_newType* create_the_new_dico(Node* tree, int deapth);

#endif /* HUFFMAN_H */
