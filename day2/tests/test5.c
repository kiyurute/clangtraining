//ほぼ武樋さんの手助け


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *str_chr(const char*, int);
;

int main(){
    char str[256];
    char c;
    int len;

    printf("文字を入力：");
    scanf("%c", &c);

    printf("文字列を入力：");
    scanf("%s", str);


    // printf("%c",str[]);

    // printf("%d\n", len);

    char* res = str_chr(str,c);
    printf("%p\n",res);
    
}

char *str_chr(const char *str, int c){
    printf("str : %s\n", str);
    printf("c : %c\n", c);
    int len = strlen(str);

    int i;

    for(i=0;i<len;i++){
        printf("%c\n", *(str+i));
        if(str[i] == c){
            return &str[i];
        }
    }

    return NULL;

    

}