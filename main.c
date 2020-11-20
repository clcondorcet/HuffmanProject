#include <stdio.h>
#include <stdlib.h>
/*
int* letter_to_binary(int letter)
{
    int* binary = (int*)malloc(8*sizeof(int));
    for (int i = 7; i >= 0; i--)
    {
        printf("%d", letter);
        binary[i] = letter%2;
        letter = letter/2;
    }
    return binary;
}

void print_in_file(FILE* bin, int* binary)
{
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

void translation_file_to_binary()
{
    FILE* file;
    FILE* bin;
    file = fopen("letter_version.txt", "r");
    bin = fopen("binary_version.txt", "w+");
    char letter;
    if (file == NULL)
    {
        printf("Error in opening file\n");
        exit(0);
        fclose(bin);
        fclose(file);
    }
    else
    {
        while (!feof(file))
        {
            letter = fgetc(file);
            int letter_in_ascii = (int)letter;
            if(letter_in_ascii != -1){
                int* binary = letter_to_binary(letter_in_ascii);
                print_in_file(bin, binary);
            }
        }

    }
    fclose(bin);
    fclose(file);
}
*/

void translate_texte_with_huffman(FILE* file, Clementstruct* hlist) // le file du texte et la liste avec la traduction Huffman
{
    FILE* bin = fopen("Huffman_version.txt", "w+");
    char letter;
    Clementstruct* temp;
    Element* hbit;
    while (!feof(file)){
        temp = hlist;
        letter = fgetc(file);
        while(temp != NULL || temp->data != letter){
            temp = temp->next
        }
        hbit = temp->binary
        while(hbit!=NULL){
            fprintf(bin, "%d", hbit->data);
            hbit = hbit->next;
        }
    }
    fclose(bin);
    fclose(file);
}


int main()
{
    return 0;
}
