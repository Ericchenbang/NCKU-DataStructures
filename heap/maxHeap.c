#include<stdio.h>
#define SIZE 100

int maxHeap[SIZE];
int currI = 0;

void swapNode(int a, int b){
    int temp = maxHeap[a];
    maxHeap[a] = maxHeap[b];
    maxHeap[b] = temp;
}

void upSwap(int index){
    if (index > 1 && maxHeap[index / 2] < maxHeap[index]){
        swapNode(index / 2, index);
        upSwap(index / 2);
    }
}

void insert(int x){
    maxHeap[++currI] = x;
    upSwap(currI);
}

int search(int x){
    for (int i = 1; i <= currI; i++){
        if (maxHeap[i] == x){
            return i;
        }
    }
    return -1;
}

int findMaxChildIndex(int index){
    if (index * 2 > currI){
        return -1;
    }else if (index * 2 + 1 > currI){
        return index * 2;
    }else{
        return maxHeap[index * 2] > maxHeap[index * 2 + 1] ? index * 2 : index * 2 + 1;
    }
}

void downSwap(int index){
    int maxChildIndex = findMaxChildIndex(index);
    printf("%d\n", maxChildIndex);
    if (maxChildIndex != -1 && maxHeap[maxChildIndex] > maxHeap[index]){
        swapNode(maxChildIndex, index);
        downSwap(maxChildIndex);
    }
}

void delete(int x){
    int index = search(x);
    if (index != -1){
        if (index == currI){
            currI -= 1;
        }else {
            maxHeap[index] = maxHeap[currI--];
            upSwap(index);
            downSwap(index);
        }
    }
}


int main(){
    char input[SIZE];
    scanf("%s", input);

    
    int x;
    while (input[0] != 'e'){
        if (input[0] == 'i'){
            scanf("%d", &x);
            insert(x);
        }else if (input[0] = 'd'){
            scanf("%d", &x);
            delete(x);
        }
        scanf("%s", input);
    }

    for (int i = 1; i <= currI; i++){
        printf("%d ", maxHeap[i]);
    }

    return 0;
}
