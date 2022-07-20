//gcc -I /opt/homebrew/Cellar/openssl@3/3.0.5/include -o client_secure client_secure.c -L /opt/homebrew/Cellar/openssl@3/3.0.5/lib -l ssl -l crypto && ./client_secure 127.0.0.1 12345

#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <resolv.h>
#include <netdb.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/select.h> 
#include <sys/ioctl.h>


#define FAIL    -1
#define stdinput 0

int val_ioctl = 1;

void resetmsg(char*);
fd_set wfds;

int OpenConnection(const char *hostname, int port)
{
    int sd;
    int con;
    struct hostent *host;
    struct sockaddr_in addr;
    if ( (host = gethostbyname(hostname)) == NULL )
    {
        perror(hostname);
        abort();
    }
    sd = socket(PF_INET, SOCK_STREAM, 0);
    bzero(&addr, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = *(long*)(host->h_addr);

    ioctl(sd, FIONBIO, &val_ioctl);
    con = connect(sd, (struct sockaddr*)&addr, sizeof(addr));
    printf("con:%d\n",con);

    if(con == 0){
        //success
    }else if( con < 0 && errno == EINPROGRESS){
       
        FD_SET(sd, &wfds);
        select(sd + 1, NULL, &wfds, NULL,NULL);
        printf("select fin\n");
    }else{
        return -1;
    }

    return sd;
}

SSL_CTX* InitCTX(void)
{
    SSL_METHOD *method;
    SSL_CTX *ctx;
    OpenSSL_add_all_algorithms();  /* Load cryptos, et.al. */
    SSL_load_error_strings();   /* Bring in and register error messages */
    method = TLSv1_2_client_method();  /* Create new client-method instance */
    ctx = SSL_CTX_new(method);   /* Create new context */
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


int main(int count, char *strings[])
{
    errno = 0;
    SSL_CTX *ctx;
    int server;
    SSL *ssl;
    int bytes;
    char *hostname, *portnum;
    char sendmes[1024] = {'\0'};
    char getmes[1024] = {'\0'};
    fd_set rfds;

    if ( count != 3 )
    {
        printf("usage: %s <hostname> <portnum>\n", strings[0]);
        exit(0);
    }

    SSL_library_init();
    hostname=strings[1];
    portnum=strings[2];
    ctx = InitCTX();
    server = OpenConnection(hostname, atoi(portnum));
    ssl = SSL_new(ctx);      /* create new SSL connection state */
    SSL_set_fd(ssl, server);    /* attach the socket descriptor */

    int connect_result;
    int cr_err;
    
    ioctl(stdinput, FIONBIO, &val_ioctl);

    // while(1){

    //     connect_result = SSL_connect(ssl);  //SSL handshake
    //     cr_err = SSL_get_error(ssl,connect_result);
    //     if(cr_err == SSL_ERROR_WANT_READ || cr_err == SSL_ERROR_WANT_WRITE || cr_err == SSL_ERROR_WANT_ACCEPT){

    //     }else if(cr_err == SSL_ERROR_NONE){
    //         break;
    //     }else{
    //         //エラー処理
    //         printf("%s.\n", strerror(errno));
    //         break;
    //     }

    // }

  
    if ( connect_result == FAIL ){   
        printf("connection error\n");
        ERR_print_errors_fp(stderr);
    }else{
        //printf("hello\n");
        printf("connection success\n");
        while(1){

            int retval;
            FD_SET(stdinput, &rfds);
            FD_SET(server, &rfds);

            retval = select(server + 1, &rfds, NULL, NULL, NULL);

            if(retval < 0){
                perror("select()");
            }else{
                if(FD_ISSET(0, &rfds)){
                    printf("get std input\n");
                    scanf("%s", sendmes);

                     while(1){

                        connect_result = SSL_connect(ssl);  //SSL handshake
                        cr_err = SSL_get_error(ssl,connect_result);
                        if(cr_err == SSL_ERROR_WANT_READ || cr_err == SSL_ERROR_WANT_WRITE || cr_err == SSL_ERROR_WANT_ACCEPT){
                        
                        }else if(cr_err == SSL_ERROR_NONE){
                            break;
                        }else{
                            //エラー処理
                            printf("%s.\n", strerror(errno));
                            break;
                        }

                    }


                    SSL_write(ssl, sendmes, strlen(sendmes));

                
                }else if(FD_ISSET(server, &rfds)){
                    int messize = SSL_read(ssl, &getmes, 1024);
                    if(getmes[0] != '\0'){
                        printf("get ssl message from server:%s\n", getmes);
                    }
                    resetmsg(getmes);

                }
            }
            
        }

    }
    close(server);         /* close socket */
    SSL_CTX_free(ctx);        /* release context */
    return 0;
}

void resetmsg(char* msg){
    // printf("%s\n", msg);
    int i;
    for(i=0; i < 1024; i++){
        msg[i] = '\0';
    }
}
