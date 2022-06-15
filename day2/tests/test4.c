#include <stdio.h>

void calc(int, int, int*, int*, int*, int*, int*);

int main(){
    int n1, n2;
    int sum, diff, mul, div,mod;

    printf("1つ目の数字を入力：");
    scanf("%d", &n1);
    printf("2つ目の数字を入力：");
    scanf("%d", &n2);

    calc(n1, n2, &sum, &diff, &mul, &div, &mod);
    printf("sum:%i diff:%i mul:%i div:%i mod:%i\n",sum,diff,mul,div,mod);


}

void calc(int n1, int n2, int* sum, int* diff, int* mul, int* div, int* mod){
    *sum = n1 + n2;
    *diff = n1 - n2;
    *mul = n1*n2;
    *div = n1/n2;
    *mod = n1%n2;
}