#ifndef STRUCTURES_H
#define STRUCTURES_H

/**
 * @brief Struture of the nodes of the occurences list.
 * 
 */
typedef struct Element{
    char chara;
    int occurrences;
    struct Element * next;
}Element;

/**
 * @brief Struture of the occurences list.
 * 
 */
typedef Element* List;

/**
 * @brief Struture of the nodes of the Huffman tree.
 * 
 */
typedef struct Node{
    char chara;
    int occurrences;
    int haveChara;
    struct Node* left;
    struct Node* right;
}Node;

/**
 * @brief Struture ofthe Huffman tree.
 * 
 */
typedef Node* Tree;

/**
 * @brief Create a element object.
 * 
 * @param chara 
 * @param occurrences 
 * @return Element* 
 */
Element * create_element(char chara, int occurrences);

/**
 * @brief remove the minimum element of the list and return it.
 * 
 * @param list 
 * @return Element* 
 */
Element * popMin(List * list);

/**
 * @brief Create a node object.
 * 
 * @param chara 
 * @param haveChara 
 * @param occurrences 
 * @param left 
 * @param right 
 * @return Node* 
 */
Node * create_node(char chara, int haveChara, int occurrences, Node * left, Node * right);

/**
 * @brief Return the deapth of a tree.
 * 
 * @param node 
 * @return int 
 */
int treeDeapth(Node * node);

#endif /* STRUCTURES_H */