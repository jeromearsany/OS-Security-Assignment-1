#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main() {
    int pipe_fd[2];
    pid_t pid;
    char buffer[256];
    char *message = "SECRET: OS Security is passing!";

    if (pipe(pipe_fd) == -1) {
        perror("Pipe failed");
        exit(1);
    }

    pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    }

    if (pid > 0) { 
        close(pipe_fd[0]); 
        printf("[Parent] Sending message to child...\n");
        write(pipe_fd[1], message, strlen(message) + 1);
        close(pipe_fd[1]); 
        wait(NULL); 
    } else { 
        close(pipe_fd[1]); 
        read(pipe_fd[0], buffer, sizeof(buffer));
        close(pipe_fd[0]); 

        if (strncmp(buffer, "SECRET:", 7) == 0) {
            printf("[Child] Message is VALID. Content: %s\n", buffer);
        } else {
            printf("[Child] ERROR: Invalid message format! Rejecting.\n");
        }
        exit(0);
    }
    return 0;
}
