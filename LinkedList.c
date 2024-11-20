/**This is a implement of double circular linked list.
 * There are two important functions: insertFront and insertLast.
 * In main() are some easy test for the two functions.
 */

#include<stdio.h>
#include<stdlib.h>

struct node{
    int data;
    struct node *next;
    struct node *last;
};

struct node *create(int x){
    struct node *newNode = malloc(sizeof(struct node));
    newNode -> data = x;
    newNode -> next = newNode;
    newNode -> last = newNode;
    return newNode;
}

void insertFront(struct node **root, int x){
    struct node *oldRoot = *root;
    struct node *oldRootLast= oldRoot -> last;
    struct node *newNode = create(x);
    newNode -> next = oldRoot;
    newNode -> last = oldRootLast;
    oldRootLast -> next = newNode;
    oldRoot -> last = newNode;
    *root = newNode;
}

void insertLast(struct node **root, int x){
    struct node *oldRoot = *root;
    struct node *oldRootLast = oldRoot -> last;
    struct node *newNode = create(x);
    newNode -> next = oldRoot;
    newNode -> last = oldRootLast;
    oldRoot -> last = newNode;
    oldRootLast -> next = newNode;
}

void printLinkedList(struct node *root){
    int check = root -> data;
    struct node *p = root;
    do{
        printf("%d ", p -> data);
        p = p -> next;
    }while(p -> data != check);
    printf("\n");
}

#define SIZE 100

int main(){
    struct node *root = create(5);
    insertFront(&root, 2);
    insertLast(&root, 9);
    insertLast(&root, 19);
    insertLast(&root, 29);
    insertFront(&root, 1);
    printLinkedList(root);

    return 0;
}

