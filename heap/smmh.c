#include<stdio.h>
#include<string.h>

#define HSIZE 100
int heap[HSIZE];
int currI = 1;
void printHeap(){
    printf("- ");
    for (int i = 2; i <= currI; i++) printf("%d ", heap[i]);
    printf("\n");
}

#define OPSIZE 10
void insert(int);
void deleteMin();
void deleteMax();

int main(){
    char operation[OPSIZE];
    scanf("%s", operation);

    while (strcmp(operation, "exit") != 0){
        if (strcmp(operation, "insert") == 0){
            int x;
            scanf("%d", &x);
            getchar();
            insert(x);
            
        }else if (strcmp(operation, "deleteMin") == 0){
            getchar();
            deleteMin();
        }else if (strcmp(operation, "deleteMax") == 0){
            getchar();
            deleteMax();
        }
        printHeap();
        scanf("%s", operation);
    }


    return 0;
}


void swapNode(int a, int b){
    int temp = heap[a];
    heap[a] = heap[b];
    heap[b] = temp;
}











int findSibling(int index, int *min){
    if (index %2 == 0){
        *min = 1;
        if (currI < index + 1) return -1;
        return index + 1;
    }else{
        *min = 0;
        return index - 1;
    }
}


int checkSibling(int index){
    int min = 0;
    int sI = findSibling(index, &min);
    

    if (min == 1 && (sI != -1 && heap[sI] < heap[index])){
        swapNode(sI, index);
        index = sI;
    }else if (min == 0 && heap[sI] > heap[index]){
        swapNode(sI, index);
        index = sI;
    }
    return index;
}

void checkInsertChange(int );
void checkGrandParentChild(int index){
    int gI = (index / 4 >= 1) ? index/4 : -1;
    if (gI == -1) return;

    if (heap[gI * 2] > heap[index]){
        swapNode(gI * 2, index);
        checkSibling(index);
        checkInsertChange(gI * 2);
    }else if (heap[gI * 2 + 1] < heap[index]){
        swapNode(gI * 2 + 1, index);
        checkSibling(index);
        checkInsertChange(gI * 2 + 1);
    }

}

void checkInsertChange(int index){
    index = checkSibling(index);
    checkGrandParentChild(index);
}

void insert(int x){
    heap[++currI] = x;
    
    checkInsertChange(currI);
}

int minChildSiblingChild(int index, int sIndex){
    if (currI < index * 2){
        return -1;
    }else if (currI < sIndex * 2){
        return index * 2;
    }else{
        return heap[index*2] < heap[sIndex*2] ? index*2 : sIndex*2;
    }
}

int maxChildSiblingChild(int index, int sIndex){
    // sIndex is smaller than index.
    if (currI < sIndex * 2 + 1){
        return -1;
    }else if (currI < index * 2 + 1){
        return sIndex*2+1;
    }else{
        return heap[sIndex*2+1] > heap[index*2+1] ? sIndex*2+1 : index*2+1; 
    }
}

void checkDeleteChange();
void checkChildAndSiblingChild(int index){
    int min = 0;
    int sI = findSibling(index, &min);

    if (min == 1){
        if (sI == -1) return;
        int changeI = minChildSiblingChild(index, sI);
        if (changeI != -1 && heap[changeI] < heap[index]){
            swapNode(changeI, index);
            checkDeleteChange(changeI);
        }
    }else{
        int changeI = maxChildSiblingChild(index, sI);
        if (changeI != -1 && heap[changeI] > heap[index]){
            swapNode(changeI, index);
            checkDeleteChange(changeI);
        }
    }
}


void checkDeleteChange(int index){
    checkSibling(index);
    checkChildAndSiblingChild(index);
}

void deleteMin(){
    heap[2] = heap[currI--];
    checkDeleteChange(2);
}

void deleteMax(){
    heap[3] = heap[currI--];
    checkDeleteChange(3);
}