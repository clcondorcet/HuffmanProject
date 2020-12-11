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

Node** add_two_array(Node** array, int size_array, int position_letter, char letter){
    size_array ++;
    Node** new_array = (Node**) malloc((size_array+1)*sizeof(Node*));
    Node* newNode = create_node(letter, 1, 1, NULL, NULL);
    int i = 0;
    for(i=0;i<position_letter;i++){
        new_array[i]=array[i];
    }
    new_array[position_letter]= newNode;
    for(i=position_letter;i<size_array;i++){
        new_array[i+1] = array[i];
    }
    free(array);
    return new_array;
}

Node** array_of_occurences(int * size){
    FILE* texte = fopen("texte.txt", "r");
    char letter = fgetc(texte);
    int size_array = 0, start=0, middle=0,end =0;
    Node** array= (Node**)malloc((1)*sizeof(Node*));
    while (letter != EOF){
        start=0;
        end = size_array-1;
        while (start <= end){
                middle = (start+end)/2;
                if (array[middle]->chara < letter){
                    start= middle+1;
                }

                else{
                    end = middle-1;
                }
        }

        if (size_array>0 && start<size_array &&  array[start]->chara == letter)
            array[start]->occurrences++;
        else{
            if(size_array==0 || end==-1 ||  array[end]->chara <= letter){
                array = add_two_array(array,size_array,start,letter);
                size_array++;
            }
        }
        letter = fgetc(texte);
    }
    *size = size_array;
    fclose(texte);
    return array;
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

int balance_factor(Node_newType* tree){
    if(tree == NULL){
        return 0;
    }
    else{
        return tree_depth_Node_newType(tree->right) - tree_depth_Node_newType(tree->left);
    }
}

void right_rotation(Node_newType** tree){
    if(*tree != NULL){
        Node_newType* temp = (*tree)->left;
        (*tree)->left = temp->right;
        temp->right = *tree;
        *tree = temp;
    }
}

void left_rotation(Node_newType** tree){
    if(*tree != NULL){
        Node_newType* temp = (*tree)->right;
        (*tree)->right = temp->left;
        temp->left = *tree;
        *tree = temp;
    }
}

void balance(Node_newType** tree){
    if (*tree != NULL){
        balance(&((*tree)->left));
        balance(&((*tree)->right));

        int bf = balance_factor(*tree);
        if(bf <= -2){//Left - ????
            if(balance_factor((*tree)->left) > 0){// Left - Right
                left_rotation(&((*tree)->left));
            }
            right_rotation(tree);// Left-Left
        }
        else if(bf >= 2){//Right - ????
            if(balance_factor((*tree)->right) < 0){// Right - Left
                right_rotation(&((*tree)->right));
            }
            left_rotation(tree);// Right-Right
        }
    }
}

void add_on_AVL(Node_newType** avl, Node_newType* node_for_AVL){
    if(*avl == NULL){
        *avl = node_for_AVL;
    }else{
        int a = (int)(node_for_AVL->data);
        int b = (int)((*avl)->data);
        if(a < b){
            avl = &((*avl)->left);
            add_on_AVL(avl, node_for_AVL);
        }else{
            avl = &((*avl)->right);
            add_on_AVL(avl, node_for_AVL);
        }
    }
}

void search_code_to_createAVL(Node* tree, char ** array, int size, Node_newType** avl){
    if(tree->haveChara == 0){
        int i = 0;
        while((*array)[i] != '\0'){
            i++;
        }
        char ** newArray1 = copyArray(array, size);
        (*newArray1)[i] = '1';
        char ** newArray2 = copyArray(array, size);
        (*newArray2)[i] = '0';
        search_code_to_createAVL(tree->right, newArray1, size, avl);
        search_code_to_createAVL(tree->left, newArray2, size, avl);
    }else{
        Node_newType* node_for_AVL = create_Node_newType(tree->chara, copyArray(array, size), NULL, NULL);
        add_on_AVL(avl, node_for_AVL);
        balance(avl);
    }
    free(*array);
    free(array);
}

Node_newType* create_the_new_dico(Node* tree, int deapth){
    Node_newType* avl = NULL;
    char ** chars = (char**) malloc(sizeof(char *));
    int i;
    *chars = (char*) malloc(deapth * sizeof(char));
    for(i = 0; i < deapth; i++){
        (*chars)[i] = '\0';
    }
    if(tree != NULL){
        search_code_to_createAVL(tree, chars, deapth, &avl);
    }
    return avl;
}
