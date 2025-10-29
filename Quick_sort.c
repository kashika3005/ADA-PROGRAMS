# include <stdio.h>
# include <stdlib.h>
# include <time.h>

void swap(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);  
    return i + 1;                    
}


void quickSort(int arr[], int low, int high) {
    if (low < high) {
        
        int pi = partition(arr, low, high);

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void generate_random_array(int arr[],int n){
    for(int i=0;i<n;i++){
        arr[i]=rand() % 100000; 
    }
}

int main(){
    int n;
    
    printf("Enter number of elements:");
    scanf("%d",&n); 

    int* arr= (int*)malloc(n*sizeof(int)); 
    if (arr==NULL){
        printf("Memory allocation failed");
        return 0;
    }

    generate_random_array(arr,n);
    clock_t start=clock();
    for (int i=0; i<100; i++){ 
        quickSort(arr,0 ,n-1);
    }
    clock_t end=clock();

    double time_taken = ((double)end-start)/CLOCKS_PER_SEC/100.0;  
    
    printf("Time taken to sort %d elements is : %f seconds\n",n,time_taken);
    free (arr);

    return 0;
}