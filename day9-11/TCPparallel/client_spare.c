
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>  //<-追記
#include <unistd.h>   //<-追記
#include <sys/select.h>  

int
main()
{
    struct sockaddr_in server;
    int sock;
    char buf[32]; //for receive from server
    char sendmes[32]; //for send for server
    int n;
    int send_size;

    sock = socket(AF_INET, SOCK_STREAM, 0);

     /* 接続先指定用構造体の準備 */
    server.sin_family = AF_INET;
    server.sin_port = htons(12345);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

     /* サーバに接続 */
    connect(sock, (struct sockaddr *)&server, sizeof(server));

    while(1){
        scanf("%s",sendmes);
        send(sock, sendmes, strlen(sendmes), 0);

        if (send_size == -1) {
            printf("send error\n");
            break;
        }

         /* サーバからデータを受信 */
        memset(buf, 0, sizeof(buf));
        n = read(sock, buf, sizeof(buf));

        printf("%d, %s\n", n, buf);

        // close(sock);

        // //select
        // fd_set rfds;
        // FD_ZERO(&rfds);

    }

       
}