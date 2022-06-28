#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>  
#include <unistd.h>   
#include <sys/select.h>  


int recvWithTimeout(int sockfd, void *buf, size_t len, int flags, unsigned int sec, unsigned int usec) {

    struct timeval tv;
    fd_set readfds;
    int ret_select;
    int ret_recv;

    /* タイムアウト時間を設定 */
    tv.tv_sec = sec;
    tv.tv_usec = usec;

    /* 読み込みFD集合を空にする */
    FD_ZERO(&readfds);

    /* 読み込みFD集合にsockfdを追加 */
    FD_SET(sockfd, &readfds);

    /* selectでreadfdsのどれかが読み込み可能になるまでorタイムアウトまで待ち */
    ret_select = select(sockfd + 1, &readfds, NULL, NULL, &tv);

    /* 戻り値をチェック */
    if (ret_select == -1) {
        /* select関数がエラー */
        printf("select error\n");
        return -1;
    }

    if (ret_select == 0) {
        /* 読み込み可能になったFDの数が0なのでタイムアウトと判断 */
        printf("timeout!!\n");
        return 0;
    }

    /* sockfdが読み込み可能なのでrecv実行 */
    ret_recv = recv(sockfd, buf, len, flags);

    return ret_recv;
}


int
main()
{
 int sock0;
 struct sockaddr_in addr;
 struct sockaddr_in client;
 int len;
 int sock;
 char mes[20];
 int meslen = strlen(mes);
 printf("meslen:%d\n",meslen);

 /* ソケットの作成 */
 sock0 = socket(AF_INET, SOCK_STREAM, 0);
 
 /* ソケットの設定 */
 addr.sin_family = AF_INET;
 addr.sin_port = htons(12345);
 addr.sin_addr.s_addr = INADDR_ANY;

 bind(sock0, (struct sockaddr *)&addr, sizeof(addr));

 /* TCPクライアントからの接続要求を待てる状態にする */
 listen(sock0, 10);

while (1) {
  char mes[20];
  int meslen = strlen(mes);
  printf("meslen:%d\n",meslen);

  //  /* TCPクライアントからの接続要求を受け付ける */
  len = sizeof(client);
  sock = accept(sock0, (struct sockaddr *)&client, &len);

  printf("sock:%d\n", sock);
  int messize = recvWithTimeout(sock, &mes, 20, 0, 5, 500000);
  printf("messize:%d\n", messize);
  printf("mesval:%s\n", mes);
  write(sock, "HELLO from server", 30);

  //  /* TCPセッションの終了 */
  close(sock);
  int i;
  for(i=0; i<20; i++){
    mes[i] = NULL;
  }
 }

 /* listen するsocketの終了 */
 close(sock0);

 return 0;
}

