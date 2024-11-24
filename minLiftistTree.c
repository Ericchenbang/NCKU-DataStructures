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

int shortest(struct Node *p){
    if (p == NULL){
        return 0;
    }
    return 1 + shortest(p -> right);
}

void printTree(struct Node *root);

/**struct Node *meld(struct Node *treeA, struct Node *treeB){
    struct Node *record = treeA;
    struct Node *a = record;
    struct Node *b = treeB;
    struct Node *lastA = NULL;

    while(1){
        if (a == NULL){
            printf("b -> data = %d\n", b -> data);
            lastA -> right = b;
            break;
        }
        if (b == NULL){
            break;
        }

        printf("a -> data = %d, b -> data = %d\n", a -> data, b -> data);
        // Set treeA is root(a -> data is smaller)
        if (a -> data > b -> data){
            struct Node *temp = a;
            
            if (lastA != NULL){
                printf("lastA -> data = %d\n", lastA -> data);
                lastA -> right = b;
            }
            a = b;
            b = temp;
        }

        printf("a -> data = %d, b -> data = %d\n", a -> data, b -> data);
        lastA = a;
        a = a -> right;
        printTree(record);
        printf("\n");
    }

    int sLength = shortest(record);
    printf("sLength = %d\n", sLength);
    for (int i = 0; i < sLength; i++){
        struct Node *p = record;
        for (int j = sLength - i - 1; j > 0; j--){
            p = p -> right;
            printf("record -> data = %d\n", p -> data);
        }

        if (shortest(p -> left) < shortest(p -> right)){
            struct Node *temp = p -> left;
            p -> left = p -> right;
            p -> right = temp;
            printf("p -> left -> data = %d, p -> right -> data = %d\n", p->left->data, p->right->data);
        }
    }

    return record;
}*/

struct Node *meld(struct Node *treeA, struct Node *treeB){
    if (treeA == NULL) return treeB;
    if (treeB == NULL) return treeA;

    // Ensure the smaller root is treeA
    if (treeA->data > treeB->data){
        struct Node *temp = treeA;
        treeA = treeB;
        treeB = temp;
    }

    // Recursively meld treeA's right child with treeB
    treeA->right = meld(treeA->right, treeB);

    // Swap to maintain leftist property
    if (shortest(treeA->left) < shortest(treeA->right)){
        struct Node *temp = treeA->left;
        treeA->left = treeA->right;
        treeA->right = temp;
    }

    return treeA;
}



void insert(struct Node **root, int x){
    struct Node *newTree = create(x);
    if (*root == NULL){
        *root = newTree;
    }else{
        *root = meld(*root, newTree);
    }
}

void delete(struct Node **root){
    struct Node *p = *root;
    if (p == NULL){
        return;
    }else if (p -> left == NULL && p -> right == NULL){
        *root = NULL;
        return;
    }else if (p -> left == NULL){
        *root = p -> right;
    }else if (p -> right == NULL){
        *root = p -> left;
    }else{
        *root = meld(p -> left, p -> right);
    }
}


#define SIZE 100

void printTree(struct Node *root){
    struct Node *queue[SIZE];
    int front = 0;  
    int rear = -1;

    if (root == NULL) return;
    queue[++rear] = root;
    while (front <= rear){
        struct Node *target = queue[front++];
        printf("%d ", target -> data);
        if (target -> left != NULL) queue[++rear] = target -> left;
        if (target -> right != NULL) queue[++rear] = target -> right;
    }
    
}


int main(){
    char operation[6];
    scanf("%s", operation);
    
    struct Node *root = NULL;

    int x;
    while (operation[0] != 'e'){
        if (operation[0] == 'i'){
            scanf("%d", &x);
            insert(&root, x);

        }else if (operation[0] == 'd'){
            delete(&root);
        }

        scanf("%s", operation);
    }
    printTree(root);

    /**struct Node *treeA = create(5);
    treeA -> left = create(9);
    treeA -> left -> left = create(12);
    treeA -> left -> left -> left = create(20);
    treeA -> left -> left -> right = create(18);
    treeA -> right = create(8);
    treeA -> right -> left = create(10);
    treeA -> right -> left -> left= create(15);

    struct Node *treeB = create(6);
    treeB -> left = create(9);
    treeB -> left -> left = create(12);
    treeB -> left -> left -> left = create(20);
    treeB -> left -> left -> left -> left= create(25);
    treeB -> left -> left -> right = create(16);
    treeB -> left -> right = create(15);
    treeB -> right = create(8);
    treeB -> right -> left = create(10);
    treeB -> right -> right = create(25);
    treeB -> right -> left -> left = create(15);

    struct Node* newTree = meld(treeA, treeB);
    
    printTree(newTree);*/

    return 0;
}