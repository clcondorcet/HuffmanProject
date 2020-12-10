#define _CRT_SECURE_NO_DEPRECATE
#include "huffman.h"

Tree create_huffman_tree(List * occurrencesList){
    if(occurrencesList != NULL){
        Element * leftE = popMin(occurrencesList);
        Node * left = create_node(leftE->chara, 1, leftE->occurrences, NULL, NULL);
        Element * rightE = popMin(occurrencesList);
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

void printDico(Node * tree, FILE * file, char * chars){
    if(tree->haveChara){
        if(tree->chara == '\n'){
            fprintf(file, "%c%c", '\\', 'n');
        }else{
            fprintf(file, "%c", tree->chara);
        }
        int i = 0;
        while(chars[i] != '\0'){
            fprintf(file, "%c", chars[i]);
            i++;
        }
        fprintf(file, "%c", '\n');
    }else{
        int i = 0;
        while(chars[i] != '\0'){
            i++;
        }
        chars[i] = '0';
        printDico(tree->left, file, chars);
        chars[i] = '1';
        printDico(tree->right, file, chars);
        chars[i] = '\0';
    }
}

int createDico(Tree huffmanTree){
    FILE * file = fopen("dico.txt", "w+");
    if(file == NULL){
        printf("Error in opening file\n");
        fclose(file);
        return 0;
    }
    int deapth = treeDeapth(huffmanTree);
    char * chars = (char*) malloc(deapth * sizeof(char));
    int i;
    for(i = 0; i < deapth; i++){
        chars[i] = '\0';
    }
    printDico(huffmanTree, file, chars);
    fclose(file);
    free(chars);
    return 1;
}

char ** copyArray(char ** array, int size){
    char ** chars = (char**) malloc(sizeof(char *));
    int i;
    *chars = (char*) malloc(size * sizeof(char));
    for(i = 0; i < size; i++){
        (*chars)[i] = (*array)[i];
    }
    return chars;
}

int createDicoOptimised(Tree huffmanTree){
    FILE * file = fopen("dico.txt", "w+");
    if(file == NULL){
        printf("Error in opening file\n");
        fclose(file);
        return 0;
    }
    int deapth = treeDeapth(huffmanTree);
    char * chars = (char*) malloc(deapth * sizeof(char));
    int i;
    for(i = 0; i < deapth; i++){
        chars[i] = '\0';
    }
    Queue * nodeQueue = create_queue();
    QueueChar * charQueue = create_queueChar();
    enqueue(nodeQueue, huffmanTree);
    enqueueChar(charQueue, copyArray(&chars, deapth));
    free(chars);
    while(!is_empty(nodeQueue)){
        Node * node = dequeue(nodeQueue);
        char ** byteCode = dequeueChar(charQueue);
        if(node->haveChara){
            if(node->chara == '\n'){
                fprintf(file, "%c%c", '\\', 'n');
            }else{
                fprintf(file, "%c", node->chara);
            }
            int i = 0;
            while((*byteCode)[i] != '\0'){
                fprintf(file, "%c", (*byteCode)[i]);
                i++;
            }
            fprintf(file, "%c", '\n');
        }else{
            enqueue(nodeQueue, node->left);
            char ** newChar = copyArray(byteCode, deapth);
            i = 0;
            while((*newChar)[i] != '\0'){
                i++;
            }
            (*newChar)[i] = '0';
            enqueueChar(charQueue, newChar);
            enqueue(nodeQueue, node->right);
            char ** newChar2 = copyArray(byteCode, deapth);
            (*newChar2)[i] = '1';
            enqueueChar(charQueue, newChar2);
        }
        free(*byteCode);
        free(byteCode);
    }
    free(nodeQueue);
    free(charQueue);
    fclose(file);
    return 1;
}

void translate_texte_with_huffman(){

    FILE* texte = fopen("texte.txt", "r");
    FILE* code = fopen("dico.txt", "r");
    FILE* encode_texte = fopen("compressed.txt", "w+");

    char letter = fgetc(texte);
    while (letter != EOF){

        char* take_info = (char*)malloc(12*sizeof(char));
        do{
            fgets(take_info, 12, code);
        }while(letter != take_info[0] && !(letter == '\n' && take_info[1] == 'n'));
        rewind(code);

        int i = 1;
        if(letter == '\n'){
            i = 2;
        }
        while(take_info[i] == '0' || take_info[i] == '1'){
            fprintf(encode_texte, "%c", take_info[i]);
            i++;
        }
        free(take_info);
        letter = fgetc(texte);
    }

    fclose(code);
    fclose(texte);
    fclose(encode_texte);
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
