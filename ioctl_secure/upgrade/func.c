
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

#include <arpa/inet.h>
#include <openssl/ssl.h>
#include <openssl/err.h>


//接続リストの構造体宣言
struct Node {
     int val;
     SSL* ssl;
     int state; //0が3way handshake完了、1がSSL handshake完了
     struct Node *next; 
 };


extern struct Node *head;

//SSLコンテキストの作成
SSL_CTX *create_context()
{
    const SSL_METHOD *method;
    SSL_CTX *ctx;

    method = TLS_server_method();

    ctx = SSL_CTX_new(method);
    if (!ctx) {
        perror("Unable to create SSL context");
        ERR_print_errors_fp(stderr);
        exit(EXIT_FAILURE);
    }

    return ctx;
}

//証明書の読み込み、有効か確認
void configure_context(SSL_CTX *ctx)
{
    //contex
    /* Set the key and cert */
    //証明書の作り方は「openssl req -new -key private-key.pem > my-request.csr」なのになぜ.pem?
    if (SSL_CTX_use_certificate_file(ctx, "server.crt", SSL_FILETYPE_PEM) <= 0) {
        ERR_print_errors_fp(stderr);
        exit(EXIT_FAILURE);
    }

    // openssl genrsa 1024 > key.pem でOK?
    if (SSL_CTX_use_PrivateKey_file(ctx, "server.key", SSL_FILETYPE_PEM) <= 0 ) {
        ERR_print_errors_fp(stderr);
        exit(EXIT_FAILURE);
    }
}



//現在登録されているfdを全て表示
void showallfds(fd_set *fs, int mxfd){
    int i;
    printf("showallfds---------------------------\n");
    for(i=0;i<mxfd + 1;i++){
        if(FD_ISSET(i,fs)){
            printf("%d exsits\n",i);
        }
    }
    printf("showallfdsfin------------------------\n");

}


//リンクリストを全て表示
void show_all_linklist(struct Node** head_ref){

    struct Node* node_address = *head_ref;

    printf("linklist-----------------------------\n");

    while(node_address != NULL){
        printf("address:%p\n", node_address);
        printf("fdval:%d\n", node_address->val);
        printf("ssladdress:%p\n", node_address->ssl);
        node_address = node_address->next;
    }

    printf("linklist fin--------------------------\n");

}

//リンクリストの末尾に追加
void push_back(struct Node** head_ref, int new_data){

    printf("node:%p\n", head_ref);
    printf("node*:%p\n", *head_ref);
    // printf("node&:%p\n", &head_ref);
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));

    struct Node* last = *head_ref;

    new_node -> next = NULL;
    new_node -> val = new_data;
    new_node -> ssl = NULL;
    new_node -> state = 0;

    if(*head_ref == NULL){
        printf("this is a first connection\n");
        *head_ref = new_node;
        return;
    }


    while(last->next != NULL){
        last = last->next;
    }

    last -> next = new_node;
    return;

}

//指定ノードの状態更新
void upgrade_state(struct Node** head_ref, int desval){

    struct Node* node_address = *head_ref;

    while(node_address != NULL){
        if(node_address -> val == desval){
            node_address -> state = 1;
            break;
        }

        node_address = node_address -> next;

    }
    

}


//リンクリストから指定の要素を削除
void drop_desval(struct Node** head_ref, int desval){

    struct Node* node_address = *head_ref;
    struct Node* pre_address = NULL;

    int counter = 0;


    while(node_address != NULL){
        printf("address:%p\n",node_address);

        if(node_address->val == desval){
            if(counter == 0){
                *head_ref = node_address->next;
                printf("close:%d\n",close(node_address->val));
                return;
            }

            pre_address->next = node_address->next;
            printf("close:%d\n",close(node_address->val));
            free(node_address);
            return;
        }

        pre_address = node_address;
        node_address = node_address->next;

        counter += 1;
    }

}

//リンクリストを接続セットに反映
void copy_linklist_to_fs(struct Node **head_ref, fd_set *fs){

    struct Node* node_address = *head_ref;

    while(node_address != NULL){
        FD_SET(node_address->val, fs);
        node_address = node_address->next;
    }
}

//リンクリストを使ったブロードキャスト
void broadcast_with_linklist(struct Node **head_ref, char *mes){

    struct Node* node_address = *head_ref;

    while(node_address != NULL){
        // send(node_address->val,mes,strlen(mes),0);
        SSL_write(node_address->ssl, mes, strlen(mes));
        node_address = node_address->next;
    }

}

//暗号化されたメッセージを受信
int get_ssl_msg(struct Node **head_ref, int fdval, char *mesbuf, SSL_CTX *ctx){

    struct Node* node_address = *head_ref;
    int get_mes_size;

    while(node_address != NULL){
 
        if(node_address->val == fdval){

            printf("node_address->val:%d\n", node_address->val);
            printf("node_address->ssl:%d\n", node_address->ssl == NULL);

            if(node_address->ssl == NULL){
        
                SSL *ssl;
                ssl = SSL_new(ctx);
                node_address->ssl = ssl;

                SSL_set_fd(node_address->ssl, node_address->val);
            }
                
            int accept_result;
            int cr_err;
            SSL *ssl = node_address->ssl;

            if(node_address -> state == 0){
    
                while(1){
                
                    accept_result = SSL_accept(ssl); 

                    cr_err = SSL_get_error(ssl,accept_result);
                    if(cr_err == SSL_ERROR_WANT_READ || cr_err == SSL_ERROR_WANT_WRITE || cr_err == SSL_ERROR_WANT_ACCEPT){
                    
                    }else if(cr_err == SSL_ERROR_NONE){
                        get_mes_size = SSL_read(node_address->ssl, mesbuf, 1024);
                        printf("get_mes_size:%d\n",get_mes_size);
                        node_address->state = 1;
                        return get_mes_size;
                    }else{
                        //エラー処理
                        printf("%s.\n", strerror(errno));
                        break;
                    }
                }

            }

            get_mes_size = SSL_read(node_address->ssl, mesbuf, 1024);
            return get_mes_size;
        }
        node_address = node_address -> next;
    }

    return 0;
}