//gcc -I /opt/homebrew/Cellar/openssl@3/3.0.5/include -o client_sample  client_sample.c -L /opt/homebrew/Cellar/openssl@3/3.0.5/lib -l ssl -l crypto && ./client_sample 127.0.0.1 12345

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


#define FAIL    -1
#define stdinput 0

void resetmsg(char*);

int OpenConnection(const char *hostname, int port)
{
    int sd;
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
    if ( connect(sd, (struct sockaddr*)&addr, sizeof(addr)) != 0 )
    {
        close(sd);
        perror(hostname);
        abort();
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
    SSL_CTX *ctx;
    int server;
    SSL *ssl;
    char buf[1024];
    char acClientRequest[1024] = {0};
    int bytes;
    char *hostname, *portnum;
    char sendmes[1024];
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

    if ( SSL_connect(ssl) == FAIL ){   /* perform the connection */
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
