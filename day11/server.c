
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>  //<-追記
#include <unistd.h>   //<-追記
#include <sys/select.h>  
#include <string.h>

int getFileSize(const char*);
void setHtmlToBuff(char*, char*);
void createResMsg(char*, char*, int*);


int
main()
{

 //ファイルサイズを読み込む
 char *path = "./index.html";
 int fileSize = getFileSize(path);
 printf("filesize:%d\n",fileSize);

 //htmlをバッファに格納
 char body[2048];
 setHtmlToBuff(body, path);
 printf("%s\n",body);

 int sock0;
 struct sockaddr_in addr;
 struct sockaddr_in client;
 socklen_t len;
 int sock;
 int yes = 1;

 char buf[2048];
 char inbuf[2048];
 int currentportnum = 12345;

 //select
 fd_set rfds;
 int stdinput = 0;
 int sival;

 sock0 = socket(AF_INET, SOCK_STREAM, 0);
 if (sock0 < 0) {
	 perror("socket");
	 return 1;
 }

 addr.sin_family = AF_INET;
 addr.sin_port = htons(12345);
 addr.sin_addr.s_addr = INADDR_ANY;

 setsockopt(sock0,
   SOL_SOCKET, SO_REUSEADDR, (const char *)&yes, sizeof(yes));

 if (bind(sock0, (struct sockaddr *)&addr, sizeof(addr)) != 0) {
	 perror("bind");
	 return 1;
 }

 if (listen(sock0, 5) != 0) {
	 perror("listen");
	 return 1;
 }

 createResMsg(buf, body, &currentportnum);


 while (1) {
     printf("enter the port num\n");
     FD_SET(stdinput, &rfds);
     FD_SET(sock0, &rfds);

     int retval;
     retval = select(sock0 + 1, &rfds, NULL, NULL, NULL);

     if(retval < 0){
         perror("select()");
     }

     if(FD_ISSET(0, &rfds)){
         printf("ready\n");
         scanf("%d",&sival);
         sock0 = socket(AF_INET, SOCK_STREAM, 0);
         if (sock0 < 0) {
         	 perror("socket");
         	 return 1;
         }

         addr.sin_family = AF_INET;
         addr.sin_port = htons(sival);
         addr.sin_addr.s_addr = INADDR_ANY;
         
         setsockopt(sock0,
           SOL_SOCKET, SO_REUSEADDR, (const char *)&yes, sizeof(yes));
         
         if (bind(sock0, (struct sockaddr *)&addr, sizeof(addr)) != 0) {
         	 perror("bind");
         	 return 1;
         }
         
         if (listen(sock0, 5) != 0) {
         	 perror("listen");
         	 return 1;
         }

         currentportnum = sival;

         createResMsg(buf,body,&currentportnum);

         
         FD_ZERO(&rfds);
         FD_SET(stdinput, &rfds);
         FD_SET(sock0, &rfds);

         printf("changed port num to %d\n", sival);

     }else{

         len = sizeof(client);
         sock = accept(sock0, (struct sockaddr *)&client, &len);
         if (sock < 0) {
	         perror("accept");
	         break;
         }
     
         memset(inbuf, 0, sizeof(inbuf));
         recv(sock, inbuf, sizeof(inbuf), 0);
         // 本来ならばクライアントからの要求内容をパースすべきです
         printf("%s", inbuf);
     
         // 相手が何を言おうとダミーHTTPメッセージ送信
         printf("sendmes:\n");
         printf("%s",buf);
         send(sock, buf, (int)strlen(buf), 0);
     
         close(sock);

     }

     
 }

 close(sock0);

 return 0;
}

//ファイルサイズを取得する関数
int getFileSize(const char *path){
    int size, read_size;
    char read_buf[2048];
    FILE *f;

    f = fopen(path, "rb");
    if(f == NULL){
        perror("cannot read a file");
        return 0;
    }

    size = 0;
    do{
        read_size = fread(read_buf, 1, 2048, f);
        size += read_size;
    }while(read_size != 0);

    fclose(f);

    return size;

}


//htmlファイルをバッファに格納する関数
void setHtmlToBuff(char *body, char *path){
    FILE *f;
    int file_size;

    file_size = getFileSize(path);

    f = fopen(path, "r");
    fread(body, 1, file_size, f);
    fclose(f);


}

//レスポンスメッセージの作成
void createResMsg(char *buf, char *html, int *port){

    // 応答用HTTPメッセージ作成
    memset(buf, 0, 2048);
    snprintf(buf, 2048,
	 "HTTP/1.1 200 OK\r\n"
     "Content-Type: text/html\r\n"
     "Connection: Keep-Alive\r\n"
     "\r\n"
     "current port num:%d\r\n"
     "%s", 
     *port,
     html
     );

}


