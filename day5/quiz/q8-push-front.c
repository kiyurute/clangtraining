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
int push_front(linked_list_t *linked_list, int key, int value);
// /* リンクリストの一番後ろを削除 */
// void pop_back(linked_list_t *linked_list);
// /* リンクリストの一番先頭を削除 */
// void pop_front(linked_list_t *linked_list);
// /* リンクリストに、keyでソートされた位置（昇順）に追加 */
// int sorted_insert(linked_list_t *linked_list, int key, int value);
// /* リンクリストのすべての要素を出力 */
// void show(const linked_list_t *linked_list);
// /* リンクリストの要素をすべて解放 */
// void clear(linked_list_t *linked_list);

int main(){

    struct node* head = NULL;

   
    // nodes in the heap
    head = (struct node*)malloc(sizeof(struct node));

    head->key = 1;
    head->value = 100;
    head->next = NULL;
    
    // printf("%p\n",head->next);
    // printf("%p\n",second);
    // printf("%p\n",third);

    linked_list_t* list;
    list = (struct linked_list_t*)malloc(sizeof(linked_list_t));
    list->front = head;

    push_front(list,0,000);

    printf("%d\n",list->front->key);
    printf("%d\n",list->front->value);
    printf("%p\n",list->front->next);

  
    printf("%d\n",(list->front->next)->key);
    printf("%d\n",(list->front->next)->value);
    printf("%d\n",(list->front->next)->next);
    
    return 0;
}



int push_front(linked_list_t* linked_list, int key, int value){

    struct node* new_node = (struct node*)malloc(sizeof(struct node));

    new_node->key = key;
    new_node->value = value;
    new_node->next = linked_list->front;
    linked_list->front = new_node;

};
