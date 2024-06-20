#include <stdio.h>
#include <stdlib.h>
void evalSocketFd(int fd){
    if (fd < 0){
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
}

void evalBind(int b){
      if(b < 0){
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
}

void evalListen(int l){
    if(l < 0){
        perror("listen");
        exit(EXIT_FAILURE);
    }
}

void evalAccept(int a){
    if(a < 0){
        perror("accept");
        exit(EXIT_FAILURE);
    }
}

void evalInet(int i){
    if(i<=0){
        perror("Invalid address/ Address not supported");
        exit(EXIT_FAILURE);
    }
}

void evalConnect(int c){
    if (c < 0){
        perror("Connection failed");
        exit(EXIT_FAILURE);
    }
}