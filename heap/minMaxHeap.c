#include<stdio.h>
#include<string.h>

#define HSIZE 100
int heap[HSIZE];
int currI = 0;


#define OPSIZE 6
void insert(int);
void delete();
void printHeap(){
    for (int i = 1; i <= currI; i++) printf("%d ", heap[i]);
    printf("\n");
}


int main(){
    char operation[OPSIZE];
    scanf("%s", operation);

    while (strcmp(operation, "exit") != 0){
        if (strcmp(operation, "insert") == 0){
            int x;
            scanf("%d", &x);
            getchar();
            insert(x);
            printHeap();
        }else if (strcmp(operation, "delete") == 0){
            getchar();
            delete();
            printHeap();
        }
        scanf("%s", operation);
    }

    printHeap();
    return 0;
}


int whichLevel(int index){
    int l = 1;
    int count = 0;
    while (l <= index){
        l *= 2;
        count += 1;
    }
    return count;
}

void swapNode(int aI, int bI){
    int temp = heap[aI];
    heap[aI] = heap[bI];
    heap[bI] = temp;
}

void minUpSwap(int index){
    if (index/4 >= 1 && heap[index/4] > heap[index]){
        swapNode(index/4, index);
        minUpSwap(index/4);
    }
}

void maxUpSwap(int index){
    if (index/4 >= 2 && heap[index/4] < heap[index]){
        swapNode(index/4, index);
        maxUpSwap(index/4);
    }
}

void insert(int x){
    heap[++currI] = x;
    int xLevel = whichLevel(currI);

    // x on max level, p on min level.
    if (xLevel % 2 == 0){
        if (currI != 1 && heap[currI / 2] > x){
            swapNode(currI/2, currI);
            minUpSwap(currI/2);
        }else if (currI != 1 && heap[currI / 2] < x){
            maxUpSwap(currI);
        }
    }
    // x on min level, p on max level.
    else if (xLevel % 2 == 1){
        if (currI != 1 && heap[currI / 2] > x){
            minUpSwap(currI);
        }else if (currI != 1 && heap[currI / 2] < x){
            swapNode(currI/2, currI);
            maxUpSwap(currI/2);
        }
    }


}

int findMinChild(int index){
    if (currI < index * 2){
        return -1;
    }else if (currI < index * 2 + 1){
        return index * 2;
    }else{
        return heap[index*2] < heap[index*2+1] ? index*2 : index*2+1;
    }
}

int findMinGrandChild(int index){
    if (currI < index * 4) return -1;
    int recordI = index * 4;
    int min = heap[index*4];
    for (int i = index * 4 + 1; i <= index * 4 + 3; i++){
        if (currI < i) break;
        if (min > heap[i]){
            recordI = i;
            min = heap[i];
        }
    }
    return recordI;
}

void minDownSwap(int index){
    int minGrandChild = findMinGrandChild(index);
    if (minGrandChild != -1 && heap[minGrandChild] < heap[index]){
        swapNode(minGrandChild, index);
        minDownSwap(minGrandChild);
    }

    // check if bigger than parent or two children
    if (index > 1 && heap[index/2] < heap[index]){
        swapNode(index/2, index);
        minDownSwap(index);
    }else{
        int minChild = findMinChild(index);
        if (minChild != -1 && heap[minChild] < heap[index]){
            swapNode(minChild, index);
            minDownSwap(index);
        }
    }

}

void delete(){
    heap[1] = heap[currI--];

    // check two child whether they are smaller than myself ?
    int minChild = findMinChild(1);
    int minGrandChild = findMinGrandChild(1);

    if (minChild != -1 && heap[minChild] < heap[1]){
        swapNode(minChild, 1);
        minDownSwap(1);

    }else if (minGrandChild != -1 && heap[minGrandChild] < heap[1]){
        swapNode(minGrandChild, 1);
        minDownSwap(minGrandChild);
    }
}
