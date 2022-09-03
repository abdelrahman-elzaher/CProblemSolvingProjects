int partition (int arr[], int low, int high) 
{ 
    int pivot = arr[high]; // pivot 
    int i = (low - 1); // Index of smaller element and indicates the right position of pivot found so far
  
    for (int j = low; j <= high - 1; j++) 
    { 
        // If current element is smaller than the pivot 
        if (arr[j] < pivot) 
        { 
            i++; // increment index of smaller element 
                int temp=0;
                temp=arr[i];
                arr[i]=arr[j];
                arr[j]=temp;            
        } 
    } 
    int temp=0;
    temp=arr[i+1];
    arr[i+1]=arr[high];
    arr[high]=temp;
    return (i + 1); 
} 
  
/* The main function that implements QuickSort 
arr[] --> Array to be sorted, 
low --> Starting index, 
high --> Ending index */
void quickSort(int arr[], int low, int high) 
{ 
    if (low < high) 
    { 
        /* pi is partitioning index, arr[p] is now 
        at right place */
        int pi = partition(arr, low, high); 
  
        // Separately sort elements before 
        // partition and after partition 
        quickSort(arr, low, pi - 1); 
        quickSort(arr, pi + 1, high); 
    } 
} 
void PrintArr(int *arr,int length)
{
    for(int i=0;i<length;i++)
    {
        printf("%d ",arr[i]);
    }
    printf("\n");
}
int pairs(int k, int arr_count, int* arr) {

int i=arr_count-1,j=1;
int count=0;

//SortArray(arr,arr_count);
PrintArr(arr,arr_count);
while((i-j)>=0)
{
    if(arr[i]-arr[i-j]==k)
    {count++;
    i--;
    j=1;}
        else if(arr[i]-arr[i-j]>k)
    {
        i--;
        j=1;

    }
    else {
        j++;
    }    
}
return count;
}
