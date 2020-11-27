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
