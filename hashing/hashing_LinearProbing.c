/**This is a hashing function of division with linear probing.
 * There are three operations for user to input.
 * 1. insert(x) 2. delete(x) 3. exit
 * The end of the file will print out the key in this hashing table,
 * which x represent none element.
 */

#include<stdio.h>
#include<stdlib.h>
#define SIZE 17
#define IV -1

int arr[SIZE];


void insert(int x){
    int location = x % SIZE;
    if (location < 0) location += SIZE;
    //printf("location = %d\n", location);
    for (int i = 0; i < SIZE; i++){
        int presentL = (location + i) % SIZE;
        if (arr[presentL] == IV){
            arr[presentL] = x;
            return;
        }
    }
    printf("The hashing table is full!\n");
    return;
}

void delete(int x){
    int location = x % SIZE;
    if (location < 0) location += SIZE;

    int presentL = location;
    for (int i = 0; i < SIZE; i++){
        presentL = (presentL + 1) % SIZE;
        if (arr[presentL] == x){
            arr[presentL] = IV; 
            break;
        }
    }

    int nextL = (presentL + 1) % SIZE;
    // The last position which has IV value.
    int lastIV = presentL;

    for (int i = 0; i < SIZE - 1; i++){
        nextL = (nextL + 1) % SIZE;

        int change = 0;
        if (arr[nextL] != IV){
            int targetL = arr[nextL] % SIZE;

            if (targetL != nextL){
                // The blank is in front of nextL.
                if (lastIV < nextL){
                    // The target Location are not between last IV and nextL.
                    if (!(lastIV < targetL && targetL < nextL)){
                        change = 1;
                    }
                // The blank is behind nextL.
                }else{
                    // The target is between nextL and lastIV.
                    if (nextL < targetL && targetL <= lastIV){
                        change = 1;
                    }
                }

                if (change){
                    arr[lastIV] = arr[nextL];
                    arr[nextL] = IV;
                    lastIV = nextL;
                }   
            }
        }else{
            break;
        }
    }
    
}

void printArr(){
    for (int i = 0; i < SIZE; i++){
        if (arr[i] == IV){
            printf("x ");
            continue;
        }
        printf("%d ", arr[i]);
    }
    printf("\n");
}


int main(){
    for (int i = 0; i < SIZE; i++) arr[i] = IV;
    int x;
    char input[6];
    scanf("%s", input);
    
    while(1){
        //printf("input=%s\n", input);
        if(input[0] == 'i'){
            scanf("%d", &x);
            //printf("x = %d\n", x);
            insert(x);
        }else if(input[0] == 'd'){
            scanf("%d", &x);
            //printf("x = %d\n", x);
            delete(x);
        }else{
            break;
        }
        getchar();
        scanf("%s", input);
    }

    printArr();
    return 0;
}