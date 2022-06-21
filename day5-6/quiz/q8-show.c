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
// void pop_back(linked_list_t *linked_list);
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
    printf("list:%p\n",list);

    
    node_t fifth = {5,500,NULL};
    node_t fourth = {4,400,&fifth};
    node_t third = {3,300,&fourth};
    node_t second = {2,200,&third};
    node_t first = {1,100,&second};


    list->front = &first;

    printf("head:%p\n",&first);
    printf("front:%p\n",list->front);


    show(list);

    // printf("%d\n",list->front->key);
    // printf("%d\n",list->front->value);
    // printf("%p\n",list->front->next);

  
    // printf("%d\n",(list->front->next)->key);
    // printf("%d\n",(list->front->next)->value);
    // printf("%d\n",(list->front->next)->next);
    
    return 0;
}



void show(const linked_list_t *linked_list){

    printf("in func:%p\n", linked_list->front);

    // struct node* new_node = (struct node*) malloc(sizeof(struct node));

    node_t *last;

    for(last = linked_list->front; last != NULL; last = last->next){
        printf("key:%d\n",last->key);
        printf("value:%d\n",last->value);
        printf("next:%p\n",last->next);

    }

    
};
