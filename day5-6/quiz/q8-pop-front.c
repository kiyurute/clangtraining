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
void pop_front(linked_list_t *linked_list);
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
    node_t sixth = {6,600,NULL};
    node_t fifth = {5,500,&sixth};
    node_t fourth = {4,400,&fifth};
    node_t third = {3,300,&fourth};
    node_t second = {2,200,&third};
    node_t first = {1,100,&second};
    list->front = &first;
    //ここまでをコメントアウトーーーーーーーーーーーーーーーーーーーーーーーーー


    pop_front(list);
    show(list);
    
    return 0;
}



void pop_front(linked_list_t *linked_list){

    if(linked_list->front != NULL){
        free(linked_list->front);
        linked_list -> front = linked_list->front->next;      
    }


};


void show(const linked_list_t *linked_list){

    struct node* new_node = (struct node*) malloc(sizeof(struct node));

    node_t *last;

    for(last = linked_list->front; last != NULL; last = last->next){
        printf("key:%d\n",last->key);
        printf("value:%d\n",last->value);
        printf("next:%p\n",last->next);

    }

    
};
