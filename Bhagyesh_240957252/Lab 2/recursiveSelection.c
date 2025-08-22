//recursive selection sorting
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int recursiveSelection(int *start, int *end)
{
    if (start>=end-1){
        return;
    }
        int *min =start;
        for (int *j=start+1;j<end;j++){
            if (*(min)>*(j)){
                min = j;
            }
        }
        //swap
        int temp = *(min);
        *(min) = *(start);
        *(start) = temp;

    recursiveSelection(start+1, end);

}

int printArr(int *arr, int n){
    for (int i=0; i<n; i++){
        printf("%d\t", *(arr+i));
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
        scanf("%d", (arr+i));
    }

    //output
    recursiveSelection(arr, arr+n);
    printf("Sorting using Selection sort...\n");
    sleep(1);
    printArr(arr, n);
    return 0;
}
