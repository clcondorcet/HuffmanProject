#include "huffman.h"


Element_occur* list_occurence(){

    List head = NULL;
    List current = NULL;
    List new_node = NULL;


    FILE* ptr = fopen("texte.txt", "r");

    if (ptr == NULL){
        printf("error");
        return 0;
    }

    int ch;
    int char_found;

    while ( (ch = fgetc(ptr)) != EOF )
    {
        current = head;
        char_found = 0;
        while ((current != NULL) && (!char_found)){
            if (current->chara == ch){
                current->occurrences++;
                char_found = 1;
            }
            current = current->next;
        }
        if (!char_found){
            new_node = create_element(ch,1);
            new_node->next = head;
            head = new_node;
        }
    }
    fclose(ptr);
    return head;
}

Tree create_huffman_tree(List * occurrencesList){
    if(occurrencesList != NULL){
        Element_occur * leftE = popMin(occurrencesList);
        Node * left = create_node(leftE->chara, 1, leftE->occurrences, NULL, NULL);
        Element_occur * rightE = popMin(occurrencesList);
        Node * right = NULL;
        int occurrences = leftE->occurrences;
        free(leftE);
        if(rightE != NULL){
            right =  create_node(rightE->chara, 1, rightE->occurrences, NULL, NULL);
            occurrences += rightE->occurrences;
            free(rightE);
        }
        Node * tree = create_node(' ', 0, occurrences, left, right);
        while(*occurrencesList != NULL){
            leftE = popMin(occurrencesList);
            left = create_node(leftE->chara, 1, leftE->occurrences, NULL, NULL);
            free(leftE);
            tree = create_node(' ', 0, left->occurrences + tree->occurrences, left, tree);
        }
        return tree;
    }else{
        return NULL;
    }
}
