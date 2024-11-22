#include<stdio.h>

/**int find(int *arr, int index){
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
}*/


int main(){
    int n;
    scanf("%d", &n);
    int input[n][n];
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            scanf("%d", &input[i][j]);
        }
    }

    //int disjointSet[n];
    //for (int i = 0; i < n; i++) disjointSet[i] = -1;
    int visited[n];
    for (int i = 0; i < n; i++) visited[i] = 0;
    visited[0] = 1;

    int edgeCost = 0;
    int edge[n-1][2];
    int edgeIndex = 0;
    edge[0][0] = 0;
    //edge[0][1] = -1;

    while (edgeIndex < n - 1){
        int min = 10000;
        int u = -1, v = -1;

        int targetIndex;
        for (int k = 0; k <= edgeIndex; k++){
            if (edgeIndex != 0 && k == edgeIndex) break;

            for (int s = 0; s < 2; s++){
                if (s == 1 && edgeIndex == 0){
                    break;
                }
                targetIndex = edge[k][s];
                for (int i = 0; i < n; i++){
                    int e = input[targetIndex][i];
                    //if (e != 0 && (find(disjointSet, targetIndex) != find(disjointSet, i)))
                    if (e != 0 && visited[i] != 1 && e < min){
                        min = e;
                        u = targetIndex;
                        v = i;
                    }
                }
            }
        }
        
        if (u == -1 || v == -1){
            printf("false\n");
            break;
        }
        //unionset(disjointSet, u, v);
        visited[v] = 1;
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

