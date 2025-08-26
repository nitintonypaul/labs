#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_SIZE 100

// Test (3+5)*(7-2)/(8-3)^(2+1) + (9-4*2) + (6/(2+1)) - (7^(2-1)) + (8*3-(9/3)) + (5+(6*2-4)) - (9-(8/(4-2))) + (7*(3+2)) - (6-5+4-3+2-1)

char charStack[MAX_SIZE];
int charTop = -1;


int intStack[MAX_SIZE];
int intTop = -1;


int isCharStackEmpty() {
    return charTop == -1;
}

int isCharStackFull() {
    return charTop == MAX_SIZE - 1;
}

void pushChar(char c) {
    if (isCharStackFull()) {
        printf("Character stack overflow!\n");
        return;
    }
    charStack[++charTop] = c;
}

char popChar() {
    if (isCharStackEmpty()) {
        printf("Character stack underflow!\n");
        return '\0';
    }
    return charStack[charTop--];
}

char peekChar() {
    if (isCharStackEmpty()) {
        return '\0';
    }
    return charStack[charTop];
}


int isIntStackEmpty() {
    return intTop == -1;
}

int isIntStackFull() {
    return intTop == MAX_SIZE - 1;
}

void pushInt(int val) {
    if (isIntStackFull()) {
        printf("Integer stack overflow!\n");
        return;
    }
    intStack[++intTop] = val;
}

int popInt() {
    if (isIntStackEmpty()) {
        printf("Integer stack underflow!\n");
        return 0;
    }
    return intStack[intTop--];
}


int isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
}

int getPrecedence(char op) {
    switch(op) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        case '^':
            return 3;
        default:
            return 0;
    }
}

int isRightAssociative(char op) {
    return (op == '^');
}


void infixToPostfix(char* infix, char* postfix) {
    
    charTop = -1;
    
    int i = 0, j = 0;
    char c;
    
    while (infix[i] != '\0') {
        c = infix[i];
        
        
        if (isdigit(c)) {
            postfix[j++] = c;
            
        }
        
        else if (c == '(') {
            pushChar(c);
            
        }
        
        else if (c == ')') {
            
            while (!isCharStackEmpty() && peekChar() != '(') {
                postfix[j++] = popChar();
            
            }
            popChar(); 
            
        }
        
        else if (isOperator(c)) {
            
            while (!isCharStackEmpty() && 
                   peekChar() != '(' &&
                   (getPrecedence(peekChar()) > getPrecedence(c) ||
                    (getPrecedence(peekChar()) == getPrecedence(c) && !isRightAssociative(c)))) {
                postfix[j++] = popChar();
            
            }
            pushChar(c);
            
        }
    
        
        for (int k = 0; k < j; k++) printf("%c", postfix[k]);
        printf("\n\n");
        
        i++;
    }
    
    
    
    while (!isCharStackEmpty()) {
        postfix[j++] = popChar();
    
    }
    
    postfix[j] = '\0'; 
    printf("postfix: %s\n\n", postfix);
}


int evaluatePostfix(char* postfix) {
    
    intTop = -1;
    
    int i = 0;
    char c;
    int operand1, operand2, result;
    
    while (postfix[i] != '\0') {
        c = postfix[i];
        
        
        
        
        if (isdigit(c)) {
            int val = c - '0';
            pushInt(val);
        
        }
        
        else if (isOperator(c)) {
            if (intTop < 1) {
        
                return 0;
            }
            
            operand2 = popInt();
            operand1 = popInt();
        
            
            switch(c) {
                case '+':
                    result = operand1 + operand2;
                    break;
                case '-':
                    result = operand1 - operand2;
                    break;
                case '*':
                    result = operand1 * operand2;
                    break;
                case '/':
                    if (operand2 != 0) {
                        result = operand1 / operand2;
                    } else {
                        printf("Division by zero\n");
                        return 0;
                    }
                    break;
                case '^':
                    result = 1;
                    for (int k = 0; k < operand2; k++) {
                        result *= operand1;
                    }
                    break;
                default:
                    printf("Unknown operator '%c'\n", c);
                    return 0;
            }
            
            pushInt(result);
        }
        
        i++;
    }
    
    if (intTop != 0) {
        printf("Invalid postfix expression\n");
        return 0;
    }
    
    
    return popInt();
}

int main() {
    char infix[MAX_SIZE];
    char postfix[MAX_SIZE];
    
    printf("Enter infix: ");
    fgets(infix, MAX_SIZE, stdin);
    
    
    int len = strlen(infix);
    if (len > 0 && infix[len-1] == '\n') {
        infix[len-1] = '\0';
    }
    
    printf("\nOriginal infix expression: %s\n", infix);
    
    
    infixToPostfix(infix, postfix);
    
    
    int result = evaluatePostfix(postfix);
    printf("Final result: %d\n", result);
    
    return 0;
}
