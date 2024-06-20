#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include "errors.h"
#include <string.h>

#define PORT 8080


int naloga(char ime[], int size) {
	//int size = sizeof(ime) / sizeof(char);
	int ret = 0;
	for (int i = 0; i < size; i++) {
		ret += (int)(ime[i]);
	}
	return ret%8 +1;
}

void encrypt(char message[], char key[], int msgSize, int keySize) {
	for (int i = 0; i < msgSize; i++) {
		int buff = ((int)message[i] + (int)key[i % keySize]) % 128;
		message[i] = (char)buff;
	}
}

void decrypt(char message[], char key[], int msgSize, int keySize) {
	for (int i = 0; i < msgSize; i++) {
		int buff = ((int)message[i] - (int)key[i % keySize] + 128) % 128;
		message[i] = (char)buff;
	}
}

int main() {
    char ime[] = "Luka Klajnsek";
    int size = strlen(ime);
    printf("Naloga: ");
    int buff = naloga(ime, size);
    printf("%d\n", buff);

    struct sockaddr_in address;
    socklen_t addrlen = sizeof(address);
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    int serverFd = socket(AF_INET, SOCK_STREAM, 0);
    evalSocketFd(serverFd);



    int b = bind(serverFd, (struct sockaddr*)&address, sizeof(address));
    evalBind(b);

    int l = listen(serverFd, 3);
    evalListen(l);

    int newSocketFd = accept(serverFd, (struct sockaddr*)&address, &addrlen);
    evalAccept(newSocketFd);

    while (1) {
        char recieved[1024] = {0};
        int valread = recv(newSocketFd, recieved, sizeof(recieved), 0);

        if (valread == -1) {
            perror("recv failed");
            exit(EXIT_FAILURE);
        } else if (valread == 0) {
            printf("Client disconnected.\n");
            break;
        } else {
            printf("Sporocilo odjemalca: \n");
            printf("%s\n",recieved);
            if (strcmp(recieved, "Connected") == 0){
                send(newSocketFd, ime, strlen(ime), 0);
            }else{
                decrypt(recieved, "AXB0", strlen(recieved), 4);
                printf("Dekodirano: ");
                printf("%s\n",recieved);
            }
            

        }
    }

    close(newSocketFd);
    close(serverFd);

    return 0;
}