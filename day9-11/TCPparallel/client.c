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
    int con;

    fd_set rfds;
    int stdinput = 0;


    sock = socket(AF_INET, SOCK_STREAM, 0);

    printf("sock:%d\n",sock);

     /* 接続先指定用構造体の準備 */
    server.sin_family = AF_INET;
    server.sin_port = htons(12345);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

     /* サーバに接続 */
    con = connect(sock, (struct sockaddr *)&server, sizeof(server));

    
    while(1){
        printf("loop start\n");
        int retval;
        FD_SET(stdinput, &rfds);
        FD_SET(sock, &rfds);

        retval = select(sock + 1, &rfds, NULL,NULL,NULL);

        printf("retval:%d\n",retval);

        if(retval < 0){
            perror("select()");
        }else{
            if(FD_ISSET(0, &rfds)){
                printf("get std input\n");
                scanf("%s", &sendmes);
                send(sock, sendmes, strlen(sendmes), 0);
            }else if(FD_ISSET(sock, &rfds)){
                printf("get message from server\n");
                int  messize = recv(sock, &buf, 20, 0);
                printf("%s\n", buf);
            }else{
                printf("nothing is set\n");
            }

        }

        // scanf("%s",sendmes);
        // send(sock, sendmes, strlen(sendmes), 0);

        // if (send_size == -1) {
        //     printf("send error\n");
        //     break;
        // }

         /* サーバからデータを受信 */
        // memset(buf, 0, sizeof(buf));
        // n = read(sock, buf, sizeof(buf));

        // printf("%d, %s\n", n, buf);

        // close(sock);

        // //select
        // fd_set rfds;
        // FD_ZERO(&rfds);

    }

       
}






