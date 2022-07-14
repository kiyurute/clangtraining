//ioctlの例 https://www.geekpage.jp/programming/linux-network/nonblocking.php
//ioctlの説明 https://linuxhint.com/c-ioctl-function-usage/#:~:text=The%20Purpose%20of%20the%20IOCTL%20Function%20in%20C%3A&text=The%20device%20files%20are%20the,IOCTL%E2%80%9D%20function%20comes%20into%20play.

//実行コマンド gcc server.c func.c -o server && ./server

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

struct Node *head = NULL;

//関数のプロトタイプ宣言
void showallfds(fd_set*, int);
void push_back(struct Node**, int);
void show_all_linklist(struct Node**);
void drop_desval(struct Node**, int);
void copy_linklist_to_fs(struct Node**, fd_set*);
void broadcast_with_linklist(struct Node**, char*);
int  check_have_msg(struct Node**, char*);

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

    int val_ioctl = 1;
    int messize;

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

     ioctl(sock0, FIONBIO, &val_ioctl);

    //  FD_SET(sock0, &rfds);
     mxfd = sock0;
     FD_SET(sock0, &rfds);


    while (1){

        char recv_msg[20]; //受信メッセージ格納用
        len = sizeof(client);
        sock = accept(sock0, (struct sockaddr *)&client, &len);

        if(sock > 3){
            printf("catched new client\n");
            push_back(&head, sock);
            show_all_linklist(&head);
        }

        int recv_msg_size = check_have_msg(&head, recv_msg);
        // printf("messize:%d\n", recv_msg_size);
        if(recv_msg_size > 0){
            broadcast_with_linklist(&head, recv_msg);
        }else if(recv_msg_size == 0){
            show_all_linklist(&head);
        }
            

    }

     /* listen するsocketの終了 */
    //  close(sock0);

     return 0;
}

