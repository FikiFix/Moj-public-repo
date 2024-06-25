#include <stdio.h>
#include <stdlib.h>
void checkFd(int fd){
    if(fd < 0){
        perror("socket error");
        exit(EXIT_FAILURE);
    }
}
void checkBind(int bind){
    if(bind < 0){
        perror("bind error");
        exit(EXIT_FAILURE);
    }
}
void checkListen(int listen){
    if(listen < 0){
        perror("listen error");
        exit(EXIT_FAILURE);
    }
}

void checkAccept(int acc){
    if(acc < 0){
        perror("Accept error");
        exit(EXIT_FAILURE);
    }
}

void checkInet(int inet){
    if(inet<=0){
        perror("Inet error: Invalid address / Address not supported");
        exit(EXIT_FAILURE);
    }
}

void checkConnect(int con){
    if(con < 0){
        perror("Connect error");
        exit(EXIT_FAILURE);
    }
}