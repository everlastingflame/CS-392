#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <string.h>

#define MSGSIZE 60

void parent(int rpipe[], int wpipe[]) {
    srand(time(NULL));
    int chosen_number = (rand() % 32) + 1;
    char message[MSGSIZE];

    snprintf(message, MSGSIZE, "Guess a number between 1 and 32\n");
    write(wpipe[1], message, MSGSIZE);

    while (1) {
        read(rpipe[0], message, MSGSIZE);
        int guess = atoi(message);

        if (guess == chosen_number) {
            snprintf(message, MSGSIZE, "bingo");
        } else if (guess < chosen_number) {
            snprintf(message, MSGSIZE, "too low");
        } else {
            snprintf(message, MSGSIZE, "too high");
        }
        write(wpipe[1], message, MSGSIZE);

        if (guess == chosen_number) {
            wait(NULL);
            exit(0);
        }
    }
}

void child(int rpipe[], int wpipe[]) {
    char message[MSGSIZE];
    int guess;

    read(rpipe[0], message, MSGSIZE);
    printf("%s", message);

    while (1) {
        printf("Enter your guess: ");
        scanf("%d", &guess);

        snprintf(message, MSGSIZE, "%d", guess);
        write(wpipe[1], message, MSGSIZE);

        read(rpipe[0], message, MSGSIZE);
        printf("%s\n", message);

        if (strcmp(message, "bingo") == 0) {
            exit(0);
        }
    }
}

int main() {
    int parent2child[2], child2parent[2];

    if (pipe(parent2child) == -1 || pipe(child2parent) == -1) {
        perror("pipe");
        exit(1);
    }

    pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(1);
    } else if (pid == 0) { // Child process
        close(parent2child[1]);
        close(child2parent[0]);
        child(parent2child, child2parent);
    } else { // Parent process
        close(parent2child[0]);
        close(child2parent[1]);
        parent(child2parent, parent2child);
    }

    return 0;
}