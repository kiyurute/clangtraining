#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>  
#include <unistd.h>   
#include <sys/select.h> 

void showallfds(fd_set*);
void addconlist(int *, int);
void conlisttoset(int *, fd_set*);
void showconlist(int *);
void broadcast(int*, char*);
void resetarr(int*);
void rmfromarr(int*, int);

int
main()
{
 int sock0;
 struct sockaddr_in addr;
 struct sockaddr_in client;
//  int len;
 socklen_t len; 
 int sock;
 int conlist[10] = {0,0,0,0,0,0,0,0,0,0}; //接続リスト

 //select
 //int inputfd = 0; //標準入力用のfd
 fd_set rfds; //読み込みが可能になるfdのセット
 FD_ZERO(&rfds);
 int mxfd = 0;

 /* ソケットの作成 */
 sock0 = socket(AF_INET, SOCK_STREAM, 0);
 printf("created socket:%d\n", sock0);

 
 /* ソケットの設定 */
 addr.sin_family = AF_INET;
 addr.sin_port = htons(12345);
 addr.sin_addr.s_addr = INADDR_ANY;

 bind(sock0, (struct sockaddr *)&addr, sizeof(addr));

 /* TCPクライアントからの接続要求を待てる状態にする */
 listen(sock0, 5);
//  FD_SET(sock0, &rfds);
 mxfd = sock0;
 FD_SET(sock0, &rfds);

while (1) {
  printf("loop start sock0:%d\n", sock0);
  FD_SET(sock0, &rfds);
  int retval;  //selectの戻り値格納用

  char mes[20];
  int meslen = strlen(mes);
//   printf("meslen:%d\n",meslen);

  printf("mxfd:%d\n",mxfd);

  showallfds(&rfds);

  retval = select(mxfd + 1, &rfds, NULL, NULL, NULL);
  printf("retval:%d\n", retval);

  //clientが終了したときはなぜかこの戻り値が2になる
  if(retval > 0){
      printf("detect connection\n");
      printf("retval:%d\n", retval);
  }else{
      perror("select()");
  };

  if(FD_ISSET(sock0, &rfds)){
      printf("this is a new conneciton\n");
      //  /* TCPクライアントからの接続要求を受け付ける */
      len = sizeof(client);
      sock = accept(sock0, (struct sockaddr *)&client, &len);
      printf("sock:%d\n", sock);
      addconlist(conlist,sock);
      showconlist(conlist);
      conlisttoset(conlist, &rfds);
      //FD_SET(sock, &rfds);
      showallfds(&rfds);
      if(sock > mxfd){
      mxfd = sock;
      }

  }else{
      printf("this is a message\n");
      int i, messize;
      for(i=4; i<14; i++){
          if(FD_ISSET(i, &rfds)){
            printf("%d is set\n", i);

            messize = recv(i, &mes, 20, 0);
            if(mes[0] != '\0'){
             broadcast(conlist, mes);
            }else{
                printf("detect discon\n");         
                FD_CLR(i, &rfds);
                rmfromarr(conlist, i);
                // resetarr(conlist);
            }
            break;

          }
      }
      conlisttoset(conlist, &rfds);
      printf("mesval:%s\n", mes);
      showconlist(conlist);

  }

//   write(sock, "get message", 30);
//   send(sock, "getmessage:",11, 0);

  //  /* TCPセッションの終了 */
//   close(sock);

  int i;
  for(i=0; i<20; i++){
    mes[i] = '\0';
  }
 
  printf("while fin\n");
 }

 /* listen するsocketの終了 */
//  close(sock0);

 return 0;
}



//現在登録されているfdを全て表示
void showallfds(fd_set *fs){
    int i;
    printf("showallfds---------------------------\n");
    for(i=0;i<10;i++){
        if(FD_ISSET(i,fs)){
            printf("%d exsits\n",i);
        }
    }
    printf("showallfdsfin------------------------\n");

}

//接続リストに追加
void addconlist(int *list, int newfd){
    int i;
    for(i=0; i<10; i++){
        if(list[i] == 0){
            list[i] = newfd;
            break;
        }
    }
    
}

//接続リストを表示
void showconlist(int *list){
    int i;
    for(i=0; i<10; i++){
        printf("i:%d val:%d\n",i,list[i]);
    }
}

//接続リストを接続セットに反映
void conlisttoset(int *list, fd_set *fs){
    printf("in conlisttoset\n");
    int i;
    for(i=0; i<10; i++){
        if(list[i] != 0){
            printf("in if:%d\n",list[i]);
            FD_SET(list[i], fs);
        }
    }
}

//ブロードキャスト
void broadcast(int *arr, char *mes){
    int i;
    
    for(i=0;i<10;i++){
        if(arr[i] != 0){
            printf("send to %d\n", arr[i]);
            send(arr[i],mes,20, 0);
            // write(arr[i],mes,30);
        }
    }
}

//配列の初期化
void resetarr(int *arr){
    int i;
    for(i=0;i<10;i++){
        arr[i] = 0;
    }
}

//配列から指定の要素を削除
void rmfromarr(int *arr, int num){
    int i;
    for(i=0; i<10; i++){
        if(arr[i] == num){
            arr[i] = 0;
        }
    }
}
