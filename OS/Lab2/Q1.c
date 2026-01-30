#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main() {
    pid_t pid = fork();
    
    if (pid == 0) { // Child
        printf("Child: PID=%d, PPID=%d\n", getpid(), getppid());
        sleep(2);
    } else { // Parent
        printf("Parent: PID=%d, Child PID=%d\n", getpid(), pid);
        wait(NULL);
        printf("Parent: Child completed\n");
    }
    return 0;
}
