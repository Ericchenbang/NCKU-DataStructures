/**SIZE is the number of m of bloom filter.
 * There are two operation for user to input:
 * 1. insert(x) 2. member(x)
 * There are three hash function:
 * 1. 3x % SIZE 2.2x % SIZE 3. x^2 % SIZE
*/

#include<stdio.h>
#include<stdbool.h>

#define SIZE 13

int arr[SIZE];

int h1(int x){
    int ans = 3*x % SIZE;
    return ans > 0 ? ans : -1 * ans;
}
int h2(int x){
    int ans = 2*x % SIZE;
    return ans > 0 ? ans : -1 * ans;
}
int h3(int x){
    int ans =  x*x % SIZE;
    return ans > 0 ? ans : -1 * ans;
}

void insert(int x){
    arr[h1(x)] = 1;
    arr[h2(x)] = 1;
    arr[h3(x)] = 1;
    return;
}

bool member(int x){
    if (arr[h1(x)] == 1 && arr[h2(x)] == 1 && arr[h3(x)] == 1) return true;
    return false;
}

void printArr(){
    for (int i = 0; i < SIZE; i++) printf("%d ", arr[i]);
    printf("\n");
    return;
}

int main(){
    char operation[6];
    scanf("%s", operation);
    int x;

    while(true){
        if (operation[0] == 'i'){
            scanf("%d", &x);
            insert(x);
        }else if (operation[0] == 'm'){
            scanf("%d", &x);
            if (member(x)){
                printf("Maybe\n");
            }else{
                printf("No\n");
            }
        }else{
            printArr();
            break;
        }
        getchar();
        scanf("%s", operation);
    }
    return 0;
}