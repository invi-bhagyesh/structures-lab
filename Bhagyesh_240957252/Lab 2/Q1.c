#include <stdio.h>
#include <stdlib.h>

smallestFind(int *arr, int n){
    small = *arr
    for (int i=0; i<n; i++){
        if (small>*(arr+i)){
            small = *(arr+i);
        }
    }

}
int printArr(int *arr){
    for (int i=0; i<n; i++){
        printf("%d", *(arr+i));
    }
}
int main()
{
    int *arr;
    int n,i;
    printf("Enter number of elements: ");
    scanf("%d", &n);

    arr = (int*)malloc(n*sizeof(int));
    if (arr==NULL){
        printf("Memory not allocated");
        return 1;
    }
    //input
    printf("Enter %d elements", n);
    for (int i=0; i<n;i++){
        scanf("%d", &arr[i]);
    }

    s = smallestFind(arr, n);
    printf("Smallest element: %d", s);
    return 0;


}
