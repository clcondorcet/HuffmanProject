#ifndef INPUT_OUTPUT_H_INCLUDED
#define INPUT_OUTPUT_H_INCLUDED
/**
 * @file input_output.h
 * @author Grp5
 * @brief All function related to reading, output and console.
 * @version 0.1
 * @date 2020-12-11
 * 
 */

#include "structures.h"
#include "huffman.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief transform a letter into it's binary code
 *
 * @param letter
 * @return binary code
 */
int* letter_to_binary(int letter);

/**
 * @brief function to print a char into a file
 *
 * @param p_file, binary
 * @return none
 */
void print_in_file(FILE * bin, int* binary);

/**
 * @brief Function to translate a text file to its binary text
 *
 * @param input_file and output_file
 * @return none
 */
void translation_file_to_binary(char* input_file, char* output_file);

/**
 * @brief Function to calculate the number of characters in a texte file
 *
 * @param txt_name
 * @return the number of characters in the text
 */
int nb_character_txt_file(char* txt_name);

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
 * @return 0 if error, 1 if all is good.
 */
int createDico(Tree huffmanTree);

/**
 * @brief Copy an array of characters into a new malloc one.
 * 
 * @param array
 * @param size
 * @return char**
 */
char ** copyArray(char ** array, int size);

/**
 * @brief Print a huffman tree optimised in dico.txt.
 * 
 * @param huffmanTree 
 * @return 0 if error, 1 if all is good.
 */
int createDicoOptimised(Tree huffmanTree);

/**
 * @brief Function that translates a text into a binary sequence based on a Huffman dictionary
 * The function has no parameters because we open and close the file in the function
 * The function take a letter of the text, find her binary sequence and print the binary sequence in a file
 */
void translate_texte_with_huffman();


/**
 * @brief Compresses a file with the huffman tree
 * The function uses all the function used before to compress a file with the huffman tree
 * @param none
 * @return none
 */
void compress_file_with_huffman();

/**
 * @brief Decompresses a file with the huffman tree
 * The function uses the huffman tree and the compressed file to decompress the text
 * @param Tree/Node*
 * @return none
 */
void decompress_text_with_huffman(Tree huffmantree);

#endif // INPUT_OUTPUT_H_INCLUDED
