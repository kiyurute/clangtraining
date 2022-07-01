#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>  
#include <unistd.h>   
#include <sys/select.h> 

void showallfds(fd_set*);
void addconlist(int *, int);
void conlisttoset(int *, fd_set*);
void showconlist(int *);
void broadcast(int*, char*);
void resetarr(int*);
void rmfromarr(int*, int);


struct Node {
     int key;
     int val;
     struct Node *next;   
 };

 void push_back(struct Node**, int);
 void show_all_linklist(struct Node**);
 void drop_desval(struct Node**, int);
 void copy_linklist_to_fs(struct Node**, fd_set*);
 void broadcast_with_linklist(struct Node**, char*);

int
main()
{
 int sock0;
 struct sockaddr_in client;
 socklen_t len; 
 struct sockaddr_in addr;
 int sock;

 struct Node *head = NULL;

 //select
 //int inputfd = 0; //標準入力用のfd
 fd_set rfds; //読み込みが可能になるfdのセット
 FD_ZERO(&rfds);
 int mxfd = -1;

 /* ソケットの作成 */
 sock0 = socket(AF_INET, SOCK_STREAM, 0);
 printf("created socket:%d\n", sock0);

 
 /* ソケットの設定 */
 addr.sin_family = AF_INET;
 addr.sin_port = htons(12345);
 addr.sin_addr.s_addr = INADDR_ANY;

 bind(sock0, (struct sockaddr *)&addr, sizeof(addr));

 /* TCPクライアントからの接続要求を待てる状態にする */
 listen(sock0, 5);
//  FD_SET(sock0, &rfds);
 mxfd = sock0;
 FD_SET(sock0, &rfds);

 

while (1) {
  printf("loop start sock0:%d\n", sock0);
  FD_SET(sock0, &rfds);
  int retval;  //selectの戻り値格納用

  char mes[20];
  int meslen = strlen(mes);
//   printf("meslen:%d\n",meslen);

  printf("mxfd:%d\n",mxfd);

  showallfds(&rfds);

  retval = select(mxfd + 1, &rfds, NULL, NULL, NULL);
  printf("retval:%d\n", retval);

  if(retval > 0){
      printf("detect connection\n");
      printf("retval:%d\n", retval);
  }else{
      perror("select()");
  };

  if(FD_ISSET(sock0, &rfds)){
      printf("this is a new conneciton\n");
      //  /* TCPクライアントからの接続要求を受け付ける */
      len = sizeof(client);
      sock = accept(sock0, (struct sockaddr *)&client, &len);
      printf("sock:%d\n", sock);
      //addconlist(conlist,sock);

      //リンクリストに追加
      push_back(&head, sock);
      show_all_linklist(&head);
      
      //showconlist(conlist);

      //conlisttoset(conlist, &rfds);
      copy_linklist_to_fs(&head,&rfds);

      showallfds(&rfds);
      if(sock > mxfd){
      mxfd = sock;
      }

  }else{
      printf("this is a message\n");
      int i, messize;
      for(i=4; i<14; i++){
          if(FD_ISSET(i, &rfds)){
                printf("%d is set\n", i);
                messize = recv(i, &mes, 20, 0);
                if(mes[0] != '\0'){
                broadcast_with_linklist(&head, mes);
            }else{
                printf("detect discon\n");         
                FD_CLR(i, &rfds);
                // rmfromarr(conlist, i);
                drop_desval(&head, i);
                show_all_linklist(&head);
                // resetarr(conlist);
            }


            break; //同時に来たときは早い方だけ

          }
      }

      //conlisttoset(conlist, &rfds);
      copy_linklist_to_fs(&head, &rfds);
      printf("mesval:%s\n", mes);
    //   showconlist(conlist);

  }

  //  /* TCPセッションの終了 */
//   close(sock);

  int i;
  for(i=0; i<20; i++){
    mes[i] = '\0';
  }
 
  printf("while fin\n");
 }

 /* listen するsocketの終了 */
//  close(sock0);

 return 0;
}


//現在登録されているfdを全て表示
void showallfds(fd_set *fs){
    int i;
    printf("showallfds---------------------------\n");
    for(i=0;i<10;i++){
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
        printf("key:%d\n", node_address->key);
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
        new_node->key = 1;
        *head_ref = new_node;
        return;
    }


    int keycounter;
    while(last->next != NULL){
        last = last->next;
        keycounter = last -> key;
    }

    new_node -> key = keycounter + 1;
    last -> next = new_node;
    return;

}


//リンクリストから指定の要素を削除
void drop_desval(struct Node** head_ref, int desval){

    struct Node* node_address = *head_ref;
    struct Node* pre_address = NULL;

    int counter = 0;


    while(node_address != NULL){
        printf("address:%p\n",node_address);

        if(node_address->val == desval){
            if(counter == 0){
                *head_ref = node_address->next;
                return;
            }

            pre_address->next = node_address->next;
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