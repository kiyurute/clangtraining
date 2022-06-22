#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>  //<-追記
#include <unistd.h>   //<-追記


int
main()
{
 int sock0;
 struct sockaddr_in addr;
 struct sockaddr_in client;
 int len;
 int sock;
 char *mes[32];
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

//  /* TCPクライアントからの接続要求を受け付ける */
//  len = sizeof(client);
//  sock = accept(sock0, (struct sockaddr *)&client, &len);

//  /* 5文字送信 */
//  write(sock, "HELLO", 5);

//  /* TCPセッションの終了 */
//  close(sock);

while (1) {
   len = sizeof(client);
   sock = accept(sock0, (struct sockaddr *)&client, &len);
   int messize = recv(sock, mes, meslen, 0);
   printf("messize:%d\n", messize);
   printf("sock:%s\n", mes);
   write(sock, "HELLO,boo", 10);

   close(sock);
 }


 /* listen するsocketの終了 */
 close(sock0);

 return 0;
}

