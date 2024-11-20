/** This is a preorder to inorder transformer.
 *  The math equation contain *-+/ and number and ().
 */

#include<stdio.h>
#include<string.h>
#define SIZE 100

int isOperator(char c){
    return c == '+' || c == '-' || c == '*' || c == '/';
}

int main(){
    char input[SIZE];
    fgets(input, SIZE, stdin);
    input[strcspn(input, "\n")] = 0;

    int stack[SIZE];
    int stackI = 0;
    int number = 0;
    int multi = 1;
    for (int i = strlen(input) - 1; i >= 0; i--){
        char t = input[i];
        if (isOperator(t)){
            //printf("stack[%d] = %d, stack[%d] = %d\n", stackI-2, stack[stackI-2], stackI-1, stack[stackI-1]);
            if (t == '+'){
                stack[stackI - 2] += stack[stackI - 1];
                
            }else if (t == '-'){
                stack[stackI - 2] = stack[stackI - 1] - stack[stackI - 2];
                
            }else if (t == '*'){
                stack[stackI - 2] = stack[stackI - 1] * stack[stackI - 2];
            }else{
                stack[stackI - 2] = stack[stackI - 1] / stack[stackI - 2];
            }
            stackI -= 1;

        }else if (t == ' '){
            if (number != 0){
                stack[stackI++] = number;
                number = 0;
                multi = 1;
            }
        }else{
            number += multi * ((int)t - 48);
            multi *= 10;
        }
    }

    printf("%d\n", stack[0]);
    return 0;
}
