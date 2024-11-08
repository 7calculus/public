#include <iostream>

using namespace std;

void merge(int leftArray[], int rightArray[], int array[], int size){
    int mid = size/2, mainIndex = 0, i = 0, j = 0;
    while(i < mid && j < size - mid){
        if(leftArray[i] < rightArray[j]){
            array[mainIndex] = leftArray[i];
            i++;
        } else {
            array[mainIndex] = rightArray[j];
            j++;
        }
        mainIndex++;
    }
    while(i < mid){
        array[mainIndex] = leftArray[i];
        i++;
        mainIndex++;
    }
    while(j < size - mid){
        array[mainIndex] = rightArray[j];
        j++;
        mainIndex++;
    }
}

void mergeSort(int array[], int size){
    if(size < 2) return;
    int mid = size/2;
    int leftArray[mid], rightArray[size - mid], j = 0;
    for(int i = 0; i < size; i++){
        if(i < mid){
            leftArray[i] = array[i];
        }
        else{
            rightArray[j] = array[i];
            j++; 
        }
    }

    mergeSort(leftArray, mid);
    mergeSort(rightArray, size - mid);
    merge(leftArray, rightArray, array, size);
}

int main(){
    freopen("input.txt", "r", stdin);
    int size = 3200, i = 0, x, array[size]; //here the size indicates the number of numbers u wanna include in the array from a large set in "intput.txt"
    while(cin>>x && i < size){ //to stop including inputs after the size has reached, instead of having all of
        array[i] = x;       // them which would exceed the array capacity if the array capacity is less than size                
        i++;
    }
    mergeSort(array, size);
    for(int j = 0; j < size; j++){
        cout<<array[j]<<" ";
    }

    return 0;
}