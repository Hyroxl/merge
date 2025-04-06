#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
void swap(int *a, int *b);
void randomize(int arr[], int *n, int* m);
void merge(int arr[], int l, int m, int r);
void mergeSort(int *arr[],int l, int r);
float runFork(int *id,int *arr[], int* size);
int main(int argc, char **argv)
{
    if(argc < 2)
    {
        printf("please retry with \"merge <VALUE>\"\n");
       return 1;
    } 
    printf("Do you want the output printed?(on larger datasets this may cause the program to be slower)Y/N:");
    char yOrN;
    scanf("%s", &yOrN);
    float totaltimeStart = (float)clock() / CLOCKS_PER_SEC;
    remove("randArr.txt");
    remove("sortedArr.txt");
    int size = atoi(argv[1]) + 1;
    int *randArr = malloc(size * sizeof *randArr);
    for (int i = 1; i < size; i++)
    {
        randArr[i] = i;
    }
    int id = fork();
    float timeElapsedThread1;
    float timeElapsedThread2;
    float threadTimeTotal;
    if (id == 0)
    {
        timeElapsedThread2 = runFork(&id, &randArr, &size);
    }else{
        timeElapsedThread1 = runFork(&id, &randArr, &size);
    }

    threadTimeTotal = timeElapsedThread1 + timeElapsedThread2;
    if (id != 0)
    {
    
        float totalTimeEnd;
        FILE *fptr;
        switch (yOrN)
        {
        case 'y':
            fptr = fopen("sortedArr.txt", "w");
            for (int j = 0; j < size; j++)
            {
                fprintf(fptr, "%d\n", randArr[j]);
            }
        fclose(fptr);
        break;
        case 'n':
        break;
        }
            free(randArr);            
            totalTimeEnd = (float)clock() / CLOCKS_PER_SEC;
            float timeElapsedTotal;
            timeElapsedTotal = totalTimeEnd - totaltimeStart;
            printf("Merge time:%f\nTotal program execution time:%f\n", threadTimeTotal, timeElapsedTotal);
    }
            return 0;
}

float runFork(int *id, int *arr[], int *size)
{
    int lim;
    int min;
    if (id == 0)
    {
        lim = *size / 2;
        min = 0;
    }
    else
    {
        lim = *size;
        min - *size / 2;
    }
    
    randomize(*arr, size, &lim);
    float timeStart = (float)clock() / CLOCKS_PER_SEC;
    mergeSort(arr, min, (lim - 1));
    float timeEnd = (float)clock() / CLOCKS_PER_SEC;
    return timeEnd - timeStart;
}
// A utility function to swap to integers
void swap (int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
// A function to generate a random permutation of arr[]
void randomize ( int arr[], int *n , int *m)
{
    // Use a different seed value so that we don't get same
    // result each time we run this program
    srand ( time(NULL) );
 
    // Start from the last element and swap one by one. We don't
    // need to run for the first element that's why i > 0
    for (int i = *n -1; i > *m; i--)
    {
        // Pick a random index from 0 to i
        int j = rand() % (i+1);
 
        // Swap arr[i] with the element at random index
        swap(&arr[i], &arr[j]);
    }
}
void merge(int arr[], int l, int m, int r) 
{ 
    int i, j, k; 
    int n1 = m - l + 1; 
    int n2 = r - m; 
  
    // Create temp arrays 
    int *L = malloc(n1 * sizeof *L);
    int *R = malloc(n2 * sizeof *L);
    // Copy data to temp arrays 
    // L[] and R[] 
    for (i = 0; i < n1; i++) 
        L[i] = arr[l + i]; 
    for (j = 0; j < n2; j++) 
        R[j] = arr[m + 1 + j]; 
  
    // Merge the temp arrays back 
    // into arr[l..r] 
    // Initial index of first subarray 
    i = 0; 
  
    // Initial index of second subarray 
    j = 0; 
  
    // Initial index of merged subarray 
    k = l; 
    while (i < n1 && j < n2) { 
        if (L[i] <= R[j]) { 
            arr[k] = L[i]; 
            i++; 
        } 
        else { 
            arr[k] = R[j]; 
            j++; 
        } 
        k++; 
    } 
  
    // Copy the remaining elements 
    // of L[], if there are any 
    while (i < n1) { 
        arr[k] = L[i]; 
        i++; 
        k++; 
    } 
  
    // Copy the remaining elements of 
    // R[], if there are any 
    while (j < n2) { 
        arr[k] = R[j]; 
        j++; 
        k++; 
    }
    free(L);
    free(R);
}

// l is for left index and r is 
// right index of the sub-array 
// of arr to be sorted 
void mergeSort(int *arr[], int l, int r) 
{ 
    if (l < r) { 
        // Same as (l+r)/2, but avoids 
        // overflow for large l and h 
        int m = l + (r - l) / 2; 
  
        // Sort first and second halves 
        mergeSort(arr, l, m); 
        mergeSort(arr, m + 1, r); 
  
        merge(*arr, l, m, r); 
    } 
} 
