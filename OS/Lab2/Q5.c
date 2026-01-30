#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>  // Added for atoi()

#define MAX_FIB 50
long fib[MAX_FIB];

void* generate_fib(void* arg) {
    int n = *(int*)arg;
    if(n >= 2) {
        fib[0] = 0; fib[1] = 1;
        for(int i=2; i<n; i++) {
            fib[i] = fib[i-1] + fib[i-2];
        }
    }
    return NULL;
}

int main(int argc, char* argv[]) {
    if(argc < 2) {
        printf("Usage: ./Q5 10\n");
        return 1;
    }
    int n = atoi(argv[1]);
    if(n > MAX_FIB) n = MAX_FIB;
    
    pthread_t thread;
    pthread_create(&thread, NULL, generate_fib, &n);
    pthread_join(thread, NULL);
    
    printf("Fibonacci: ");
    for(int i=0; i<n; i++) printf("%ld ", fib[i]);
    printf("\n");
    return 0;
}

