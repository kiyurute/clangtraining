#include <stdio.h>

int str_cmp(const char*, const char*);

int main(){
    char input1[] = "abcdef";
    char input2[] = "abcdef";

    int res = str_cmp(input1, input2);
    printf("res:%d\n", res);
    

}

int str_cmp(const char *str0, const char *str1){

    while ((*str0) != '\0' && (*str1) != '\0')
    {
        // printf("str0:%c\0",(*str0));
        // printf("str1:%c\0",(*str1));

        if((*str0) != (*str1)){
            return 1;
        }

        // if((*str0) == '\0' && (*str1) == '\0'){
        //     return 0;
        // }

        str0++;
        str1++;

    }

    if((*str0) == '\0' && (*str1) == '\0'){
            return 0;
    }

    return 1;

    


}
