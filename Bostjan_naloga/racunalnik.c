#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
#include "napake.h"
#include "komunikacija.h"

#define PORT 8080
#define PACKET_SIZE 256 + sizeof(int) + 1

void charToInt(char* src, int* dest, int size){
    for(int i = 0; i < size; i++){
        dest[i] = (char)src[i];
    }
}


void printArr(char* arr, int size){
    printf("Array: ");
    for(int i = 0; i < size; i++){
        printf("%d ", (int)arr[i]);
    }printf("\n");
}

void decript(char* ret, char* freq, int size) {
    for(int i = 0; i < size; i++) {
        if(i % 2 == 0) {
            int buff = ((int)ret[i] - (int)freq[i]);
            ret[i] = (char)buff;
        } else {
            int buff = ((int)freq[i] + (int)ret[i]);
            ret[i] = (char)buff;
        }
    }
}

int main(){
    char name[] = "Bostjan Kociper Pomper";
    size_t nameSize = sizeof(name)/sizeof(char);
    
    struct sockaddr_in address;
    socklen_t addrlen = sizeof(address);
    address.sin_family = AF_INET; //pove da bomo meli IPv4 kominikacijo
    address.sin_addr.s_addr = INADDR_ANY; //sprejmemo kirekoli adresse na našem ip
    address.sin_port = htons(PORT); //porihtamo endianess (mreže rabijo big endian se mi zdi)

    struct Message msg;

    int serverFd = socket(AF_INET, SOCK_STREAM, 0);
    checkFd(serverFd);
    
    int b = bind(serverFd, (struct sockaddr*)&address, sizeof(address));
    checkBind(b);

    int l = listen(serverFd, 3);
    checkListen(l);

    int socket = accept(serverFd, (struct sockaddr*)&address, &addrlen);
    checkAccept(socket);
    char freq[nameSize];
    while (1) {
        char recieved[PACKET_SIZE] = {0};
        int status = recv(socket, recieved, sizeof(recieved), 0);
        //status nam pove koliko bajtov podatkov je bilo prenesenih
        // -1 = napaka, 0 = odjemalec se je odklopil, status > 0: dobili smo sporocilo
        if (status == -1) {
            perror("recv failed");
            exit(EXIT_FAILURE);
        } else if (status == 0) {
            printf("Krmilnik se je odklopil.\n");
            break;
        } else {
            printf("Sporocilo odjemalca: \n");
            parseMessage(&msg, recieved, 256);
            printf("%d\n", msg.type); 

            if(msg.type == 0){
                send(socket, name, strlen(name), 0);
            }else if(msg.type == 1){
                strcpy(freq, msg.content);
                //printArr(msg.content, 22);
            }else if(msg.type == 2){
                printf("Pred decript: %s\n", msg.content);

                //printArr(freq, 22);
                //printArr(msg.content, 22);
                decript(msg.content, freq, nameSize);
                //printArr(msg.content, 22);
                printf("Po decript: %s\n", msg.content);
            }

        }
    }

    close(socket);
    close(serverFd);
    return 0;
}