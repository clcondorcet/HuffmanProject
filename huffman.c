#define _CRT_SECURE_NO_DEPRECATE
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

void selection_sort(Node ** array, int size){
    int min, i, y;
    for(i = 0; i < size-1; i++){
        min = i;
        for(y = i + 1; y < size; y++){
            if(array[y]->occurrences < array[min]->occurrences){
                min = y;
            }
        }
        if(min != i){
            Node * temp = array[min];
            array[min] = array[i];
            array[i] = temp;
        }
    }
}

void printList(Node ** array, int size){
    for(int i = 0; i < size; i++){
        if(array[i]->haveChara){
            printf("%c%d ", array[i]->chara ,array[i]->occurrences);
        }else{
            printf("%d ", array[i]->occurrences);
        }
    }
}

Node * getMin(Queue * sourceQueue, Queue * newNodeQueue){
    Node * toAdd = front(sourceQueue);
    if(toAdd == NULL){
        return dequeue(newNodeQueue);
    }else{
        Node * other = front(newNodeQueue);
        if(other != NULL && other->occurrences < toAdd->occurrences){
            return dequeue(newNodeQueue);
        }
    }
    return dequeue(sourceQueue);
}

Tree create_huffman_tree_Optimised(Node ** arrayNodes, int size){
    selection_sort(arrayNodes, size);
    Queue * sourceQueue = create_queue(); // <- arrayOfNodes
    Queue * newNodeQueue = create_queue(); // <- array of new nodes (without characters)
    int i;
    for(i = 0; i < size; i++){
        enqueue(sourceQueue, arrayNodes[i]);
    }
    while(!is_empty(sourceQueue) || !is_empty(newNodeQueue)){
        Node * left = getMin(sourceQueue, newNodeQueue);
        Node * right = getMin(sourceQueue, newNodeQueue);
        int sum = left->occurrences;
        if(right != NULL){
            sum += right->occurrences;
        }else{
            free(sourceQueue);
            free(newNodeQueue);
            return left;
        }
        Node * newNode = create_node(' ', 0, sum, left, right);
        enqueue(newNodeQueue, newNode);
    }
    printf("If you see this, the dev is not good.");
    free(sourceQueue);
    free(newNodeQueue);
    return NULL; // Should not be call.
}

