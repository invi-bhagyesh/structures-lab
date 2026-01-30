#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>  // Added for exit()

int main() {
    if (fork() == 0) {
        printf("Child PID=%d exiting\n", getpid());
        exit(0);
    }
    printf("Parent sleeping...\n");
    sleep(30);  // Reduced time
    printf("Parent done\n");
    return 0;
}

