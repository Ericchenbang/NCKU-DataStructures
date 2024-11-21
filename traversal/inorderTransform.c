#include<stdio.h>
#include<stdlib.h>

#define SIZE 100

struct Node{
    char data;
    struct Node *left;
    struct Node *right;
};
struct Node *create(char x){
    struct Node *newNode = malloc(sizeof(struct Node));
    newNode -> data = x;
    newNode -> left = NULL;
    newNode -> right = NULL;
}
void inorder(struct Node *root){
    if(root != NULL){
        inorder(root -> left);
        printf("%c ", root -> data);
        inorder(root -> right);
    }
    return;
}
void preorder(struct Node *root){
    if(root != NULL){
        printf("%c ", root -> data);
        preorder(root -> left);
        preorder(root -> right);
    }
    return;
}
void postorder(struct Node *root){
    if(root != NULL){
        postorder(root -> left);
        postorder(root -> right);
        printf("%c ", root -> data);
    }
    return;
}
void printTree(){

}


int main(){
    /**char input[SIZE];
    fgets(input, SIZE, stdin);
    input[strcspn(input, "\n")] = 0;

    inorder(input);
    preorder(input);
    postorder(input);*/

    struct Node *tree = create('A');
    tree -> right = create('C');
    tree -> left = create('B');
    tree -> left -> left = create('D');
    tree -> left -> left -> left = create('H');
    tree -> left -> right = create('E');
    tree -> left -> right -> right = create('I');
    tree -> right -> left = create('F');
    tree -> right -> left -> left= create('J');
    tree -> right -> right = create('G');

    inorder(tree);
    printf("\n");
    preorder(tree);
    printf("\n");
    postorder(tree);
    return 0;
}

