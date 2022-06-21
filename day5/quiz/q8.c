#include <stdio.h>
#include <stdlib.h>

typedef struct node {
  int key;
  int value;
  struct node *next;
} node_t;

typedef struct linked_list {
  node_t *front;
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

    struct node* head = NULL;
    struct node* second = NULL;
    struct node* third = NULL;

   
    // allocate 3 nodes in the heap
    head = (struct node*)malloc(sizeof(struct node));
    second = (struct node*)malloc(sizeof(struct node));
    third = (struct node*)malloc(sizeof(struct node));

    head->key = 1;
    head->value = 100;
    head->next = second;

    second->key = 2;
    second->value = 200;
    second->next = third;

    third->key = 3;
    third->value = 300;
    third->next = NULL;

    int i;
    
    // printf("%p\n",head->next);
    // printf("%p\n",second);
    // printf("%p\n",third);

    linked_list_t* list;
    list = (struct linked_list_t*)malloc(sizeof(linked_list_t));
    list->front = head;

    show(list);
    
    
    return 0;
}


void show(const linked_list_t* linked_list){

    node_t *node;
    node = linked_list->front;
    while(node -> next =! NULL){
        printf("%p\n", node);
        printf("%d\n", node -> key);
        printf("%d\n", node -> value);
        printf("%p\n", node -> next);

        node = node->next;
    }



};
