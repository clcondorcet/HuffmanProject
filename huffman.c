#include "huffman.h"

void translate_texte_with_huffman(){

    FILE* texte = fopen("texte.txt", "r");
    FILE* code = fopen("dico.txt", "r");
    FILE* encode_texte = fopen("compressed.txt", "w+");

    char letter = fgetc(texte);
    while (letter != EOF){

        char* take_info = (char*)malloc(12*sizeof(char));
        do{
            fgets(take_info, 12, code);
        }while(letter != take_info[0]);
        rewind(code);

        int i = 1;
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
