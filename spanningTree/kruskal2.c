#include<stdio.h>
#include<stdlib.h>

#define SIZE 100
int minHeap[SIZE];
int currIndex = 0;

void swapNode(int a, int b){
    int temp = minHeap[a];
    minHeap[a] = minHeap[b];
    minHeap[b] = temp;
    return;
}


void upSwap(int index){
    if (index > 1 && minHeap[index / 2] > minHeap[index]){
        swapNode(index / 2, index);
        upSwap(index / 2);
    }
    return;
}


void insert(int x){
    minHeap[++currIndex] = x;
    upSwap(currIndex);
    /*for (int i = 0; i <= currIndex; i++) printf("%d ", minHeap[i]);
    printf("\n");*/
}

int findMinChild(int index){
    if (currIndex < index * 2){
        return -1;
    }else if (currIndex < index * 2 + 1){
        return index * 2;
    }else{
        return minHeap[index * 2] < minHeap[index * 2 + 1] ? index * 2 : index * 2 + 1;
    }
}

void downSwap(int index){
    int childIndex = findMinChild(index);
    if (childIndex != -1 && minHeap[childIndex] < minHeap[index]){
        swapNode(childIndex, index);
        downSwap(childIndex);
    }
}

int deleteMin(){
    int temp = minHeap[1];
    minHeap[1] = minHeap[currIndex--];
    downSwap(1);
    return temp;
    /*for (int i = 0; i <= currIndex; i++) printf("%d ", minHeap[i]);
    printf("\n");*/
}


int find(int *arr, int a){
    int temp = a;
    while (arr[a] != -1){
        a = arr[a];
    }
    if (temp != a) arr[temp] = a;
    return a;
}

void unionVertex(int *arr, int a, int b){
    int bossA = find(arr, a);
    int bossB = find(arr, b);
    if (bossA != bossB){
        arr[bossA] = bossB;
    }
}

int main(){
    int n;
    scanf("%d", &n);
    int **input = malloc(sizeof(int *) * n);
    for (int i = 0; i < n; i++) input[i] = malloc(sizeof(int) * n);

    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            scanf("%d", &input[i][j]);
        }
    }    

    for (int i = 0; i < n; i++){
        for (int j = i + 1; j < n; j++){
            if (input[i][j] != 0){
                insert(input[i][j]);
            }
        }
    }

    int *disjointSet = malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++) disjointSet[i] = -1;

    int **edge = malloc(sizeof(int *) * (n - 1));
    for (int i = 0; i < n; i++) edge[i] = malloc(sizeof(int) * 2);
    int edgeNumber = 0;
    int edgeCost = 0;

    while (edgeNumber <= n - 1){
        int min = deleteMin();
        int u = -1, v = -1;
        for (int i = 0; i < n; i++){
            for (int j = i; j < n; j++){
                
                if (input[i][j] == min){
                    u = i;
                    v = j;
                    break;
                }
            }
            if (u != -1) break;
        }
        
        if (find(disjointSet, u) != find(disjointSet, v)){
            edgeCost += min;
            edge[edgeNumber][0] = u;
            edge[edgeNumber++][1] = v;
            unionVertex(disjointSet, u, v);
        }

        if (currIndex < 1) break;
    }

    if (edgeNumber < n - 1){
        printf("There is no min spannint tree.\n");
        return 0;
    }

    printf("%d ", edgeCost);
    for (int i = 0; i < edgeNumber; i++){
        printf("(%d, %d) ", edge[i][0], edge[i][1]);
    }

    return 0;
}

