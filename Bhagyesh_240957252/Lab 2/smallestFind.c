#include <stdio.h>
#include <stdlib.h>

int smallestFind(int *arr, int n){
    int small = *arr;
    for (int i=0; i<n; i++){
        if (small>*(arr+i)){
            small = *(arr+i);
        }
    }
    return small;

}
int printArr(int *arr, int n){
    for (int i=0; i<n; i++){
        printf("%d", *(arr+i));
    }
}
int main()
{
    int *arr;
    int n,i;
    printf("Enter number of elements:\n");
    scanf("%d", &n);

    arr = (int*)malloc(n*sizeof(int));
    if (arr==NULL){
        printf("Memory not allocated");
        return 1;
    }
    //input
    printf("Enter %d elements\n", n);
    for (int i=0; i<n;i++){
        scanf("%d", &arr[i]);
    }

    //output
    int s = smallestFind(arr, n);
    printf("Smallest element: %d", s);
    return 0;


}
