#include "input_output.h"

int* letter_to_binary(int letter)
{
    int* binary = (int*) malloc(8*sizeof(int));
    binary[0] = 0;
    for (int i = 7; i >= 1; i--)
    {
        binary[i] = letter%2;
        letter = letter/2;
    }
    return binary;
}

void print_in_file(char* p_file, int* binary)
{
    FILE* bin;
    bin = fopen(p_file, "w+");
    if (bin == NULL)
    {
        printf("Error in opening file.\n");
    }
    else
    {
        for (int i = 0; i < 8; i++)
        {
            fprintf(bin, "%d", binary[i]);
        }
    }
    fclose(bin);
}

void translation_file_to_binary(char* input_file, char* output_file)
{
    FILE *bin, *file;
    file = fopen(input_file, "r+");
    bin = fopen(output_file, "w+");
    char letters;
    if (file == NULL)
    {
        printf("Error in opening file\n");
    }
    else
    {
        while (!feof(file))
        {
            letters = fgetc(file);
            int letter_in_ascii = (int)letters;
            if (letter_in_ascii != -1)
            {
                int* binary = letter_to_binary(letter_in_ascii);
                print_in_file(bin, binary);
            }
        }

    }
    fclose(bin);
    fclose(file);
}



int nb_character_txt_file(char* txt_name)
{
    int count = 0;
    char letter;
    FILE *file;
    file = fopen(txt_name, "r");
    if (file == NULL)
    {
        printf("Error in opening file\n");
        return 0;
    }
    while(!feof(file))
    {
        letter = fgetc(file);
        count++;
    }
    fclose(file);
    return count-1; //Does not include spaces and returns.
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

// The function compresses a text file using a dico file.
// The function has as parameter size_max which represents the highest Huffman code size of a character.
// The function return nothing. It just creates a text file with the compressed text.
int translate_texte_with_huffman(int size_max){

    FILE* texte = fopen("texte.txt", "r"); // We open the file texte.txt
    FILE* code = fopen("dico.txt", "r"); // We open the file dico.txt
    FILE* encode_texte = fopen("compressed.txt", "w+"); // We create the file compressed.txt
    char letter = fgetc(texte); // We take the first character of the texte
    if (texte == NULL || code== NULL || encode_texte==NULL){
        return 0;
    }
    while (letter != EOF){ // While we are not at the end of the texte
        char* take_info = (char*)malloc((size_max+3)*sizeof(char)); // We create an array to contain the character and its Huffman code that we are looking for
        do{
            fgets(take_info, size_max+3, code); // We take a line of the code.txt to find the Huffman code of the character that we want
        }while(letter != take_info[0] && !(letter == '\n' && take_info[1] == 'n')); // the first character of the array contains the character of the Huffman code so we
        rewind(code);                                                               // check that the character of the array is what we are looking for. A security has been
                                                                                    // set for the particular case of the \n, two characters are used for the line break.
        int i = 1;
        if(letter == '\n'){ // If the character is a line break
            i = 2;
        }
        while(take_info[i] == '0' || take_info[i] == '1'){
            fprintf(encode_texte, "%c", take_info[i]); // We write the code as long as there are 0's and 1's in the array
            i++;
        }
        free(take_info); // We free the array
        letter = fgetc(texte); // We take the following letter
    }
    // We close the file
    fclose(code);
    fclose(texte);
    fclose(encode_texte);
    return 1;
}




int decompress_text_with_huffman(Tree huffmantree){
    FILE* encoded_texte = fopen("compressed.txt", "r");
    FILE* texte = fopen("decompressed.txt", "w+");
    if(encoded_texte == NULL){
        printf("Error in opening compressing file\n");
        fclose(encoded_texte);
        fclose(texte);
        return 0;
    }
    if(texte == NULL){
        printf("Error in opening decompressed file\n");
        fclose(encoded_texte);
        fclose(texte);
        return 0;
    }
    else{
        int number = 0;
        while(number!= EOF){
            Node* temp = huffmantree;
            while(temp->haveChara!=1 && number!=EOF){
                number=fgetc(encoded_texte);
                if(number == 49){
                    temp = temp->right;
                }
                if(number == 48){
                    temp = temp->left;
                }
            }
            fprintf(texte,"%c",temp->chara);
            temp = huffmantree;
        }
    }
    fclose(encoded_texte);
    fclose(texte);
    return 1;
}

int compress_file_with_huffman(){
    int question=0, verif=0;
    do{
    printf("Do you want to compress your file texte.txt ? (Enter 1 if yes, 0 if no)");
    scanf("%d",&question);
    }while(question !=1 && question !=0);
    if (question==1){
        Element_occur* El = list_occurence();
        Tree huffmantree = create_huffman_tree(&El);
        if (huffmantree== NULL){
            printf("Error to build the tree\n Compression failed");
            return 0;
        }
        createDico(huffmantree);
        verif=translate_texte_with_huffman(treeDeapth(huffmantree));
        if (verif==0){
            printf("Compression failed\n");
            return 0;
        }
        else{
            printf("Compression completed\n");
        }
        question=0;
        do{
        printf("Do you want to decompress it too ? (Enter 1 if yes, 0 if no)");
        scanf("%d",&question);
        }while(question !=1 && question !=0);
        if (question==1){
            verif=decompress_text_with_huffman(huffmantree);
            if (verif==0){
                printf("Decompression failed\n");
                return 0;
            }
            else{
                printf("Decompression completed\n");
            }
        }
    }
    return 1;
}
