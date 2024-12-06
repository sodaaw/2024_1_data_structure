#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define MAXSIZE 100

// 노드 구조체
typedef struct node {
    char data;
    struct node *next;
} node;

// 스택 구조체
typedef struct stack {
    node *top;
    int len;
} stack;

// 스택 생성
stack* create() {
    stack *myStack = (stack*)malloc(sizeof(stack));
    if (myStack == NULL) {
        printf("메모리 할당 실패\n");
        exit(EXIT_FAILURE);
    }
    myStack->len = 0;
    myStack->top = NULL;

    return myStack;
}

// 스택이 비어있는지 검사
bool is_empty (stack* myStack) {
    return myStack->len == 0;
}

// 스택에 요소 추가
void push(stack* myStack, char data) {
    if (myStack->len == MAXSIZE) {
        printf("스택이 꽉 찼습니다.\n");
        return;
    }

    node *newNode = (node *)malloc(sizeof(node));

    if (newNode == NULL) {
        printf("메모리 할당 실패\n");
        exit(EXIT_FAILURE);
    }

    newNode->data = data;
    newNode->next = (struct node*)myStack->top;
    myStack->top = newNode;
    myStack->len++;
}

// 스택에서 요소 제거하고 반환 
char pop(stack* myStack) {
    if (is_empty(myStack)) {
        printf("Error (nothing to pop)\n");
        return '\0';
    }
    node *topNode = myStack->top;
    char data = topNode->data;
    myStack->top = topNode->next;
    free(topNode);
    myStack->len--;
    return data;
}

// 스택 출력
void print(stack* myStack) {
    if (is_empty(myStack)) {
        printf("빈 스택입니다.\n");
        return;
    }

    stack *newStack = create();

    node *currentNode = myStack->top;
    while (currentNode != NULL) {
        push(newStack, currentNode->data);
        currentNode = currentNode->next;
    }

    while (!is_empty(newStack)) {
        char data = pop(newStack);
        if (!is_empty(newStack))
            printf("%c ", data);
        else
            printf("(%c)", data);
    }
    printf("\n");
    free(newStack);
}

// 스택이 꽉 차있는지 검사
void is_full(stack* myStack) {
    if (myStack->len == MAXSIZE)
        printf("True\n");
    else
        printf("False\n");
}

// 스택 맨 위 요소 출력
void peek(stack* myStack) {
    printf("%c\n", myStack->top->data);
}

// 스택의 요소 개수 출력
void element_count(stack* myStack) {
    printf("%d\n", myStack->len);
}

// 스택 맨 위 요소와 위치 출력
void top(stack* myStack) {
    printf("(%d, %c)\n", myStack->len, myStack->top->data);
}

// 해당 요소가 스택에 존재하는지 검사
void is_member(stack* myStack, char data) {
    stack *newStack = create();
    stack *tempStack = create();

    node *currentNode = myStack->top;
    while (currentNode != NULL) {
        push(newStack, currentNode->data);
        push(tempStack, currentNode->data);
        currentNode = currentNode->next;
    }

    bool found = false;
    while (!is_empty(tempStack)) {
        char tempData = pop(tempStack);
        if (tempData == data) {
            printf("True\n");
            found = true;
            break;
        }
    }

    if (!found)
        printf("False\n");

    free(newStack);
    free(tempStack);
}

// 스택의 요소 교체
void replace(stack* myStack, char new_data) {
    myStack->top->data = new_data;
}

// 스택 비우기
void clear(stack* myStack) {
    while (!is_empty(myStack))
        pop(myStack);
}

// 창작 기능
// 1. 중복된 요소 제거
void removeSame(stack* myStack) {
    if (is_empty(myStack))
        return;

    stack* tempStack = create();
    char current;

    while (!is_empty(myStack)) {
        current = pop(myStack);

        bool found = false;
        node* temp = tempStack->top;
        while (temp != NULL) {
            if (temp->data == current) {
                found = true;
                break;
            }
            temp = temp->next;
        }

        if (!found)
            push(tempStack, current);
    }

    while (!is_empty(tempStack))
        push(myStack, pop(tempStack));

    free(tempStack);
}

// 2. 알파벳순으로 가장 앞에 있는 문자를 출력
void findMin(stack* myStack) {
    char minChar = 'z';
    stack *tempStack = create();

    while (!is_empty(myStack)) {
        char current = pop(myStack);
        if (current < minChar)
            minChar = current;
        push(tempStack, current);
    }

    while (!is_empty(tempStack))
        push(myStack, pop(tempStack));

    printf("%c\n", minChar);
}

// 3. 현재 스택을 현재 스택 뒤에 붙여줌
void cat(stack* myStack) {
    stack *tempStack = create();

    node *currentNode = myStack->top;
    while (currentNode != NULL) {
        push(tempStack, currentNode->data);
        currentNode = currentNode->next;
    }

    while (!is_empty(tempStack)) {
        char data = pop(tempStack);
        push(myStack, data);
    }

    free(tempStack);
}

// 개행 문자 제거
void removeNewLine(char* str) {
    int len = strlen(str);
    if (str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}

int main() {
    stack *myStack = create();

    int exit_loop = 0;

    printf("명령어 목록\n");
    printf("push: +\n");
    printf("pop: -\n");
    printf("스택 출력: L\n");
    printf("스택 맨 위 요소 출력: P\n");
    printf("스택이 꽉 차있는지 검사: F\n");
    printf("스택의 요소 개수 출력: #\n");
    printf("스택의 맨 위 요소와 위치 출력: T\n");
    printf("요소가 스택 안에 있는지 검사: ?\n");
    printf("스택의 요소 교체: =\n");
    printf("중복된 요소 제거: R\n");
    printf("사전순으로 제일 앞에 있는 요소 출력: D\n");
    printf("현재 스택을 현재 스택 뒤에 붙이기: W\n");
    printf("스택 비우기: C\n");
    printf("종료: Q\n");

    while (!exit_loop) {
        char input[30] = {0};

        printf("명령어를 입력하세요: ");
        fgets(input, sizeof(input), stdin);
        //removeNewLine(input);
        int inputLength = strlen(input);

        for (int i = 0; i < inputLength; i++) {
            switch (input[i]) {
                case '+':
                    push(myStack, input[i + 1]);
                    i++;
                    break;
                case '-':
                    printf("%c ", pop(myStack));
                    break;
                case 'L':
                    print(myStack);
                    break;
                case 'P':
                    peek(myStack);
                    break;
                case 'F':
                    is_full(myStack);
                    break;
                case '#':
                    element_count(myStack);
                    break;
                case 'T':
                    top(myStack);
                    break;
                case '?':
                    is_member(myStack, input[i + 1]);
                    i++;
                    break;
                case '=':
                    replace(myStack, input[i + 1]);
                    i++;
                    break;
                case 'R':
                    removeSame(myStack);
                    break;
                case 'D':
                    findMin(myStack);
                    break;
                case 'W':
                    cat(myStack);
                    break;
                case 'C':
                    clear(myStack);
                    break;
                case 'Q':
                case 'q':
                    exit_loop = 1;
                default:
                    if (isdigit(input[i])) {
                        int num = input[i] - '0';
                        for (int j = 0; j < num; j++)
                            printf("%c ", pop(myStack));
                    }
                    i++;
                    break;
            }
        }
    }
    return 0;
}