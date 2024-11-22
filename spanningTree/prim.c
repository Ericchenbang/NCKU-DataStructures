#include<stdio.h>


int find(int *arr, int index){
    int store = index;
    while (arr[index] != -1){
        index = arr[index];
    }
    if (store != index) arr[store] = index;
    return index;
}

void unionset(int *arr, int a, int b){
    int checkA = find(arr, a);
    int checkB = find(arr, b);
    if (checkA != checkB) arr[checkB] = checkA;
    return;
}

#define SIZE 100
int main(){
    int n;
    scanf("%d", &n);
    int input[n][n];
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            scanf("%d", &input[i][j]);
        }
    }

    int disjointSet[n];
    for (int i = 0; i < n; i++) disjointSet[i] = -1;

    int edgeCost = 0;
    int edge[n-1][2];
    int edgeIndex = 0;
    edge[0][0] = 0;
    //edge[0][1] = -1;

    while (edgeIndex < n - 1){

        int min = 10000;
        int u = -1, v = -1;

        if (edgeIndex == 0){
            int targetIndex = 0;
            for (int i = 0; i < n; i++){
                int e = input[targetIndex][i];
                if (e != 0 && (find(disjointSet, targetIndex) != find(disjointSet, i))){
                    if (e < min){
                        min = e;
                        u = targetIndex;
                        v = i;
                    }
                }
            }
        }else{
            for (int k = 0; k < edgeIndex; k++){
                for (int s = 0; s < 2; s++){
                    int targetIndex = edge[k][s];

                    for (int i = 0; i < n; i++){
                        int e = input[targetIndex][i];
                        if (e != 0 && (find(disjointSet, targetIndex) != find(disjointSet, i))){
                            if (e < min){
                                min = e;
                                u = targetIndex;
                                v = i;
                            }
                        }
                    }
                }
                
            }
        }
        
        if (u == -1 || v == -1){
            printf("false\n");
            break;
        }
        unionset(disjointSet, u, v);
        edge[edgeIndex][0] = u;
        edge[edgeIndex++][1] = v;
        edgeCost += min;
    }

    printf("%d", edgeCost);
    for (int i = 0; i < edgeIndex; i++){
        printf(" (%d, %d)", edge[i][0] + 1, edge[i][1] + 1);
    }
    printf("\n");
    return 0;

}

