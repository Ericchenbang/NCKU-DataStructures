#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct Node{
    int data;
    struct Node *next;
    struct Node *child;
};
struct Node *min = NULL;
#define TBSIZE 51
struct Node *table[TBSIZE][TBSIZE];

#define OPSIZE 6
void insert(int);
void deleteMin();
void printHeap();

int main(){
    char operation[OPSIZE];
    scanf("%s", operation);
    getchar();

    while (strcmp(operation, "exit") != 0){
        printf("op = %s", operation);
        if (strcmp(operation, "insert") == 0){
            int x;
            scanf("%d", &x);
            printf(", x = %d\n", x);
            insert(x);

        }else if (strcmp(operation, "delete") == 0){
            printf("\n");
            deleteMin();
        }
        scanf("%s", operation);
        getchar();
    }

    printHeap();
    return 0;
}

void printMin(){
    printf("min: ");
    if (min == NULL){
        printf("null\n");
        return;
    }

    int temp = min -> data;
    struct Node *p = min;
    do{
        printf("%d ", p -> data);
        p = p -> next;
    }while (p -> data != temp);
    printf("\n");
    return;
}

void printTable(){
    for (int i = 0; i < TBSIZE; i++){
        int allNull = 1;
        for (int j = 0; j < TBSIZE; j++){
            if (table[i][j] == NULL) break;
            else if (j == 0) printf("degree %d: ", i);

            printf("%d ", table[i][j] -> data);
            allNull = 0;
        }
        if (!allNull) printf("\n");
    }
    return;
}


struct Node *create(int x){
    struct Node *newNode = malloc(sizeof(struct Node));
    newNode -> data = x;
    newNode -> next = newNode;
    newNode -> child = NULL;
    return newNode;
}

void addToList(struct Node **root, struct Node *node){
    if (*root == NULL){
        *root = node;
        return;
    }
    
    struct Node *lastNode = *root;
    while(lastNode -> next != *root){
        lastNode = lastNode -> next;
    }

    struct Node *cmp = *root;
    struct Node *cmpLast = lastNode;
    int temp = cmp -> data;
    while (node -> data > cmp -> data){
        cmpLast = cmp;
        cmp = cmp -> next;
        if (cmp -> data == temp){
            break;
        }
    }
    node -> next = cmp;
    cmpLast -> next = node;

    /* This node is the min.*/
    if (node -> data < (*root) -> data){
        *root = node;
    }
    
    return;
}

int findDegree(struct Node *node){
    int degree = 0;
    int temp = 0;
    struct Node *p = NULL;

    if (node -> child != NULL){
        temp = node -> child -> data;
        p = node -> child;
    }else{
        return 0;
    }
    
    do{
        degree += 1;
        p = p -> next;
    }while(p -> data != temp);
    return degree;
}


void addToTable(struct Node *node){
    int d = findDegree(node);
    int j;
    for (j = 0; j < TBSIZE; j++){
        if (table[d][j] == NULL){
            table[d][j] = node;
            break;
        }
    }
    printf("hh");
    printTable();

    /* sorting */
    for (j; j >= 1; j--){
        if (table[d][j] -> data < table[d][j - 1] -> data){
            struct Node *temp = table[d][j];
            table[d][j] = table[d][j - 1];
            table[d][j - 1] = temp;
        }else{
            break;
        }
    }
}



void insert(int x){
    struct Node *newNode = create(x);
    addToList(&min, newNode);
    addToTable(newNode);
    printMin();
    printTable();
}

void removeFromMin(struct Node *node){
    if (min -> next == min){
        min = NULL;
        return;
    }else if (min -> data == node -> data){ /* if the deleted node is min.*/
        int temp = min -> data;
        //printf("%d\n", temp);
        struct Node *p = min;
        while (p -> next != min){
            p = p -> next;
        }
        
        min = min -> next;
        p -> next = min;
        //printf("p = %d, min = %d\n", p -> data, min -> data);
        return;
    }

    struct Node *p = min;
    struct Node *lastNode = NULL;
    while(1){
        if (p -> data == node -> data){
            break;
        }
        lastNode = p;
        p = p -> next;
    }

    lastNode -> next = p -> next;
    return;
}

void removeFromTable(struct Node *node){
    int d = findDegree(node);
    printf("degree = %d\n", d);
    for (int j = 0; j < TBSIZE; j++){
        if (table[d][j] -> data == node -> data){
            for (int k = j; k < TBSIZE; k++){
                if (table[d][k] == NULL) break;
                table[d][k] = table[d][k + 1];
            }
            break;
        }
    }
    return;
}


void pairwiseCombine(){
    for (int i = 0; i < TBSIZE; i++){
        for (int j = 0; j < TBSIZE; j++){
            if (table[i][j] == NULL || table[i][j + 1] == NULL) break;

            struct Node *parent = table[i][j];
            struct Node *parentChild = table[i][j + 1];
            removeFromMin(table[i][j + 1]);

            parentChild -> next = parentChild;
            if (parent -> child == NULL){
                parent -> child = parentChild;
            }else{
                addToList(&(parent -> child), parentChild);
            }

            for (int k = j; k < TBSIZE; k += 2){
                if (table[i][k] == NULL) break;
                table[i][k] = table[i][k + 2];
                table[i][k + 1] = table[i][k + 3];
            }
            j -= 1;

            addToTable(parent);
            printTable();
        }
    }
}

void deleteMin(){
    struct Node *copyMin = min;
    removeFromMin(copyMin);
    removeFromTable(copyMin);
    printMin();
    printTable();

    if (copyMin -> child != NULL){
        struct Node *c = copyMin -> child;
        int cTemp = c -> data;
        do{
            struct Node *cCopy = c;
            c = c -> next;
            cCopy -> next = cCopy;
            addToList(&min, cCopy);
            addToTable(cCopy);
            printMin();
            printTable();
        }while (c -> data != cTemp);
    }

    pairwiseCombine();
    printf("after combine: \n");
    printMin();
    printTable();
}

#define QSIZE 100
struct Node *queue[QSIZE];
int front = 0;
int rear = -1;

void printHeap(){
    for (int i = 0; i < TBSIZE; i++){
        int allNull = 1;
        for (int j = 0; j < TBSIZE; j++){
            if (table[i][j] == NULL) break;


            queue[++rear] = table[i][j];

            while (front <= rear){
                struct Node *curr = queue[front];
                if (curr -> child != NULL){
                    struct Node *p = curr -> child;
                    int temp = p -> data;
                    do {
                        queue[++rear] = p;
                        p = p -> next;
                    }while (p -> data != temp);
                }
                printf("%d ", queue[front++] -> data);
            }    
            printf("\n");                                                           
        }
    }
}

