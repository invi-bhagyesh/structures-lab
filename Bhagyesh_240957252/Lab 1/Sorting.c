#include <stdio.h>
void insertionSort(int arr[], int n) {

    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }

        arr[j + 1] = key;
    }
}



void selectionSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int min = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[min]) {
                min = j;
            }
        }

        int temp = arr[min];
        arr[min] = arr[i];
        arr[i] = temp;
    }
}

void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {


        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]){

                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int n;
    printf("Enter array size:\n");
    scanf("%d", &n);
    int arr[n];
    printf("Enter array elements:\n");
    for (int i=0; i<n; i++){
        scanf("%d", &arr[i]);
    }

    printf("Original array: \n");
    printArray(arr, n);
    printf("Enter for\n selectionSort: 1\n bubbleSort: 2\n insertionSort:3\n");
    int sort;
    scanf("%d", &sort);
    switch(sort)
    {
    case 1:
         selectionSort(arr, n);
         break;

    case 2:
        bubbleSort(arr, n);
        break;
    case 3:
        insertionSort(arr, n);
        break;
    }

    printf("Sorted array: \n");
    printArray(arr, n);

    return 0;


}



