#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int x = 10;
    int *y = (int *)malloc(sizeof(int));
    *y = 20;

    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    }

    if (pid > 0) {
        x = 50;
        *y = 60;
        printf("=== PARENT PROCESS ===\n");
        printf("Value of x: %d\n", x);
        printf("Address of x: %p\n", (void *)&x);
        printf("Value of *y (dynamic): %d\n", *y);
        printf("Address of y (dynamic): %p\n\n", (void *)y);
        wait(NULL); 
        free(y);    
    } else {
        sleep(1); 
        x = 100;
        *y = 200;
        printf("=== CHILD PROCESS ===\n");
        printf("Value of x: %d\n", x);
        printf("Address of x: %p\n", (void *)&x);
        printf("Value of *y (dynamic): %d\n", *y);
        printf("Address of y (dynamic): %p\n\n", (void *)y);
        free(y);    
        exit(0);
    }
    return 0;
}
