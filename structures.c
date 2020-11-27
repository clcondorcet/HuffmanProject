#include "structures.h"
#include <stdlib.h>

Element * create_element(char chara, int occurrences){
    Element * newEle = (Element *) malloc(sizeof(Element));
    newEle->chara = chara;
    newEle->occurrences = occurrences;
    newEle->next = NULL;
    return newEle;
}

Element * popMin(List * list){
    if(*list != NULL){
        Element ** min = list;
        Element ** temp = list;
        while(*temp != NULL){
            if((*temp)->occurrences < (*min)->occurrences){
                min = temp;
            }
            temp = &((*temp)->next);
        }
        Element * toReturn = (*min);
        *min = (*min)->next;
        toReturn->next = NULL;
        return toReturn;
    }else{
        return NULL;
    }
}

Node * create_node(char chara, int haveChara, int occurrences, Node * left, Node * right){
    Node * newNode = (Node *) malloc(sizeof(Node));
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