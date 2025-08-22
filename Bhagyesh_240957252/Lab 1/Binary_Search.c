
#include <stdio.h>

int main()
{
    int n, target;
    printf("Enter number of elements and target element:\n");
    scanf("%d %d", &n, &target);
    int arr[n];
    printf("Enter array  elements:\n");
    for (int i=0; i<n; i++){
        scanf("%d", &arr[i]);
    }
    printf("\n");
    printf("Index of target is: ");
    int low = 0, high=n-1;
    while(low<=high){
            int mid = low + (high-low)/2;
    if (arr[mid]==target){
        printf("%d", mid);
        break;
    }
    else if (arr[mid]<target)
        low = mid+1;

    else
        high =mid-1;
    }

}



