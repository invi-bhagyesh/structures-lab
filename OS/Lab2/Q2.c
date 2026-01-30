#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
int main() {
    pid_t pid = fork();
    
    if (pid == 0) {
        execl("./Q1", "Q1", NULL);  
        perror("exec failed");
        exit(1);
    } else {
        wait(NULL);
        printf("Parent: exec child completed\n");
    }
    return 0;
}

