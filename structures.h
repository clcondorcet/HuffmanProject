#ifndef STRUCTURES_H
#define STRUCTURES_H

typedef struct Element{
    char chara;
    int occurrences;
    struct Element * next;
}Element;

typedef Element* List;

typedef struct Node{
    char chara;
    int occurrences;
    int haveChara;
    struct Node* left;
    struct Node* right;
}Node;

typedef Node* Tree;

Element * create_element(char chara, int occurrences);
Element * popMin(List * list);
Node * create_node(char chara, int haveChara, int occurrences, Node * left, Node * right);
int treeDeapth(Node * node);

#endif /* STRUCTURES_H */