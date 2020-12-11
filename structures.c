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
