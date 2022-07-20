//gcc -I /opt/homebrew/Cellar/openssl@3/3.0.5/include -o server server.c func.c -L /opt/homebrew/Cellar/openssl@3/3.0.5/lib -l ssl -l crypto

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

#include <arpa/inet.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

//接続リストの構造体宣言
struct Node {
     int val;
     SSL *ssl;
     int state; //0が3way handshake完了、1がSSL handshake完了
     struct Node *next; 
 };


//先頭ノードの作成
struct Node *head = NULL;

//関数のプロトタイプ宣言
void showallfds(fd_set*, int);
void push_back(struct Node**, int);
void show_all_linklist(struct Node**);
void drop_desval(struct Node**, int);
void copy_linklist_to_fs(struct Node**, fd_set*);
void broadcast_with_linklist(struct Node**, char*);
int get_ssl_msg(struct Node**, int, char*);




int get_sig_flag = 0;

//シグナルの設定
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
    errno = 0;
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

    //SSL
    // SSL_CTX *ctx;
    // ctx = create_context();
    // configure_context(ctx);

    int sock0;
    struct sockaddr_in client;
    socklen_t len; 
    struct addrinfo hints, *res;
    int sock;
    int err;

    int val_ioctl = 1;

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

    //  printf("created socket:%d\n", sock0);

    if(bind(sock0, res->ai_addr, res->ai_addrlen) != 0){
        perror("bind");
        return 1;
    };

    freeaddrinfo(res);

    /* TCPクライアントからの接続要求を待てる状態にする */
    listen(sock0, 5);
    mxfd = sock0;
    FD_SET(sock0, &rfds);

    ioctl(sock0, FIONBIO, &val_ioctl);

    while (1) {
      printf("loop start sock0:%d\n", sock0);
      FD_SET(sock0, &rfds);
      int select_retval;  //selectの戻り値格納用
    //   SSL *ssl;

      char mes[1024];
      int meslen = strlen(mes);

      printf("mxfd:%d\n",mxfd);

      showallfds(&rfds, mxfd);

      select_retval = select(mxfd + 1, &rfds, NULL, NULL, NULL);
    //   printf("retval:%d\n", retval);

      if(select_retval > 0){
          printf("detect connection\n");
          printf("retval:%d\n", select_retval);
      }else{
          perror("select()");
      };

      if(FD_ISSET(sock0, &rfds)){
          printf("this is a new conneciton\n");
          //  /* TCPクライアントからの接続要求を受け付ける */
          len = sizeof(client);
          sock = accept(sock0, (struct sockaddr *)&client, &len);
          printf("sock:%d\n", sock);

        //###############################################################
          
        //   ssl = SSL_new(ctx);
        //   SSL_set_fd(ssl, sock);

        //   int accept_result;
        //   int cr_err;

        //   while(1){

        //       accept_result = SSL_accept(ssl);  //SSL handshake
        //       cr_err = SSL_get_error(ssl,accept_result);
        //       printf("cr_err:%d\n", cr_err);
        //       if(cr_err == SSL_ERROR_WANT_READ || cr_err == SSL_ERROR_WANT_WRITE || cr_err == SSL_ERROR_WANT_ACCEPT){

        //       }else if(cr_err == SSL_ERROR_NONE){
        //           break;
        //       }else{
        //           //エラー処理
        //           printf("%s.\n", strerror(errno));
        //           break;
        //       }
      
        //   }

        //###############################################################

          //最初は登録だけする　次にメッセージが来た時にSSLハンドシェイクする。メッセージ処理の中にSSLハンドシェイクを含める。ノードの中にSSLハンドシェイクが済んでいるかのstateを保存する。

          //リンクリストに追加
          push_back(&head, sock);
        //   show_all_linklist(&head);
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
                messize = get_ssl_msg(&head, i, mes);
                printf("messize:%d\n",messize);
                memset(mes,'\0',sizeof(mes));
                if(messize > 0){
                    broadcast_with_linklist(&head, mes);
                }else if(messize == 0){
                    printf("detect discon\n");         
                    FD_CLR(i, &rfds);
                    drop_desval(&head, i);
                    show_all_linklist(&head);
                }else{
                    printf("connection error\n");         
                    // FD_CLR(i, &rfds);
                    // drop_desval(&head, i);
                    // show_all_linklist(&head);
                }

                break; //同時に来たときは早い方だけ

              }
          }

          copy_linklist_to_fs(&head, &rfds);
          printf("mesval:%s\n", mes);

      }

      //  /* TCPセッションの終了 */
    //   close(sock);

      printf("while fin\n");
     }

     /* listen するsocketの終了 */
    //  close(sock0);

     return 0;
}




