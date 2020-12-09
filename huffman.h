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
 * @brief Create a huffman tree object.
 *
 * @param occurrencesList
 * @return Tree
 */
Tree create_huffman_tree(List * occurrencesList);


#endif /* HUFFMAN_H */
