#ifndef STRUCTURES_H
#define STRUCTURES_H

/**
 * @brief Struture of the nodes of the occurrences list.
 * 
 */
typedef struct Element{
    char chara;
    int occurrences;
    struct Element * next;
}Element;

/**
 * @brief Struture of the occurrences list.
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
    int haveChara; // 1 = occurrence with character, 0 = just occurrence.
    struct Node* left;
    struct Node* right;
}Node;

/**
 * @brief Struture ofthe Huffman tree.
 * 
 */
typedef Node* Tree;

typedef struct QueueElement{
    Node * data;
    struct QueueElement * next;
}QueueElement;

typedef struct Queue{
    QueueElement * values_of_queue;
}Queue;

typedef struct QueueCharElement{
    char ** data;
    struct QueueCharElement * next;
}QueueCharElement;

typedef struct QueueChar{
    QueueCharElement * values_of_queue;
}QueueChar;

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

QueueCharElement * create_QueueCharElement(char ** data);

QueueChar * create_queueChar();

int is_emptyChar(QueueChar * queue);

void enqueueChar(QueueChar * queue, char ** data);

char ** dequeueChar(QueueChar * queue);

char ** frontChar(QueueChar * queue);

void free_queueChar(QueueChar * queue);

#endif /* STRUCTURES_H */
