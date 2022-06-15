#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>

void show(int, int, int);
void swap(int*, int*);

int main(){
    // int a, b,c;
    // srand((unsigned)time(NULL));

    // a = rand() % 10 + 1; //1~10の乱数

    // rand() % n + 1 //1からんnでの乱数を数える方法
    // rand() % (n+1) //0からnまでの乱数を数える方法

    // double t = tan(2*3.14);


    // int a = 100;
    // double b = 123.4;
    // float c = 123.4f;
    // char d = 'a';
    // printf("aの値は%d, 大きさは%dbyte、アドレスは0x%x\n", a, sizeof(int), &a);
    // printf("bの値は%d, 大きさは%dbyte、アドレスは0x%x\n", a, sizeof(double), &b);
    // printf("cの値は%d, 大きさは%dbyte、アドレスは0x%x\n", a, sizeof(float), &c);
    // printf("dの値は%d, 大きさは%dbyte、アドレスは0x%x\n", a, sizeof(char), &d);

    // int a = 100;   
    // int b = 200;
    // int *p = NULL;
    // p = &a;    //pにaのアドレスを代入
    // show(a, b, *p);
    // *p = 300;  //*pに値を代入
    // show(a, b, *p);
    // p = &b;    //pにbのアドレスを代入
    // show(a, b, *p);
    // *p = 400;  //pに値を代入
    // show(a, b, *p);

    // -------------------------------------------

    // int a = 1, b = 2;

    // printf("a = %d b = %d\n", a, b);
    // swap(&a, &b);
    // printf("a = %d b = %d\n", a, b);

    // --------------------------------------------------


    // double d[3] = {0.2, 0.4, 0.6};
    // double *p1 = NULL, *p2 = NULL;

    // int i;

    // p1 = d;
    // p2 = d;

    // for (i = 0; i < 3; i++){
    //     printf("%f %f %f\n", *(d+i), p1[i], *p2);
    //     p2++;

    // }

    //------------------------------------------------

    char s[10];
    int len;

    strcpy(s, "ABC");
    printf("s=%s\n",s);
    strcat(s,"DEF");
    printf("s=%s\n",s);
    len = strlen(s);
    printf("文字列の長さ:%d\n",len);



}

void show(int n1, int n2, int n3){
    printf("a = %d b = %d *p = %d\n", n1, n2, n3);
}

void swap(int* num1, int* num2){
    int temp = *num1;
    *num1 = *num2;
    *num2 = temp;
}
