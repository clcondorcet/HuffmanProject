#ifndef STRUCTURES_H
#define STRUCTURES_H

typedef struct Element_occur{
    char chara;
    int occurrences;
    struct Element_occur* next;
}Element_occur;

typedef Element_occur* List;

typedef struct Node{
    char chara;
    int occurrences;
    int haveChara;
    struct Node* left;
    struct Node* right;
}Node;

typedef Node* Tree;

Element_occur * create_element(char chara, int occurrences);
Element_occur * popMin(List * list);
Node * create_node(char chara, int haveChara, int occurrences, Node * left, Node * right);
int treeDeapth(Node * node);

#endif /* STRUCTURES_H */
