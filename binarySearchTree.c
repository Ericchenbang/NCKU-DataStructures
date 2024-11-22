#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct Node{
    int data;
    struct Node *left;
    struct Node *right;
};

struct Node *create(int x){
    struct Node *newNode = malloc(sizeof(struct Node));
    newNode -> data = x;
    newNode -> left = NULL;
    newNode -> right = NULL;
    return newNode;
}

struct Node *search(int x, struct Node *root, struct Node **lastNode){
    struct Node *localLastNode = NULL;
    struct Node *findNode = root;
    while (findNode != NULL){
        if (findNode -> data > x){
            localLastNode = findNode;
            findNode = findNode -> left;
        }else if (findNode -> data < x){
            localLastNode = findNode;
            findNode = findNode -> right;
        }else{
            *lastNode = localLastNode;
            return findNode;
        }
    }
    *lastNode = localLastNode;
    return findNode;
}

void insert(int x, struct Node **root){
    //struct Node *copyRoot = *root;
    struct Node *newNode = create(x);
    if (*root == NULL){
        *root = newNode;
        return;
    }
    struct Node *lastNode;
    search(x, *root, &lastNode);
    if (lastNode -> data > x){
        lastNode -> left = newNode;
    }else{
        lastNode -> right = newNode;
    }
    //*root = copyRoot;
}

void delete(int x, struct Node **root){
    struct Node *deleteNode;
    struct Node *lastNode;
    deleteNode = search(x, *root, &lastNode);
    if (deleteNode -> left == NULL && deleteNode -> right == NULL){
        if (lastNode -> left == deleteNode){
            lastNode -> left = NULL;
        }else{
            lastNode -> right = NULL;
        }
    }else if (deleteNode -> left == NULL){
        if (lastNode -> left == deleteNode){
            lastNode -> left = deleteNode -> right;
        }else{
            lastNode -> right = deleteNode -> right;
        }
    }else if (deleteNode -> right == NULL){
        if (lastNode -> left == deleteNode){
            lastNode -> left = deleteNode -> left;
        }else{
            lastNode -> right = deleteNode -> left;
        }
    }else{
        struct Node *deleteLeft = deleteNode -> left;
        struct Node *deleteRight = deleteNode -> right;
        struct Node *p = deleteRight;

        while (deleteRight -> left != NULL){
            p = deleteRight;
            deleteRight = deleteRight -> left;
        }

        deleteNode -> data = deleteRight -> data;

        if (deleteRight != p){
            p -> left = deleteRight -> right;
        }else{
            deleteNode -> right = deleteRight -> right;
        }
    }


}

void printNode(struct Node *p){
    struct Node *leftChild = NULL;
    struct Node *rightChild = NULL;
    if (p != NULL){
        //printf("%d ", p -> data);
        leftChild = p -> left;
        rightChild = p -> right;
    }

    if (leftChild != NULL){
        printf("%d ", leftChild -> data);
    }
    if (rightChild != NULL){
        printf("%d ", rightChild -> data);
    }

    if (leftChild != NULL){
        printNode(leftChild);
    }
    if (rightChild != NULL){
        printNode(rightChild);
    }
}


int main(){
    char operation[6];
    scanf("%s", operation);
    struct Node *root = NULL;
    int x;

    while(1){
        //printf("%s\n", operation);
        if (operation[0] == 'i'){
            scanf("%d", &x);
            //printf("%d\n", x);
            insert(x, &root);
        }else if (operation[0] == 'd'){
            scanf("%d", &x);
            delete(x, &root);

        }else{
            break;
        }
        getchar();
        scanf("%s", operation);
    }

    printf("%d ", root -> data);
    printNode(root);

    return 0;
}

