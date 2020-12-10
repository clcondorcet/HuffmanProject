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