#include <stdio.h>

int calcavg(int num1,int num2){
    int avg = (num1 + num2) /2;
    return avg;
}

int main(){

    while(1){
        int num1, num2, avgval;

        printf("%s\n","1つ目の値を入力してください。");
        scanf("%d",&num1);

        printf("%s\n","2つ目の値を入力してください。");
        scanf("%d",&num2);

        avgval = calcavg(num1,num2);

        printf("%s","平均値は");
        printf("%d",avgval);
        printf("%s","です。");
        printf("%s","\n##########################\n");


    }

    
}