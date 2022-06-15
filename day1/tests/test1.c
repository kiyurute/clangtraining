#include <stdio.h>

int main(){

    int num[10];
    int even[10];
    int odd[10];
    int i;

    for(i=0; i<10; i++){
        printf("%dこ目の数字を入力してください。",i+1);
        scanf("%d",&num[i]);
    }

    printf("%s","偶数:");

    for(i=0; i<10; i++){
        if(num[i] %2 == 0){
            printf("%d",num[i]);
            printf("%s"," ");
        }
    }

    printf("\n");
    printf("%s","奇数:");


    for(i=0; i<10; i++){
        if(!(num[i] %2 == 0)){
            printf("%d",num[i]);
            printf("%s"," ");
        }
    
    }

    printf("\n");

    
    

    

    
    
}