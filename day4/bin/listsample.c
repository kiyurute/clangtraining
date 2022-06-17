#include <stdio.h>
#define N 9
 
struct LIST {
    int data;  // 要素
    struct LIST *next; // 次のデータの場所（ポインタ）
} ;  // ここにもセミコロンあるよ！
 
void printList(struct LIST *p) {
    while(p != NULL) {
        printf("%d ",p->data);
        p = p->next; // 配列でいう i++ と同じ
    }
    printf("\n");
}
 
 
int main() {
    struct LIST p0,p1,p2,p3,p4,p5;
    struct LIST *top;
     
    p0.data = 75;
    p0.next = &p1;
 
    p1.data = 68;
    p1.next = &p2;  
     
    p2.data = 97;
    p2.next = &p3;
     
    p3.data = 43;
    p3.next = &p4;  
     
    p4.data = 55;
    p4.next = NULL;  
     
    top = &p0; // リストの先頭場所を代入 
     
    printList(top); // 75 68 97 43 55 
     
    // p2(97)とp3(43)の間に要素「50」を追加
    p5.data = 50;  
    p5.next = &p3; 
    p2.next = &p5;
    // 追加終了　要素数関係なしに3ステップで可能！
     
    printList(top); // 75 68 97 50 43 55 
     
    // p2 のデータを削除
    p1.next = p1.next->next;
    // 削除終了　要素数関係なしに2ステップで可能！
     
    printList(top); // 75 68 50 43 55 
     
    return 0;
}