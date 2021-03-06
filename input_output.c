#include "input_output.h"
#include <time.h>

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

void print_in_file(FILE * bin, int* binary){
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

// The function compresses a text file using a dico file.
// The function has as parameter size_max which represents the highest Huffman code size of a character.
// The function return nothing. It just creates a text file with the compressed text.
void translate_texte_with_huffman(int size_max){

    FILE* texte = fopen("texte.txt", "r"); // We open the file texte.txt
    FILE* code = fopen("dico.txt", "r"); // We open the file dico.txt
    FILE* encode_texte = fopen("compressed.txt", "w+"); // We create the file compressed.txt
    char letter = fgetc(texte); // We take the first character of the texte
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
}

void translate_texte_with_avl(Node_newType * avl, int size_max){
    FILE* texte = fopen("texte.txt", "r");
    if(texte == NULL){
        printf("Error in opening file\n");
        fclose(texte);
        return;
    }
    FILE* encode_texte = fopen("compressed.txt", "w+");
    if(encode_texte == NULL){
        printf("Error in opening file\n");
        fclose(encode_texte);
        return;
    }
    char letter = fgetc(texte);
    while (letter != EOF){
        Node_newType * temp = avl;
        while(temp->data != letter){
            if((int)temp->data > (int) letter){
                temp = temp->left;
            }else{
                temp = temp->right;
            }
        }
        fprintf(encode_texte, "%s", *(temp->l));
        letter = fgetc(texte);
    }
    fclose(texte);
    fclose(encode_texte);
}

void decompress_text_with_huffman(Tree huffmantree){
    FILE* encoded_texte = fopen("compressed.txt", "r");
    FILE* texte = fopen("decompressed.txt", "w+");
    if(encoded_texte == NULL){
        printf("Error in opening file\n");
        fclose(encoded_texte);
        fclose(texte);
        return;
    }
    if(texte == NULL){
        printf("Error in opening file\n");
        fclose(encoded_texte);
        fclose(texte);
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
    printf("Decompression performed\n");
}

char ** addChar(char ** array, int newSize, char newLetter){
    char ** chars = (char**) malloc(sizeof(char *));
    int i;
    *chars = (char*) malloc(newSize * sizeof(char));
    for(i = 0; i < newSize-1; i++){
        (*chars)[i] = (*array)[i];
    }
    (*chars)[newSize-1] = newLetter;
    free(*array);
    free(array);
    return chars;
}

Tree huffman_from_dico(){
    FILE* dico = fopen("dico.txt", "r");
    if(dico == NULL){
        printf("Error in opening file\n");
        fclose(dico);
        exit(0);
    }
    char letter = fgetc(dico);
    char current = '\0';
    Node * huffmanTree= create_node(' ', 0, 1, NULL, NULL);
    Node * temp = huffmanTree;
    while(letter != EOF){
        if(letter == '\n'){
            temp->haveChara = 1;
            temp->chara = current;
            current = '\0';
            temp = huffmanTree;
            letter = fgetc(dico);
        }else{
            if(current == '\0'){
                if(letter == '\\'){
                    letter = fgetc(dico);
                    if(letter == 'n'){
                        current = '\n';
                        letter = fgetc(dico);
                    }else{
                        current = '\\';
                    }
                }else{
                    current = letter;
                    letter = fgetc(dico);
                }
            }
            if(letter == '0'){
                if(temp->left == NULL){
                    temp->left = create_node(' ', 0, 1, NULL, NULL);
                }
                temp = temp->left;
            }else{
                if(temp->right == NULL){
                    temp->right = create_node(' ', 0, 1, NULL, NULL);
                }
                temp = temp->right;
            }
            letter = fgetc(dico);
        }
    }
    return huffmanTree;
}

void compress_file_with_huffman(){
    int question=0;
    do{
    printf("Do you want to compress your file texte.txt ? (Enter 1 if yes, 0 if no)");
    scanf("%d",&question);
    }while(question !=1 && question !=0);
    if (question==1){
        clock_t t;
        t = clock();
        int size;
        Node ** arrayOccurences = array_of_occurences(&size);
        if (arrayOccurences == NULL){
            return;
        }
        Tree huffmanTree = create_huffman_tree_Optimised(arrayOccurences, size);
        if (huffmanTree == NULL){
            printf("Error to build the tree\n Compression failed");
            return;
        }
        createDicoOptimised(huffmanTree);
        Node_newType * avl = create_the_new_dico(huffmanTree, treeDeapth(huffmanTree));
        translate_texte_with_avl(avl, treeDeapth(huffmanTree));
        question=0;
        t = clock() - t;
        double time_taken = ((double)t)/CLOCKS_PER_SEC;
        printf(" Took %f seconds to execute \n", time_taken);
        printf("Your compress has suceeded\nDo you want to decompress it too ? (Enter 1 if yes, 0 if no)");
        scanf("%d",&question);
        if (question==1){
            Tree newHuffmanTree = huffman_from_dico();
            decompress_text_with_huffman(newHuffmanTree);
        }
    }
    printf("Bye");
}
