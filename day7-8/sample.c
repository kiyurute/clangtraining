#include <stdio.h>

int func_x (int x){
    return x + 2;
}

int main(){

    int (*a)(int);
    a = func_x;
    printf("%d\n", a(3));

}