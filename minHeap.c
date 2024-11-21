#include<stdio.h>
#include<stdlib.h>
#define SIZE 100
int output[SIZE];
int currI = 0;

void swapNode(int a, int b){
    int temp = output[a];
    output[a] = output[b];
    output[b] = temp;
}

void upSwap(int index){
    if (index > 1 && output[index] < output[index / 2]){
        swapNode(index, index / 2);
        upSwap(index / 2);
    }
}
int findMinChildIndex(int index){
    if (currI < index * 2){
        return -1;
    }else if (currI < index * 2 + 1){
        return index * 2;
    }else{
        return output[index * 2] < output[index * 2 + 1] ? index * 2 : index * 2 + 1;
    }
}
void downSwap(int index){
    int minChildIndex = findMinChildIndex(index);
    while (minChildIndex != -1 && output[minChildIndex] < output[index]){
        swapNode(minChildIndex, index);
        index = minChildIndex;
        minChildIndex = findMinChildIndex(index);
    }

}
void insert(int data){
    output[++currI] = data;
    upSwap(currI); 
}
int search(int x){
    for (int i = 1; i <= currI; i++){
        if (output[i] == x){
            return i;
        }
    }
    return -1;
}
void delete(int data){
    int index = search(data);
    if (index == -1 ) return;
    swapNode(index, currI);
    currI -= 1;

    upSwap(index);
    downSwap(index);
}

void printMinHeap(){
    for (int i = 1; i <= currI; i++){
        printf("%d ", output[i]);
    }
    printf("\n");
}


int main(){ 

    char operation[6];
    scanf("%s", operation);
    int x;
    while(1){
        if (operation[0] == 'e'){
            break;
        }else if (operation[0] == 'i'){
            scanf("%d", &x);
            insert(x);
        }else{
            scanf("%d", &x);
            delete(x);
        }
        scanf("%s", operation);
    }
    printMinHeap();
    return 0;
}