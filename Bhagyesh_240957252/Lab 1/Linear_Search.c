#include <stdio.h>

int main()
{
    int n, target;
    printf("Enter number of elements and target element:\n");
    scanf("%d %d", &n, &target);
    int arr[n];
        printf("\n");
    printf("Enter array  elements:\n");
    for (int i=0; i<n; i++){
        scanf("%d", &arr[i]);
    }
    printf("\n");
    printf("Index of target is: ");

    for (int i=0; i<n; i++){
        if (arr[i]==target){
            printf("%d", i);
        }
    }
        printf("\n");


}
