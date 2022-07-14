#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>  //<-追記
#include <unistd.h>   //<-追記
#include <sys/ioctl.h>


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

 int val_ioctl = 1;

 /* ソケットの作成 */
 sock0 = socket(AF_INET, SOCK_STREAM, 0);

 /* ソケットの設定 */
 addr.sin_family = AF_INET;
 addr.sin_port = htons(12345);
 addr.sin_addr.s_addr = INADDR_ANY;

 bind(sock0, (struct sockaddr *)&addr, sizeof(addr));

 /* TCPクライアントからの接続要求を待てる状態にする */
 listen(sock0, 10);

 printf("ioctl:%d\n",ioctl(sock0, FIONBIO, &val_ioctl));   //recvで止まらない


while (1) {
  char mes[20];
  int meslen = strlen(mes);
  printf("meslen:%d\n",meslen);

  //  /* TCPクライアントからの接続要求を受け付ける */
  len = sizeof(client);
  sock = accept(sock0, (struct sockaddr *)&client, &len);

  printf("sock:%d", sock);

  if(sock > 0){
      printf("new client\n");

      while(1){

          int messize = recv(sock, &mes, 20, 0); //どこから来たかを調べるには？

          if(messize < 1){
             
          }else{
              printf("catch message\n");

          }
          
      }
  }

//   int messize = recv(sock, &mes, 20, 0);

//   if(messize < 1){

//   }else{
//       printf("catch message\n");

//   }
//   printf("messize:%d\n", messize);
  printf("mesval:%s\n", mes);
  write(sock, "HELLO from server", 30);

  sleep(1);

  //  /* TCPセッションの終了 */
  close(sock);
  int i;
  for(i=0; i<20; i++){
    mes[i] = '\0';
  }
 }

 /* listen するsocketの終了 */
 close(sock0);

 return 0;
}

