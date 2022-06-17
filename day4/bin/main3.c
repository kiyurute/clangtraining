#include <stdio.h>

int main(int argc, char *argv[]){
    if(argc > 3){
        printf("%s\n", argv[0]);
        printf("%s\n", argv[1]);
        printf("%s\n", argv[2]);
        printf("%s\n", argv[3]);
        printf("%s\n", (*argv + 2));

    }


}
