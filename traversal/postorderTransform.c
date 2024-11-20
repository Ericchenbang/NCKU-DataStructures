/** This code count the postorder math equation.
 * For example: The ans of "2 3 4 * + 400 200 / -" is 12.
 * There are space between each of the number and operator.
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define SIZE 100

int main(){
    char input[SIZE];
    fgets(input, SIZE, stdin);
    input[strcspn(input, "\n")] = 0;
    int inputL = strlen(input);
    //printf("%s\n", input);

    int stack[inputL];
    int stackI = -1;

    int number = 0;
    int lastIsNumber = 0;

    for (int i = 0; i < inputL; i++){
        char t = input[i];
        //printf("t = %c\n", t);
        int temp;
        if (t == '+' || t == '-' || t == '*' || t == '/'){ 
            if (t == '+'){
                temp = stack[stackI - 1] + stack[stackI];
            }else if (t == '-'){ 
                temp = stack[stackI - 1] - stack[stackI];
            }else if (t == '*'){
                temp = stack[stackI - 1] * stack[stackI];
            }else{
                temp = stack[stackI - 1] / stack[stackI];
            }

            //printf("temp = %d\n", temp);
            stackI -= 1;
            stack[stackI] = temp;
            lastIsNumber = 0;

        }else if (t == ' '){
            if (lastIsNumber){
                stack[++stackI] = number;
                //printf("stack[%d] = %d\n", stackI, stack[stackI]);
                number = 0;
                lastIsNumber = 0;
            }
            
        }else{
            number *= 10;
            number += (int)t - 48;
            //printf("number = %d\n", number);
            lastIsNumber = 1;
        }


    }
    
    printf("%d", stack[0]);
    return 0;
}