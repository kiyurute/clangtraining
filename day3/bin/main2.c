// ファイルの扱い
#include <stdio.h>
#include <stdlib.h>

#define SIZE 256

void main(){

    // FILE *file;

    // file = fopen("./f/foo.txt","w");
    // if(file == NULL){
    //     printf("ファイルがひらけません");
    //     exit(1);
    // }

    // fprintf(file, "Hello World.\r\n");
    // fprintf(file, "ABCDEF\r\n");
    // fclose(file);

    // ---------------------------------------------

    FILE *file;
    char line[SIZE];
    line[0] = '\0';
    file = fopen("./f/foo.txt","r");

    if(file == NULL){
        printf("ファイルがひらけません");
        exit(1);
    }

    while (fgets(line, SIZE, file) != NULL){
        printf("%s",line);
    }
    fclose(file);

}