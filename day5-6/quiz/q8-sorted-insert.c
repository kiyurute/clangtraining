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
int sorted_insert(linked_list_t *linked_list, int key, int value);
// /* リンクリストのすべての要素を出力 */
void show(const linked_list_t *linked_list);
// /* リンクリストの要素をすべて解放 */
// void clear(linked_list_t *linked_list);

int main(){

    linked_list_t* list;
    list = (struct linked_list_t*)malloc(sizeof(linked_list_t));

    
    //空のリストで試すときはここから、ーーーーーーーーーーーーーーーーーーーー
    // node_t fifth = {5,500,NULL};
    // node_t fourth = {4,400,&fifth};
    // node_t third = {3,300,&fourth};
    // node_t second = {2,200,&third};
    // node_t first = {1,100,&second};
    // list->front = &first;
    //ここまでをコメントアウトーーーーーーーーーーーーーーーーーーーーーーーーー


    sorted_insert(list,3,550);
    show(list);
    
    return 0;
}



int sorted_insert(linked_list_t *linked_list, int key, int value){

    struct node* new_node = (struct node*) malloc(sizeof(struct node));

    new_node->key = key;
    new_node->value = value;
    new_node->next=NULL;

    node_t *last;

    if(linked_list->front == NULL){
        linked_list->front = new_node;
        return 0;
    }

    for(last = linked_list->front; last != NULL; last = last->next){
        // printf("key:%d\n",last->key);
        // printf("value:%d\n",last->value);
        // printf("next:%p\n",last->next);

        if(last->next->key >= key ){
            new_node->next=last->next;
            last->next=new_node;
            return 0;
        }

        if(last->next == NULL){
            last->next = new_node;
            return 0;
        }
        
    }


    return 0;

};


void show(const linked_list_t *linked_list){

    struct node* new_node = (struct node*) malloc(sizeof(struct node));

    node_t *last;

    for(last = linked_list->front; last != NULL; last = last->next){
        printf("key:%d\n",last->key);
        printf("value:%d\n",last->value);
        // printf("next:%p\n",last->next);

    }

    
};
