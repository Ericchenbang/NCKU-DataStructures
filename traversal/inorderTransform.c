/** Inorder to postorder. */

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


    char stack[SIZE];
    int stackI = -1;
    char output[SIZE];
    int outputI = 0;
    for (int i = 0; i < strlen(input); i++){
        char c = input[i];
        if (isOperator(c)){
            if (c == '+' || c == '-'){
                for ( ;stackI >= 0; stackI--){
                    output[outputI++] = stack[stackI];
                }
                stack[++stackI] = c;
            }else{
                if (stackI > -1){
                    if (stack[stackI] == '+' || stack[stackI] == '-'){
                        stack[++stackI] = c;
                    }else{
                        output[outputI++] = stack[stackI];
                        stack[stackI] = c;
                    }
                }else{
                    output[outputI++] = stack[stackI];
                    stack[stackI] = c;
                }
            }
        }else{
            output[outputI++] = c;
        }
    }
    for (; stackI >= 0; stackI--){
        output[outputI++] = stack[stackI];
    }
    output[outputI] = '\n';
    printf("%s\n", output);

    return 0;
}

