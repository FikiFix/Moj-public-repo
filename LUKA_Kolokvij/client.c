#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include "errors.h"

#define PORT 8080
#define SERVER_IP "127.0.0.1"

struct Message { //menda ne rabim
    int id;
    char content[256];
};

void encrypt(char message[], char key[], int msgSize, int keySize) {
    for (int i = 0; i < msgSize; i++) {
        int buff = ((int)message[i] + (int)key[i % keySize]) % 128;
        message[i] = (char)buff;
    }
}


int main(){
    struct sockaddr_in serverAdress;
    //int sock = 0, valread;

    int clientFd = socket(AF_INET, SOCK_STREAM, 0);
    evalSocketFd(clientFd);
    char message[1024] = {0};

    serverAdress.sin_family = AF_INET;
    serverAdress.sin_port = htons(PORT);



    int i = inet_pton(AF_INET, SERVER_IP, &serverAdress.sin_addr);
    evalInet(i);

    int c = connect(clientFd, (struct sockaddr *)&serverAdress, sizeof(serverAdress));
    evalConnect(c);

    strcpy(message, "Connected");
    send(clientFd, message, strlen(message), 0);
    printf("Message sent to server: %s\n", message);

    char buffer[1024] = {0};
    int valread = recv(clientFd, buffer, sizeof(buffer), 0);
    if (valread == -1) {
        perror("recv failed");
        exit(EXIT_FAILURE);
    } else if (valread == 0) {
        printf("Server disconnected.\n");
    } else {
        printf("Sporocilo serverja: %s\n", buffer);

        strcpy(message, buffer);
        encrypt(message, "AXB0", strlen(message), 4);
        send(clientFd, message, strlen(message), 0);
    }


}