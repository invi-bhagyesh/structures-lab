#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <stdlib.h>

#define MAX 100
int arr[MAX]; int n;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void* bubble_sort(void* arg) {
    clock_t start = clock();
    pthread_mutex_lock(&lock);
    for(int i=0; i<n-1; i++)
        for(int j=0; j<n-i-1; j++)
            if(arr[j]>arr[j+1]) {
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
    pthread_mutex_unlock(&lock);
    printf("Bubble sort: %.3f sec\n", (double)(clock()-start)/CLOCKS_PER_SEC);
    return NULL;
}

void* selection_sort(void* arg) {
    clock_t start = clock();
    pthread_mutex_lock(&lock);
    for(int i=0; i<n-1; i++) {
        int min_idx = i;
        for(int j=i+1; j<n; j++)
            if(arr[j] < arr[min_idx]) min_idx = j;
        int temp = arr[min_idx];
        arr[min_idx] = arr[i];
        arr[i] = temp;
    }
    pthread_mutex_unlock(&lock);
    printf("Selection sort: %.3f sec\n", (double)(clock()-start)/CLOCKS_PER_SEC);
    return NULL;
}

int main(int argc, char* argv[]) {
    if(argc < 3) {
        printf("Usage: ./Q4 5 64 34 25 12 22\n");
        return 1;
    }
    n = atoi(argv[1]);
    for(int i=0; i<n; i++) arr[i] = atoi(argv[i+2]);
    
    printf("Original: ");
    for(int i=0; i<n; i++) printf("%d ", arr[i]);
    printf("\n");
    
    pthread_t t1, t2;
    pthread_create(&t1, NULL, bubble_sort, NULL);
    pthread_create(&t2, NULL, selection_sort, NULL);
    
    pthread_join(t1, NULL); pthread_join(t2, NULL);
    
    printf("Final sorted: ");
    for(int i=0; i<n; i++) printf("%d ", arr[i]);
    printf("\n");
    return 0;
}

