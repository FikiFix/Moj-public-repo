#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include "napake.h"
#include "komunikacija.h"
#include <time.h>

#define PORT 8080
#define SERVER_IP "127.0.0.1"
#define PACKET_SIZE 256 + sizeof(int) + 1

void sendStruct(int clientFd, struct Message* msg){ //pošlje strukturo na socket
    char buffer[PACKET_SIZE];
    stringifyMessage(msg, buffer, 256);
    send(clientFd, buffer, PACKET_SIZE, 0);
}

int randInt(int min, int max) { //random int

    int randomNumber = rand() % (max - min + 1) + min;

    return randomNumber;
}


void generateFreq(int* ret, int size){
    for(int i = 0; i < size; i++){
        ret[i] = randInt(100, 1000)%256;
    }
}

void encript(char* ret, char* freq, int size) {
    for(int i = 0; i < size; i++) {
        if(i % 2 == 0) {
            int buff = ((int)freq[i] + (int)ret[i]);
            ret[i] = (char)buff;
        } else {
            int buff = ((int)ret[i] - (int)freq[i]);
            ret[i] = (char)buff;
        }
    }
}


void printArr(char* arr, int size){
    printf("Array: ");
    for(int i = 0; i < size; i++){
        printf("%d ", (int)arr[i]);
    }printf("\n");
}
void freqToChar(char* ret, int* freq, int size){
        for(int i = 0; i < size; i++){
            ret[i] = (char)freq[i];
    }
}



int main(){
    srand(time(NULL));
    struct sockaddr_in serverAdress;
    serverAdress.sin_family = AF_INET;
    serverAdress.sin_port = htons(PORT);
    struct Message msg;  //to je buffer za posiljanje sporočil na server

    int clientFd = socket(AF_INET, SOCK_STREAM, 0);
    checkFd(clientFd);


    int i = inet_pton(AF_INET, SERVER_IP, &serverAdress.sin_addr);
    checkInet(i);

    int c = connect(clientFd, (struct sockaddr *)&serverAdress, sizeof(serverAdress));
    checkConnect(c);

    /////////tu damo upodno sporočilo računalniku ki mi pove da smo povezani
    strcpy(msg.content, "Connected");
    msg.type = 0;
    ////////

    sendStruct(clientFd, &msg);
    printf("Message sent to server: %s\n", msg.content);

    char buffer[1024] = {0};
    int status = recv(clientFd, buffer, sizeof(buffer), 0);
    if (status == -1) {
        perror("failedv recieve");
        exit(EXIT_FAILURE);
    } else if (status == 0) {
        printf("Server disconnected.\n");
    } else {
        printf("Sporocilo serverja: %s\n", buffer);
        int buffSize = strlen(buffer);
        printf("Velikost: %d\n", buffSize);
        int freq[buffSize];
        generateFreq(freq, buffSize);


        freqToChar(msg.content, freq, buffSize);
        encript(buffer, msg.content, buffSize);

        printf("Po encript: %s\n",buffer);
        
        
        msg.type = 1;
        sendStruct(clientFd, &msg);

        strcpy(msg.content, buffer);
        msg.type = 2;
        sendStruct(clientFd, &msg);

    }
    return 0;
}