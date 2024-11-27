/**This code is to find the articulation point in a given graph.
 * The input of graph are given by array.
 * First, I use dfs go through the whole graph, count how many edge are they connected in the beginning.
 * Then, each time I delete one node to see how many edge are connected.
 * If it is less than the value of beginning minus 1, then this current node is articulation point.
 */


#include<stdio.h>
#include<stdlib.h>
#define SIZE 100

int visited[SIZE];
int stack[SIZE];
int stackI = 0;
int edgeNumber = 0;

void dfs(int **arr, int n, int testPoint){
    int startI = stack[--stackI];

    for (int i = 0; i < n; i++){
        if (i == testPoint){
            continue;
        }
        if(visited[i] == 0 && arr[startI][i] != 0){
            visited[i] = 1;
            edgeNumber++;
            stack[stackI++] = i;
            dfs(arr, n, testPoint);
        }
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
    
    visited[0] = 1;
    stack[stackI++] = 0;
    dfs(input, n, n);
    int initialEdgeNumber = edgeNumber;
    

    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            visited[j] = 0;
        }
        stackI = 0;
        edgeNumber = 0;
        if (i == 0){
            stack[stackI++] = 1;
        }else{
            stack[stackI++] = 0;
        }
        dfs(input, n, i);
        if (edgeNumber < initialEdgeNumber - 1){
            printf("Vertex %d is articulation point.\n", i + 1);
        }
    }



    return 0;
}

