#include <stdio.h>
#include <stdlib.h>
#include <sys/select.h>

int main(void){
    int fd0 = 0;
    int fd1 = 1;
    fd_set rfds;
    struct timeval tv;
    char* inputval;
    int retval;

    FD_ZERO(&rfds);
    FD_SET(fd0, &rfds);
    FD_SET(fd1, &rfds);
    tv.tv_sec = 5;
    tv.tv_usec = 500000;


    retval = select(fd1 + 1, &rfds, NULL, NULL, &tv);

    if(retval < 0){
        perror("select()");
    }
    else if(retval > 0){
        scanf("%s", inputval);
        printf("input: %s\n", inputval);
    }
    else{
        printf("timeout\n");
    }
    return (EXIT_SUCCESS);
}