#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;
int partition_find_pivot(int* array, int n, int pivot_index){
    int i = 1, j = 1;
    swap(array[0], array[pivot_index]);
    while(array[j] < array[0] && j < n){
        j++;i++;
    }
    while(j < n){
        if(array[j] > array[0]){j++;}
        else{//includes the case where array[j] = array[0]
            swap(array[j], array[i]);
            j++;i++;
        }
    }
    swap(array[i - 1], array[0]);
    return i - 1;
}
void quickSort(int* array, int n){  
    if(n < 2) return;
    srand(time(0));
    int randomIndex = rand() % n;
    int pivot = partition_find_pivot(array, n, randomIndex);
    //smart-move time
    quickSort(array, pivot);
    quickSort(array + pivot + 1, n - 1 - pivot); //move the pointer to the beginning of the right half
    //doing the above trick stops me from creating leftA and rightA array and them stitching them back to array.
  
}
int main(){
    int array[] = {8, 82, 33, 90, 10, 60, 88, 81, 24, 1};
    quickSort(array, 10);
    for(int elem : array){ cout << elem<<" ";}
    return 0;
}