#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>  //<-追記
#include <unistd.h>   //<-追記

int
main(int argc, char const *argv[])
{
 printf("arg:%s\n",argv[2]);
 printf("arg:%s\n",argv[3]);
 struct sockaddr_in server;
 int sock;
 char buf[32];
 int n;
//  char mes[] = "iamclient";
//  int meslen = strlen(mes);
//  printf("meslen:%d\n", meslen);
 /* ソケットの作成 */
 sock = socket(AF_INET, SOCK_STREAM, 0);

 /* 接続先指定用構造体の準備 */
 server.sin_family = AF_INET;
 server.sin_port = htons(12345);
 server.sin_addr.s_addr = inet_addr("127.0.0.1");

 /* サーバに接続 */
 connect(sock, (struct sockaddr *)&server, sizeof(server));
 printf("mes:%s address:%p\n", argv[2],&argv[2]);
 send(sock, argv[2], strlen(argv[2]), 0);

 /* サーバからデータを受信 */
 memset(buf, 0, sizeof(buf));
 n = read(sock, buf, sizeof(buf));

 printf("%d, %s\n", n, buf);

 /* socketの終了 */
 close(sock);

 return 0;
}