#include <stdio.h>
#include <stdlib.h>

typedef struct node {
  int key;
  int value;
  struct node *next;
} node_t;

typedef struct linked_list {
  node_t *front;  //nodet型のアドレス
} linked_list_t;


// /* リンクリストの一番最後に追加 */
// int push_back(linked_list_t *linked_list, int key, int value);
// /* リンクリストの一番先頭に追加 */
// int push_front(linked_list_t *linked_list, int key, int value);
// /* リンクリストの一番後ろを削除 */
void pop_back(linked_list_t *linked_list);
// /* リンクリストの一番先頭を削除 */
// void pop_front(linked_list_t *linked_list);
// /* リンクリストに、keyでソートされた位置（昇順）に追加 */
// int sorted_insert(linked_list_t *linked_list, int key, int value);
// /* リンクリストのすべての要素を出力 */
void show(const linked_list_t *linked_list);
// /* リンクリストの要素をすべて解放 */
// void clear(linked_list_t *linked_list);

int main(){

    linked_list_t* list;
    list = (struct linked_list_t*)malloc(sizeof(linked_list_t));

    
    //空のリストで試すときはここから、ーーーーーーーーーーーーーーーーーーーー
    // node_t sixth = {6,600,NULL};
    node_t *third;
    node_t *second;
    node_t *first;

    third = (node_t*)malloc(sizeof(node_t));
    third->key = 3;
    third->value = 300;
    third->next = NULL;

    second = (node_t*)malloc(sizeof(node_t));
    second->key = 2;
    second->value = 200;
    second->next = third;

    first = (node_t*)malloc(sizeof(node_t));
    first->key = 1;
    first->value = 100;
    first->next = second;

    list->front = first;


    pop_back(list);
    show(list);
    
    return 0;
}



void pop_back(linked_list_t *linked_list){

    node_t *last;
    last = (struct node_t*)malloc(sizeof(node_t));

    for(last = linked_list->front; last != NULL; last = last->next){

        if((last->next)->next == NULL){ 
            free(last->next);   //<-できない
            last->next = NULL;  //<-できる
            
        }

    }

};


void show(const linked_list_t *linked_list){


    node_t *last;

    printf("======================\n");
    for(last = linked_list->front; last != NULL; last = last->next){
        printf("key:%d value:%d\n",last->key, last->value);
        // printf("next:%p\n",last->next);

    }

};
