#include <stdio.h>
#include <stdlib.h>
#include "huffman.h"
#include "structures.h"


int main(){
    int a;
    a=compress_file_with_huffman();
    if (a==0){
        printf("Please verify your files\n");
    }
    printf("Bye");
    return 0;
}
