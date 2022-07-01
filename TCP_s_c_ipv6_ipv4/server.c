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

//接続リストの構造体宣言
struct Node {
     int val;
     struct Node *next;   
 };

struct Node *head = NULL;

//関数のプロトタイプ宣言
void showallfds(fd_set*, int);
void push_back(struct Node**, int);
void show_all_linklist(struct Node**);
void drop_desval(struct Node**, int);
void copy_linklist_to_fs(struct Node**, fd_set*);
void broadcast_with_linklist(struct Node**, char*);

int get_sig_flag = 0;

void signal_handler(int signo){
    printf("\nclose:%d",close(3));
    get_sig_flag = 1;
    char *server_shut_msg = "server closed";
    broadcast_with_linklist(&head, server_shut_msg);
    printf("\nbye\n");
    exit(0);
}


int
main()
{
    //signalの設定
    struct sigaction sa;
    sigemptyset(&sa.sa_mask);
    sa.sa_handler = signal_handler;
    sa.sa_flags = 0;

    int retval_INT = sigaction(SIGINT, &sa, NULL); //<-sigactionの第一引数がキャッチできるやつだったら0,　キャッチできないやつだったら-1が返る
    int retval_HUP = sigaction(SIGHUP, &sa, NULL); //<-sigactionの第一引数がキャッチできるやつだったら0,　キャッチできないやつだったら-1が返る


    //select
    //int inputfd = 0; //標準入力用のfd
    fd_set rfds; //読み込みが可能になるfdのセット
    FD_ZERO(&rfds);
    int mxfd = -1;

    int sock0;
    struct sockaddr_in client;
    socklen_t len; 
    struct addrinfo hints, *res;
    int sock;
    int err;

    memset(&hints, 0, sizeof(hints));
    
     /* ソケットの設定 */
    hints.ai_family = AF_INET6;
    hints.ai_flags = AI_PASSIVE;
    hints.ai_socktype = SOCK_STREAM;
    err = getaddrinfo(NULL, "12345", &hints, &res);
    if (err != 0) {
        printf("getaddrinfo : %s\n", gai_strerror(err));
        return 1;
      }

    /* ソケットの作成 */
     sock0 = socket(res->ai_family, res->ai_socktype, 0);
     if(sock0 < 0){
         perror("socket");
         return 1;
     }

     printf("created socket:%d\n", sock0);

    if(bind(sock0, res->ai_addr, res->ai_addrlen) != 0){
        perror("bind");
        return 1;
    };

    freeaddrinfo(res);

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

      showallfds(&rfds, mxfd);

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

          showallfds(&rfds, mxfd);
          if(sock > mxfd){
          mxfd = sock;
          }

      }else{
          printf("this is a message\n");
          int i, messize;
          for(i=4; i<mxfd + 1; i++){
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
        printf("address:%p\n",node_address);

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