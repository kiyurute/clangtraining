//server.cで使う関数をまとめたソースファイル

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>  
#include <unistd.h>   
#include <sys/select.h> 
#include <netdb.h>
#include <signal.h> 
#include <sys/ioctl.h>

//接続リストの構造体宣言
struct Node {
     int val;
     struct Node *next;   
 };

extern struct Node *head;

//現在登録されているfdを全て表示
void showallfds(fd_set *fs, int mxfd){
    int i;
    printf("showallfds---------------------------\n");
    for(i=0;i<mxfd + 1;i++){
        if(FD_ISSET(i,fs)){
            printf("%d exsits\n",i);
        }
    }
    printf("showallfdsfin------------------------\n");

}

//リンクリストを全て表示
void show_all_linklist(struct Node** head_ref){

    struct Node* node_address = *head_ref;

    printf("linklist-----------------------------\n");

    while(node_address != NULL){
        printf("address:%p\n", node_address);
        printf("fdval:%d\n", node_address->val);
        node_address = node_address->next;
    }

    printf("linklist fin--------------------------\n");

}

//リンクリストの末尾に追加
void push_back(struct Node** head_ref, int new_data){

    printf("node:%p\n", head_ref);
    printf("node*:%p\n", *head_ref);
    // printf("node&:%p\n", &head_ref);
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));

    struct Node* last = *head_ref;

    new_node -> next = NULL;
    new_node -> val = new_data;

    if(*head_ref == NULL){
        printf("this is a first connection\n");
        *head_ref = new_node;
        return;
    }


    while(last->next != NULL){
        last = last->next;
    }

    last -> next = new_node;
    return;

}

//リンクリストから指定の要素を削除
void drop_desval(struct Node** head_ref, int desval){

    struct Node* node_address = *head_ref;
    struct Node* pre_address = NULL;

    int counter = 0;


    while(node_address != NULL){
        // printf("address:%p\n",node_address);

        if(node_address->val == desval){
            if(counter == 0){
                *head_ref = node_address->next;
                printf("close:%d\n",close(node_address->val));
                return;
            }

            pre_address->next = node_address->next;
            printf("close:%d\n",close(node_address->val));
            free(node_address);
            return;
        }

        pre_address = node_address;
        node_address = node_address->next;

        counter += 1;
    }

}

//リンクリストを接続セットに反映
void copy_linklist_to_fs(struct Node **head_ref, fd_set *fs){

    struct Node* node_address = *head_ref;

    while(node_address != NULL){
        FD_SET(node_address->val, fs);
        node_address = node_address->next;
    }
}

//リンクリストを使ったブロードキャスト
void broadcast_with_linklist(struct Node **head_ref, char *mes){

    struct Node* node_address = *head_ref;

    while(node_address != NULL){
        send(node_address->val,mes,20,0);
        node_address = node_address->next;
    }

}

//sockのどれかにメッセージが来てるか確認する
//切断を検知したらリンクリストから削除
//戻り値はメッセージサイズ
int check_have_msg(struct Node **head_ref, char* mes){

    struct Node* node_address = *head_ref;
    int messize;

    while(node_address != NULL){

        messize = recv(node_address->val, mes, 20, 0); //0が接続なし -1が接続あるけどメッセージなし

        // printf("val:%d, messize:%d\n", node_address->val, messize);

        if(messize > 0){
            printf("find message:%s\n",mes);
            return messize;
        }else if(messize == 0){           //接続が切断された場合はリストから削除
            printf("detect discon\n");
            drop_desval(head_ref, node_address->val);
            return messize;
        }

        node_address = node_address -> next;

    }

    return messize;
    
}


