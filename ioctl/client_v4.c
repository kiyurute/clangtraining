 //実行コマンド：gcc -o client_v4 client_v4.c && ./client_v4

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>  //<-追記
#include <unistd.h>   //<-追記
#include <sys/select.h>  
#include <sys/ioctl.h>
#include <errno.h>

#define stdinput 0


int
main()
{
    struct sockaddr_in server;
    int sock;
    char buf[32]; //for receive from server
    char sendmes[32] = {'\0'}; //for send for server
    int n;
    int send_size;
    int con;

    fd_set wfds;
    int val_ioctl = 1;

    //ソケットの作成
    sock = socket(AF_INET, SOCK_STREAM, 0);
    ioctl(sock, FIONBIO, &val_ioctl);

    printf("sock:%d\n",sock);

     /* 接続先指定用構造体の準備 */
    server.sin_family = AF_INET;
    server.sin_port = htons(12345);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

     /* サーバに接続 */
    con = connect(sock, (struct sockaddr *)&server, sizeof(server));  //3wayhandshake

    if(con == 0){
        //success
    }else if( con < 0 && errno == EINPROGRESS){
        FD_SET(sock, &wfds);
        select(sock + 1, NULL, &wfds, NULL,NULL);
    }else{
        return -1;
    }

    // printf("con:%d errno:%d\n", con, errno);
    // printf("print error string by strerror: %s\n", strerror(errno));


    //標準入力の非同期化
    ioctl(stdinput, FIONBIO, &val_ioctl);

    
    while(1){

        scanf("%s", sendmes);
        if(strlen(sendmes) > 0){
            printf("input:%s\n",sendmes);
            send(sock, sendmes, strlen(sendmes), 0);
            memset(sendmes, '\0', sizeof(sendmes));
        }

        int  messize = recv(sock, &buf, 32, 0);
        if(messize > 0){
            printf("get message from server:%s\n", buf);
            memset(buf, '\0', sizeof(buf));
        }
        

    }

       
}







