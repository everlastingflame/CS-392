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
    
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    int PORT = atoi(argv[1]);


    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }


    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }


    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }


    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d...\n", PORT);


    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }

    printf("Connection accepted from client %s:%d\n", inet_ntoa(address.sin_addr), ntohs(address.sin_port));


    double sum = 0;
    char buffer[1024] = {0};

    while(1) {
        int valread = read(new_socket, buffer, 1024);
        if (valread <= 0) {
            break;
        }

        double number = atof(buffer);
        sum += number;
        printf("Number: %lf, current sum is %lf\n", number, sum);

        sprintf(buffer, "%.2lf", sum);
        send(new_socket, buffer, strlen(buffer), 0);
    }

    
    printf("Client disconnected, total sum is %lf\n", sum);

    close(new_socket);
    close(server_fd);


    return 0;
}
