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


/* リンクリストの一番最後に追加 */
int push_back(linked_list_t *linked_list, int key, int value);
/* リンクリストの一番先頭に追加 */
int push_front(linked_list_t *linked_list, int key, int value);
/* リンクリストの一番後ろを削除 */
void pop_back(linked_list_t *linked_list);
/* リンクリストの一番先頭を削除 */
void pop_front(linked_list_t *linked_list);
/* リンクリストに、keyでソートされた位置（昇順）に追加 */
int sorted_insert(linked_list_t *linked_list, int key, int value);
/* リンクリストのすべての要素を出力 */
void show(const linked_list_t *linked_list);
/* リンクリストの要素をすべて解放 */
void clear(linked_list_t *linked_list);

int main(void)
{
  linked_list_t linked_list = { NULL };

  push_back(&linked_list, 3, 4);
  show(&linked_list);
  push_back(&linked_list, 2, 10);
  show(&linked_list);
  push_back(&linked_list, 5, 20);
  show(&linked_list);
  push_back(&linked_list, 1, 0);
  show(&linked_list);
  push_back(&linked_list, -1, -100);
  show(&linked_list);

  pop_front(&linked_list);
  show(&linked_list);
  pop_front(&linked_list);
  show(&linked_list);
  pop_front(&linked_list);
  show(&linked_list);
  pop_front(&linked_list);
  show(&linked_list);
  pop_front(&linked_list);
  show(&linked_list);

  clear(&linked_list);

  push_front(&linked_list, 30, 12);
  show(&linked_list);
  push_front(&linked_list, 100, 120);
  show(&linked_list);
  push_front(&linked_list, 3, 2);
  show(&linked_list);
  push_front(&linked_list, -100, 1000);
  show(&linked_list);

  pop_back(&linked_list);
  show(&linked_list);
  pop_back(&linked_list);
  show(&linked_list);
  pop_back(&linked_list);
  show(&linked_list);
  pop_back(&linked_list);
  show(&linked_list);
  pop_back(&linked_list);
  show(&linked_list);

  clear(&linked_list);

  sorted_insert(&linked_list, 1, 1);
  show(&linked_list);
  sorted_insert(&linked_list, 2, 2);
  show(&linked_list);
  sorted_insert(&linked_list, 3, 3);
  show(&linked_list);
  sorted_insert(&linked_list, 4, 4);
  show(&linked_list);
  sorted_insert(&linked_list, 4, -4);
  show(&linked_list);
  sorted_insert(&linked_list, 1, -1);
  show(&linked_list);
  sorted_insert(&linked_list, 2, -2);
  show(&linked_list);

  clear(&linked_list);

  sorted_insert(&linked_list, 99, 199);
  sorted_insert(&linked_list, 32, -32);
  sorted_insert(&linked_list, 1000, 10);
  sorted_insert(&linked_list, 2, 22);
  sorted_insert(&linked_list, 50, 0);
  sorted_insert(&linked_list, 23, 100);
  sorted_insert(&linked_list, 490, 99);
  show(&linked_list);

  return 0;
}


int push_back(linked_list_t *linked_list, int key, int value){

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
        if(last->next == NULL){
            
            last->next=new_node;
            break;
        }
        
    }

    return 0;


};

int push_front(linked_list_t* linked_list, int key, int value){
    printf("in push_front\n");

    struct node* new_node = (struct node*)malloc(sizeof(struct node));

    new_node->key = key;
    new_node->value = value;
    new_node->next = linked_list->front;
    linked_list->front = new_node;

};

void pop_back(linked_list_t *linked_list){
    printf("in pop_back\n");

    node_t *last;
    last = (struct node_t*)malloc(sizeof(node_t));

    if(linked_list->front != NULL && linked_list->front->next != NULL){

        for(last = linked_list->front; last != NULL; last = last->next){

        if((last->next)->next == NULL){ 
            free(last->next);   //<-できない
            last->next = NULL;  //<-できる
            
        }

        }

    }else if(linked_list->front != NULL && linked_list->front->next == NULL){
        free(linked_list->front);
        linked_list->front = NULL;
    }


};

void pop_front(linked_list_t *linked_list){
    printf("in pop_front\n");

    if(linked_list->front != NULL){
        node_t *tmp = linked_list -> front;
        linked_list -> front = linked_list->front->next;  
        free(tmp);    
    }


};

int sorted_insert(linked_list_t *linked_list, int key, int value){

    struct node* new_node = (struct node*) malloc(sizeof(struct node));

    new_node->key = key;
    new_node->value = value;
    new_node->next=NULL;


    if(linked_list->front == NULL){  //一個もない時
        linked_list->front = new_node;
        return 0;
    }else if(linked_list->front->next == NULL){  //一個しかない時
        if(new_node->key > linked_list->front->key){
            linked_list->front->next = new_node;
        }else{
            new_node->next = linked_list->front;
            linked_list->front = new_node;
        }
        return 0;
    }else{

        node_t *last;
        node_t *prev_node = linked_list->front;


        for(last = linked_list->front->next; last != NULL; last = last->next){

        // printf("value:%d\n",last->value);
        // printf("next:%p\n",last->next);
       
        if(prev_node->key >= new_node->key){
            new_node->next = linked_list->front;
            linked_list->front = new_node;
            return 0;
        }

        if(prev_node < new_node->key && new_node->key <= last->key){
            new_node->next = last;
            prev_node->next = new_node;
            return 0;
        }

        if(last->key >= new_node->key ){
            new_node->next = last;
            prev_node->next = new_node;

            return 0;
        }

        prev_node = last;

        if(last->next == NULL){
            last->next = new_node;
            return 0;
        }

        }

    }

    return 0;

};

void clear(linked_list_t *linked_list){

    // node_t *last;
    // for(last = linked_list->front; last != NULL; last = last->next){
    //     // printf("key:%d\n",last->key);
    //     // printf("value:%d\n",last->value);
    //     printf("next:%p\n",last);
    //     free(last);
        
    // }

    linked_list->front = NULL;


};

void show(const linked_list_t *linked_list){

    node_t *last;

    printf("======================\n");
    for(last = linked_list->front; last != NULL; last = last->next){
        printf("key:%d value:%d\n",last->key, last->value);
        // printf("next:%p\n",last->next);

    }

};