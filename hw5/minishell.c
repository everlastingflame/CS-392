#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <pwd.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define max_tokens 64
#define max_input 256


void sigint_handler(int signal_number){
    printf("\nCannot terminate minishell using Ctrl-C.\n");
}


void sigchld_handler(int signal_number){
    int status; 
    pid_t pid;
    while ((pid = waitpid(-1, &status, WNOHANG)) > 0) {
        printf("pid %d done\n", pid);
    }
}

int main() {
    char input[max_input];
    char *tokens[max_tokens];

    if (signal(SIGINT, sigint_handler) == SIG_ERR) {
        fprintf(stderr, "Error: Cannot register signal handler. %s.\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    if (signal(SIGCHLD, sigchld_handler) == SIG_ERR) {
        fprintf(stderr, "Error: Cannot register signal handler. %s.\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    while (1) {
    char cwd[max_input];
    if(getcwd(cwd, sizeof(cwd)) == NULL){
        fprintf(stderr, "Error: Cannot get current working directory. %s.\n", strerror(errno));
        exit(EXIT_FAILURE);
    }  

    struct passwd *pass;
    uid_t uid = getuid();
    pass = getpwuid(uid);


    if(pass == NULL){
        fprintf(stderr, "Error: Cannot get passwd entry. %s.\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    printf("minishell:%s:%s$ ", pass->pw_name, cwd);

    if(fgets(input, max_input, stdin) == NULL){
        fprintf(stderr, "Error: Cannot read input. %s.\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    if(input[strlen(input) - 1] == '\n'){
        input[strlen(input) - 1] = '\0';
    }

    int bg = 0; 
    if(input[strlen(input) - 1] == '&'){
        bg = 1;
        input[strlen(input) - 1] = '\0';
    }

    int count = 0;
    tokens[count++] = strtok(input, " ");
    while(tokens[count - 1] != NULL){
        tokens[count++] = strtok(NULL, " ");
    }

    if(tokens[0] == NULL){
        continue;
    }

    if(strcmp(tokens[0], "exit") == 0){
        if(tokens[1] != NULL || bg){
            fprintf(stderr, "Error: Too many arguments to exit. \n");
        }
        else{
            exit(EXIT_SUCCESS);
        }
    }

    else if (strcmp(tokens[0], "cd") == 0){
        if(tokens[1] == NULL || strcmp(tokens[1], "~") == 0){
            chdir(getpwuid(getuid())->pw_dir);
        }

        else if (tokens[2] != NULL){
            fprintf(stderr, "Error: Too many arguments to cd.\n");
        }

        else if (chdir(tokens[1]) < 0){
            fprintf(stderr, "Error: Cannot change directory to %s. %s.\n", tokens[1], strerror(errno));
        }
    }

    else{
        pid_t pid = fork();
        if(pid < 0){
            fprintf(stderr, "Error: fork() failed. %s.\n", strerror(errno));
            exit(EXIT_FAILURE);
        }

        else if (pid == 0){
            if(execvp(tokens[0], tokens) < 0){
                fprintf(stderr, "Error: Cannot execute %s. %s.\n", tokens[0], strerror(errno));
                exit(EXIT_FAILURE);
            }
        }

        else{
            if (!bg){
                int status;
                if(waitpid(pid, &status, 0) < 0){
                    fprintf(stderr, "Error: wait() failed. %s.\n", strerror(errno));
                }
            }
            else{
                printf("pid: %d cmd: %s\n", pid, tokens[0]);
            }
        }
     }
  }
}




