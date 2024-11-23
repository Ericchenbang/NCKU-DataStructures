#include<stdio.h>
#include<stdlib.h>

int find(int *set, int a){
    int temp = a;
    while (set[a] != -1){
        a = set[a];
    }
    if (temp != a) set[temp] = a;
    return a;
}

void unionVertex(int *set, int a, int b){
    int aBoss = find(set, a);
    int bBoss = find(set, b);
    if (aBoss != bBoss){
        set[aBoss] = bBoss;
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

    int *disjointSet = malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++) disjointSet[i] = -1;

    int **edge = malloc(sizeof(int *) * (n - 1));
    for (int i = 0; i < n - 1; i++) edge[i] = malloc(sizeof(int) * 2);

    int edgeNumber = 0;
    int edgeCost = 0;

    while (edgeNumber < n - 1){
        int minEdge = 1e9;
        int u = -1;
        int v = -1;

        for (int i = 0; i < n; i++){
            for (int j = i + 1; j < n; j++){
                if ((input[i][j] != 0 && input[i][j] < minEdge)){
                    //printf("i = %d, j = %d\n", i, j);
                    if (find(disjointSet, i) != find(disjointSet, j)){
                        minEdge = input[i][j];
                        u = i;
                        v = j;
                    }else{
                        input[i][j] = 0;
                    }
                }
            }
        }

        if (u == -1 || v == -1){
            break;
        }else{
            //printf("u = %d, v = %d\n", u, v);
            unionVertex(disjointSet, u, v);
            input[u][v] = 0;
            edge[edgeNumber][0] = u;
            edge[edgeNumber++][1] = v;
            edgeCost += minEdge;

        }

    }

    if (edgeNumber < n - 1){
        printf("No minimum cost spanning tree.\n");
        return 0;
    }else{
        printf("%d ", edgeCost);
        for (int i = 0; i < n - 1; i++){
            printf("(%d, %d) ", edge[i][0] + 1, edge[i][1] + 1);
        }
    }


    for (int i = 0; i < n; i++) free(input[i]);
    free(input);
    for (int i = 0; i < n; i++) free(disjointSet);
    for (int i = 0; i < n; i++) free(edge[i]);
    free(edge);

    return 0;
}