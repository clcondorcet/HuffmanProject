#include "structures.h"
#include <stdlib.h>

Element_occur* create_element(char chara, int occurrences){
    Element_occur* newEle = (Element_occur*) malloc(sizeof(Element_occur));
    newEle->chara = chara;
    newEle->occurrences = occurrences;
    newEle->next = NULL;
    return newEle;
}

Element_occur* popMin(List * list){
    if(*list != NULL){
        Element_occur ** min = list;
        Element_occur ** temp = list;
        while(*temp != NULL){
            if((*temp)->occurrences < (*min)->occurrences){
                min = temp;
            }
            temp = &((*temp)->next);
        }
        Element_occur * toReturn = (*min);
        *min = (*min)->next;
        toReturn->next = NULL;
        return toReturn;
    }else{
        return NULL;
    }
}

Node* create_node(char chara, int haveChara, int occurrences, Node* left, Node* right){
    Node* newNode = (Node*) malloc(sizeof(Node));
    newNode->chara = chara;
    newNode->haveChara = haveChara;
    newNode->occurrences = occurrences;
    newNode->left = left;
    newNode->right = right;
    return newNode;
}

int treeDeapth(Node * node){
    if(node == NULL){
        return 0;
    }
    int max = treeDeapth(node->left);
    int right = treeDeapth(node->right);
    if(right > max){
        max = right;
    }
    return max + 1;
}

QueueElement * create_QueueElement(Node * data){
    QueueElement * newEle = (QueueElement*) malloc(sizeof(QueueElement));
    newEle->data = data;
    newEle->next = NULL;
    return newEle;
}

Queue * create_queue(){
    Queue * newQueue = (Queue *) malloc(sizeof(Queue));
    newQueue->values_of_queue = NULL;
    return newQueue;
}

int is_empty(Queue * queue){
    if(queue->values_of_queue == NULL){
        return 1;
    }
    return 0;
}

void enqueue(Queue * queue, Node * data){
    if(data != NULL){
        QueueElement * newEle = create_QueueElement(data);
        QueueElement ** temp = &(queue->values_of_queue);
        while((*temp) != NULL){
            temp = &((*temp)->next);
        }
        *temp = newEle;
    }
}

Node * dequeue(Queue * queue){
    Node * data;
    QueueElement * temp;
    if(is_empty(queue) == 1){
        return NULL;
    }
    temp = queue->values_of_queue;
    queue->values_of_queue = temp->next;
    data = temp->data;
    free(temp);
    return data;
}

Node * front(Queue * queue){
    QueueElement * temp;
    if(is_empty(queue) == 1){
        return NULL;
    }
    return queue->values_of_queue->data;
}

void free_queue(Queue * queue){
    QueueElement * node = queue->values_of_queue;
    QueueElement * temp;
    while(node != NULL){
        temp = node->next;
        free(node);
        node = temp;
    }
    free(queue);
}

QueueCharElement * create_QueueCharElement(char ** data){
    QueueCharElement * newEle = (QueueCharElement*) malloc(sizeof(QueueCharElement));
    newEle->data = data;
    newEle->next = NULL;
    return newEle;
}

QueueChar * create_queueChar(){
    QueueChar * newQueue = (QueueChar *) malloc(sizeof(QueueChar));
    newQueue->values_of_queue = NULL;
    return newQueue;
}

int is_emptyChar(QueueChar * queue){
    if(queue->values_of_queue == NULL){
        return 1;
    }
    return 0;
}

void enqueueChar(QueueChar * queue, char ** data){
    if(data != NULL){
        QueueCharElement * newEle = create_QueueCharElement(data);
        QueueCharElement ** temp = &(queue->values_of_queue);
        while((*temp) != NULL){
            temp = &((*temp)->next);
        }
        *temp = newEle;
    }
}

char ** dequeueChar(QueueChar * queue){
    char ** data;
    QueueCharElement * temp;
    if(is_emptyChar(queue) == 1){
        return NULL;
    }
    temp = queue->values_of_queue;
    queue->values_of_queue = temp->next;
    data = temp->data;
    free(temp);
    return data;
}

char ** frontChar(QueueChar * queue){
    QueueCharElement * temp;
    if(is_emptyChar(queue) == 1){
        return NULL;
    }
    return queue->values_of_queue->data;
}

void free_queueChar(QueueChar * queue){
    QueueCharElement * node = queue->values_of_queue;
    QueueCharElement * temp;
    while(node != NULL){
        temp = node->next;
        free(node);
        node = temp;
    }
    free(queue);
}

Node_newType* create_Node_newType(char letter, Element_newType* list, Node_newType* theRight, Node_newType* theLeft){
    Node_newType* newNode = (Node_newType*)malloc(sizeof(Node_newType));
    newNode->data = letter;
    newNode->l = list;
    newNode->right = theRight;
    newNode->left = theLeft;
    return newNode;
}

Element_newType* create_Element_newType(int nbr, Element_newType* list){
    Element_newType* newElement = (Element_newType*)malloc(sizeof(Element_newType));
    newElement->boolean = nbr;
    newElement->next = list;
    return newElement;
}
