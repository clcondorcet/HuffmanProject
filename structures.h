#ifndef STRUCTURES_H
#define STRUCTURES_H
/**
 * @file structures.h
 * @author Grp5
 * @brief All function related to structures.
 * @version 0.1
 * @date 2020-12-11
 * 
 */



/**
 * @brief Struture of the nodes of the occurrences list.
 * 
 */
typedef struct Element_occur{
    char chara;
    int occurrences;
    struct Element_occur* next;
}Element_occur;

/**
 * @brief Struture of the occurrences list.
 * 
 */
typedef Element_occur* List;

/**
 * @brief Struture of the nodes of the Huffman tree.
 * 
 */
typedef struct Node{
    char chara;
    int occurrences;
    int haveChara; // 1 = occurrence with character, 0 = just occurrence.
    struct Node* left;
    struct Node* right;
}Node;

/**
 * @brief Struture ofthe Huffman tree.
 * 
 */
typedef Node* Tree;

/**
 * @brief Structure for a Queue Element with a Node* in data
 * 
 */
typedef struct QueueElement{
    Node * data;
    struct QueueElement * next;
}QueueElement;

/**
 * @brief Structure for a Queue (Node* data)
 * 
 */
typedef struct Queue{
    QueueElement * values_of_queue;
}Queue;

/**
 * @brief Structure for a Queue Element with a char** in data
 * 
 */
typedef struct QueueCharElement{
    char ** data;
    struct QueueCharElement * next;
}QueueCharElement;

/**
 * @brief Structure for a Queue (Char** data)
 * 
 */
typedef struct QueueChar{
    QueueCharElement * values_of_queue;
}QueueChar;

/**
 * @brief Create a element object.
 * 
 * @param chara 
 * @param occurrences 
 * @return Element_occur* 
 */
Element_occur * create_element(char chara, int occurrences);

/**
 * @brief remove the minimum element of the list and return it.
 * 
 * @param list 
 * @return Element_occur* 
 */
Element_occur * popMin(List * list);

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

/**
 * @brief Create a QueueElement object
 * 
 * @param data 
 * @return QueueElement* 
 */
QueueElement * create_QueueElement(Node * data);

/**
 * @brief Create a queue object
 * 
 * @return Queue* 
 */
Queue * create_queue();

/**
 * @brief Return wether or not a queue is empty.
 * 
 * @param queue 
 * @return 1 empty, 0 not empty.
 */
int is_empty(Queue * queue);

/**
 * @brief Add a Node* at the end of a Queue (a QueueElement is automatically created).
 * 
 * @param queue 
 * @param data 
 */
void enqueue(Queue * queue, Node * data);

/**
 * @brief Remove and return the first Node* of a Queue (it free the QueueElement automatically).
 * 
 * @param queue 
 * @return Node* or NULL
 */
Node * dequeue(Queue * queue);

/**
 * @brief Return the first Node* of a Queue but doesn't remove it.
 * 
 * @param queue 
 * @return Node* 
 */
Node * front(Queue * queue);

/**
 * @brief Free the Queue (it free QueueElement but not the Node* inside).
 * 
 * @param queue 
 */
void free_queue(Queue * queue);

/**
 * @brief Create a QueueCharElement object
 * 
 * @param data 
 * @return QueueCharElement* 
 */
QueueCharElement * create_QueueCharElement(char ** data);

/**
 * @brief Create a queueChar object
 * 
 * @return QueueChar* 
 */
QueueChar * create_queueChar();

/**
 * @brief Return wether or not a queue is empty.
 * 
 * @param queue 
 * @return 1 empty, 0 not empty.
 */
int is_emptyChar(QueueChar * queue);

/**
 * @brief Add a char** at the end of a Queue (a QueueCharElement is automatically created).
 * 
 * @param queue 
 * @param data 
 */
void enqueueChar(QueueChar * queue, char ** data);

/**
 * @brief Remove and return the first char** of a Queue (it free the QueueCharElement automatically).
 * 
 * @param queue 
 * @return Node* or NULL
 */
char ** dequeueChar(QueueChar * queue);

/**
 * @brief Return the first char** of a Queue but doesn't remove it.
 * 
 * @param queue 
 * @return Node* 
 */
char ** frontChar(QueueChar * queue);

/**
 * @brief Free the Queue (it free QueueElement but not the char** inside).
 * 
 * @param queue 
 */
void free_queueChar(QueueChar * queue);

/**
 * @brief Struture of a linked list with an integer data.
 * 
 */
typedef struct Element_newType{
    int boolean;
    struct Element_newType* next;
}Element_newType;

/**
 * @brief  Struture of the nodes of the AVL tree with a list.
 * 
 */
typedef struct Node_newType{
    char data;
    Element_newType* l;
    struct Node_newType* right;
    struct Node_newType* left;
}Node_newType;

/**
 * @brief Create a Element_newType object.
 *
 * @param int
 * @param Element_newType* 
 * @return Element_newType* 
 */
Element_newType* create_Element_newType(int nbr, Element_newType* list);

/**
 * @brief Create a Node_newType object.
 * 
 * @param char 
 * @param Element_newType*
 * @param Node_newType*
 * @param Node_newType*
 * @return Node* 
 */
Node_newType* create_Node_newType(char letter, Element_newType* list, Node_newType* theRight, Node_newType* theLeft);

/**
 * @brief Return the deapth of a tree with the type Node_new_Type.
 * 
 * @param Node_newType* 
 * @return int
 */
int tree_depth_Node_newType(Node_newType* tree);

#endif /* STRUCTURES_H */
