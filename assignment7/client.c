#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>


int main(int argc, char *argv[]) {
    
    if (argc != 2) {
        printf("Usage: %s <port>\n", argv[0]);
        return -1;
    }    
    
    int sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[1024] = {0};
    int PORT = atoi(argv[1]);

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\nSocket creation error\n");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        printf("\nInvalid address/ Address not supported\n");
        return -1;
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("\nConnection Failed \n");
        return -1;
    }

    double number;
    char input[1024] = {0};

    while (1) {
        printf("Enter a number to add (or 'q' to quit): ");
        scanf("%s", input);

        if (strcmp(input, "Q") == 0 || strcmp(input, "q") == 0) {
            break;
        }

        number = atof(input);
        sprintf(buffer, "%.2lf", number);
        send(sock, buffer, strlen(buffer), 0);

        int valread = read(sock, buffer, 1024);
        buffer[valread] = '\0';
        double sum = atof(buffer);
    }

    close(sock);
    return 0;
}