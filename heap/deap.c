/** User input insert, deleteMin or deleteMax.
 *  To be careful: when deleteMax(), the corresponding node may also be the child of the corresponding node,
 *  so if the child are bigger than myself, it should be change!
 */


#include<stdio.h>
#include<string.h>

#define HSIZE 100
int heap[HSIZE];
int currI = 1;

void printHeap(){
    printf("- ");
    for (int i = 2; i <= currI; i++){
        printf("%d ", heap[i]);
    }
    printf("\n");
}

#define OPSIZE 10
void insert(int);
void deleteMin();
void deleteMax();

int main(){
    char operation[OPSIZE];
    scanf("%s", operation);
    getchar();

    while (strcmp(operation, "exit") != 0){
        if (strcmp(operation, "insert") == 0){
            int x;
            scanf("%d", &x);
            printf("op = %s, x = %d\n", operation, x);
            insert(x);
        }else if (strcmp(operation, "deleteMin") == 0){
            printf("op = %s\n", operation);
            deleteMin();
        }else if (strcmp(operation, "deleteMax") == 0){
            printf("op = %s\n", operation);
            deleteMax();
        }
        printHeap();
        scanf("%s", operation);
        getchar();
    }


    return 0;
}

int findCorresponding(int index, int *min){
    if (index == 2){
        *min = 1;
        return -1;
    }

    // which level is this index on ?
    int multi = 2;   
    while (multi <= index){
        multi *= 2;
    }
    int lowerBound = multi / 2, upperBound = multi - 1;
    int distract = (upperBound + 1 - lowerBound) / 2;
    printf("lower = %d, upper = %d, distarct = %d\n", lowerBound, upperBound, distract);

    if (index >= lowerBound + distract){
        *min = 0;
        return index - distract;
    }else{
        *min = 1;
        if (currI < index + distract) return (index + distract) / 2;
        else return index + distract;
    }
}

void swapNode(int a, int b){
    int temp = heap[a];
    heap[a] = heap[b];
    heap[b] = temp;
}

void minUpSwap(int index){
    if (index > 2 && heap[index / 2] > heap[index]){
        swapNode(index/2, index);
        minUpSwap(index/2);
    }
}

void maxUpSwap(int index){
    if (index > 3 && heap[index / 2] < heap[index]){
        swapNode(index / 2, index);
        maxUpSwap(index / 2);
    }
}

int findMaxChild(int);

void checkCorresponding(int corr, int index, int min){
    if (min == 1){
        if (heap[corr] < heap[index]){
            swapNode(corr, index);
            minUpSwap(index);
            maxUpSwap(corr);
        }else{
            minUpSwap(index);
        }
    }else{
        if (heap[corr] > heap[index]){
            swapNode(corr, index);
            minUpSwap(corr);
            maxUpSwap(index);
        }else if (currI < index * 2 + 1){
            /** corr maybe the children of current corr. */
            int change = 0, changeIndex;
            if (currI < index * 2){
                int maxCorrChild = findMaxChild(corr);
                if (maxCorrChild != -1 && heap[maxCorrChild] > heap[index]){
                    change = 1;
                    changeIndex = maxCorrChild;
                }
            }else if (currI < index * 2 + 1){
                if (corr * 2 + 1 <= currI && heap[corr*2+1] > heap[index]){
                    change = 1;
                    changeIndex = corr*2+1;
                }
            }

            if (change){
                swapNode(changeIndex, index);
                /** I think is no need to upswap, but in case. */
                minUpSwap(changeIndex);
                maxUpSwap(index);
            }

        }else{
            maxUpSwap(index);
        }
    }
}



void insert(int x){
    heap[++currI] = x;
    if (currI == 2) return;
    int min = 0;
    int correspondingI = findCorresponding(currI, &min);
    printf("corres = %d\n", correspondingI);

    checkCorresponding(correspondingI, currI, min);
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

void deleteMin(){
    int index = 2;
    int minChild;
    while (1){
        minChild = findMinChild(index);
        if (minChild != -1){
            swapNode(minChild, index);
            index = minChild;
        }else{
            break;
        }
    }

    if (index < currI)  heap[index] = heap[currI--];
    else index = --currI;
    int min = 0;
    int correspondingI = findCorresponding(index, &min);
    printf("corr = %d, min = %d\n", correspondingI, min);
    checkCorresponding(correspondingI, index, min);
}

int findMaxChild(int index){
    if (currI < index * 2){
        return -1;
    }else if (currI < index * 2 + 1){
        return index * 2;
    }else{
        return heap[index*2] > heap[index*2+1] ? index*2 : index*2+1;
    }
}

void deleteMax(){
    int index = 3;
    int maxChild;
    while(1){
        maxChild = findMaxChild(index);
        if (maxChild != -1){
            swapNode(maxChild, index);
            index = maxChild;
        }else{
            break;
        }
    }

    if (index < currI)  heap[index] = heap[currI--];
    else index = --currI;
    int min = 0;
    int correspondingI = findCorresponding(index, &min);
    printf("corr = %d, min = %d\n", correspondingI, min);
    checkCorresponding(correspondingI, index, min);
}
