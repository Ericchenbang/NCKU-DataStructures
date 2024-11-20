/**This is the implement of dfs and bfs for graph.
 * User input adjacency matrix, and then go dfs() or bfs().
 */

#include<stdio.h>
#include<stdlib.h>

#define SIZE 100
int visited[SIZE];

void dfs(int **arr, int n, int start){
    for (int j = 0; j < n; j++){
        //printf("arr[%d][%d] = %d\n", start, j, arr[start][j]);
        //printf("visited[%d] = %d\n", j, visited[j]);

        if (arr[start][j] != 0 && visited[j] == 0){
            printf("%d ", j);
            visited[j] = 1;
            dfs(arr, n, j);
        }
    }
    return;
}

int queue[SIZE];
int front = 0;
int last = 0;
void bfs(int **arr, int n, int start){
    do{
        for (int j = 0; j < n; j++){
            if (arr[start][j] != 0 && visited[j] == 0){
                printf("%d ", j);
                visited[j] = 1;
                queue[last++] = j;
            }
        }
        start = queue[front++];
    }while(front - last != 1);
    
    return;
}


int main(){
    int n;
    scanf("%d", &n);
    //printf("n = %d\n", n);
    int **input = malloc(sizeof(int *) * n);
    for (int i = 0; i < n; i++){
        input[i] = malloc(sizeof(int) * n);
    }
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            scanf("%d", &input[i][j]);
        }
    }
    
    printf("0 ");
    visited[0] = 1;
    dfs(input, n, 0);
    printf("\n");
    bfs(input, n, 0);

    return 0;
}