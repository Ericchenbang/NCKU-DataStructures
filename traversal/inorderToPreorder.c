/** This is for inorder transform to preorder.
 * Pseudocode:
 *      while go through the input
 *          if c is '+' or '-'
 *              push it to the output front
 *          else if c is '*' or '/'
 *              rewrite the ouput from x, for x is input[i], to c x y, for y is input[i+1]
 *          else if c is alpha
 *              push it to output rear
 */



#include<stdio.h>
#include<string.h>
#define SIZE 100

int isOperator(char c){
    return c == '+' || c == '-' || c == '*' || c == '/';
}

int main(){
    char input[SIZE];
    scanf("%s", input);

    int output[SIZE];
    int front = 49; 
    int rear = 50;
    

    for (int i = 0; i < strlen(input); i++){
        char c = input[i];
        if (isOperator(c)){
            if (c == '+' || c == '-'){
                output[front--] = c;
            }else{
                char temp = output[--rear];
                output[rear++] = c;
                output[rear++] = temp;
                output[rear++] = input[++i];

            }
        }else{
            output[rear++] = c;
        }
    }

    for (int i = front + 1; i < rear; i++){
        printf("%c ", output[i]);
    }
    return 0;
}

