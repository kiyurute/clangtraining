#include <stdio.h>
#include <stdlib.h>

int main(){
    
    int *a;

    a = malloc(sizeof(int) * 3);

    printf("%p\n",a);

    int i = 0;
    for(i=0; i<100; i++){
        *(a+i) = i * 100;
        printf("%d\n",*(a+i));
    }
    printf("%d,i");
    printf("%p\n",(a+i));


    if(a == NULL){
        printf("failed\n");
    }else{
        free(a);
    }

    // int i = 10;
    // int *ip = &i;
    // void *vp;

    // vp = ip;
    // printf("%p\n", vp);
    // printf("%p\n", ip);

    // printf("%d\n", *(int *)vp);
    // printf("%d\n", *ip);



}