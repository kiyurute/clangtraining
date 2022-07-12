//gcc -I /opt/homebrew/Cellar/openssl@3/3.0.5/include -o client client.c -L /opt/homebrew/Cellar/openssl@3/3.0.5/lib -l ssl -l crypto && ./client 127.0.0.1 12345


#include <stdio.h>
#include <errno.h>
#include <unistd.h>   
#include <string.h>
#include <resolv.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>  
#include <sys/select.h>  

#include <openssl/ssl.h>
#include <openssl/err.h>

void resetmsg(char*);

//ssl_ctxの初期化?
SSL_CTX* InitCTX(void)
{
    SSL_METHOD *method;
    SSL_CTX *ctx;
    OpenSSL_add_all_algorithms();  /* Load cryptos, et.al. */
    SSL_load_error_strings();   /* Bring in and register error messages */
    method = TLSv1_2_client_method();  /* Create new client-method instance */
    ctx = SSL_CTX_new(method);   /* Create new context */  //これのせい
    if ( ctx == NULL )
    {
        ERR_print_errors_fp(stderr);
        abort();
    }
    return ctx;
}

void ShowCerts(SSL* ssl)
{
    X509 *cert;
    char *line;
    cert = SSL_get_peer_certificate(ssl); /* get the server's certificate */
    if ( cert != NULL )
    {
        printf("Server certificates:\n");
        line = X509_NAME_oneline(X509_get_subject_name(cert), 0, 0);
        printf("Subject: %s\n", line);
        free(line);       /* free the malloc'ed string */
        line = X509_NAME_oneline(X509_get_issuer_name(cert), 0, 0);
        printf("Issuer: %s\n", line);
        free(line);       /* free the malloc'ed string */
        X509_free(cert);     /* free the malloc'ed certificate copy */
    }
    else
        printf("Info: No client certificates configured.\n");
}


int
main()
{
    SSL_CTX *ctx;
    struct sockaddr_in server;
    int sock;
    SSL *ssl;
    char buf[32]; //for receive from server
    char sendmes[32]; //for send for server
    int n;
    int send_size;
    int con;

    fd_set rfds;
    int stdinput = 0;

    SSL_library_init();

    ctx = InitCTX(); 

    sock = socket(PF_INET, SOCK_STREAM, 0);  //sock == server
    printf("sock:%d\n",sock);

    // printf("sock:%d\n",sock);

     /* 接続先指定用構造体の準備 */
    server.sin_family = AF_INET;
    server.sin_port = htons(12345);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    ssl = SSL_new(ctx);
    SSL_set_fd(ssl, sock);

    if ( SSL_connect(ssl) == -1 ){
        /* perform the connection */
        ERR_print_errors_fp(stderr);
    }  
    else{

        printf("connection success\n");
    }

    // SSL_connect(ssl);
    // con = connect(sock, (struct sockaddr *)&server, sizeof(server));

    
    while(1){
        // printf("loop start\n");
        int retval;
        FD_SET(stdinput, &rfds);
        FD_SET(sock, &rfds);

        retval = select(sock + 1, &rfds, NULL,NULL,NULL);

        // printf("retval:%d\n",retval);

        if(retval < 0){
            perror("select()");
        }else{
            if(FD_ISSET(0, &rfds)){
                printf("get std input\n");
                scanf("%s", sendmes);
                printf("\n\nConnected with %s encryption\n", SSL_get_cipher(ssl));
                ShowCerts(ssl);
                SSL_write(ssl, sendmes, strlen(sendmes));
                // send(sock, sendmes, strlen(sendmes), 0);
            }else if(FD_ISSET(sock, &rfds)){
                int  messize = recv(sock, &buf, 20, 0);
                // printf("messize:%d\n",messize);
                if(buf[0] != '\0'){
                    printf("get message from server:%s\n", buf);
                    resetmsg(buf);
                }
    
            }else{
                printf("nothing is set\n");
            }

        }
    }
       
}

void resetmsg(char* msg){
    // printf("%s\n", msg);
    int i;
    for(i=0; i < 32; i++){
        msg[i] = '\0';
    }
}






