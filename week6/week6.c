#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#define MAXSIZE 100

// 연결리스트 노드 구조체
typedef struct node {
    char data;
    struct node *next;
} node;

// 스택 구조체
typedef struct stack{
    node *top;
    int len;
} stack;

// 스택이 비어있는지 검사
bool is_empty (stack* myStack) {
    return myStack->len == 0;
}

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

// 스택에 요소 추가 (push)
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

// 스택에서 요소 제거하고 반환 (pop)
char pop(stack* myStack) {
    if (is_empty(myStack)) {
        return '\0';
    }
    node *topNode = myStack->top;
    char data = topNode->data;
    myStack->top = topNode->next;
    free(topNode);
    myStack->len--;
    return data;
}

// 스택의 top 요소 반환 (peek)
char peek(stack* myStack) {
    return myStack->top->data;
}

// 스택 활용해 수식 괄호 검사 진행
bool checkBrackets(char* input) {
    stack *myStack;
    myStack->top = NULL;
    myStack->len = 0;

    for (int i = 0; input[i] != '\0'; i++) {
        char ch = input[i]; // 각각의 문자에 대해 검사
        if (ch == '(')
            push(myStack, ch);
        else if (ch == ')') {
            if (is_empty(myStack))  // 빈 스택인데 닫는 괄호가 나오면 오류
                return false;
            else {
                char topChar = pop(myStack);    // 스택에서 여는 괄호 pop 한 뒤 짝 맞는지 확인
                if (topChar != '(')             // 여는 괄호와 짝이 안 맞음
                    return false;
            }
        }
    }

    if (!is_empty(myStack)) // 남아 있는 여는 괄호가 있다면 짝이 안맞음
        return false;

    return true;
}

// 연산자 우선순위 판별 (우선순위 높을수록 큰 값 리턴)
int priority(char op) {
    if (op == '+' || op == '-')
        return 1;
    else if (op == '*' || op == '/')
        return 2;
    return 0;
}

// 입력 받은 수식을 후위 표기식으로 변환
char* infixToPostfix(char* input) {
    stack *myStack = create();
    // 결과를 저장할 배열
    char *postfix = (char *)malloc(sizeof(char) * (strlen(input) + 1));

    int index = 0;

    for (int i = 0; input[i] != '\0'; i++) {
        char ch = input[i];

        // 숫자인 경우 후위표기식에 바로 추가
        if (isdigit(ch))
            postfix[index++] = ch;
        // 여는 괄호일 경우 스택에 추가
        else if (ch == '(')
            push(myStack, ch);
        // 닫는 괄호일 경우 
        else if (ch == ')') {
            // 스택에서 여는 괄호(짝) 나올 때까지 pop하고 후위 표현식에 추가
            while (!is_empty(myStack) && peek(myStack) != '(')
                postfix[index++] = pop(myStack);
            // 스택에서 여는 괄호 제거해서 짝을 제거
            pop(myStack);
        } else {
            // 현재 연산자의 우선순위가 top에 있는 연산자의 우선순위보다 높/같일때
            while (!is_empty(myStack) && priority(ch) <= priority(peek(myStack)))
                // 스택에서 연산자 pop해서 후위 표현식에 추가
                postfix[index++] = pop(myStack);
            // 현재 연산자를 스택에 추가
            push(myStack, ch);
        }
    }
    // 스택에 남아 있는 모든 연산자를 후위 표기식에 추가하고 널문자 추가
    while (!is_empty(myStack))
        postfix[index++] = pop(myStack);
    postfix[index] = '\0';

    free(myStack);

    return postfix;
}

// 후위 표기식 계산해 결과 출력
int calculate(char* postfix) {
    stack *myStack = create();
    for (int i = 0; postfix[i] != '\0'; i++)
    {
        char ch = postfix[i];
        // 숫자일 경우 스택에 추가
        if (isdigit(ch))
            push(myStack, ch - '0');
        // 연산자일 경우
        else {
            // 연산할 숫자를 변수에 저장
            int op2 = pop(myStack);
            int op1 = pop(myStack);
            int result;
            switch (ch) {
                case '+':
                    result = op1 + op2;
                    break;
                case '-':
                    result = op1 - op2;
                    break;
                case '*':
                    result = op1 * op2;
                    break;
                case '/':
                    result = op1 / op2;
                    break;
            }
            // 스택에 연산된 결과를 추가
            push(myStack, result);  
        }
    }
    // 최종 연산 결과를 pop
    int result = pop(myStack);
    free(myStack);
    return result;
}

int main() {
    char userInput[100];

    while (1) {
        printf("수식을 입력하세요(종료는 Q): ");
        fgets(userInput, sizeof(userInput), stdin);

        if (strcmp(userInput, "Q\n") == 0 || strcmp(userInput, "q\n") == 0)
            break;

        if (!checkBrackets(userInput)) {
            printf("잘못된 입력입니다. 다시 입력하세요.\n");
            continue;
        }

        bool brackets = checkBrackets(userInput);
        printf("괄호 검사: %s\n", brackets ? "성공" : "실패");

        char *postfix = infixToPostfix(userInput);
        printf("후위 표기식: %s\n", postfix);

        int result = calculate(postfix);
        printf("계산 결과: %d\n", result);
    }

    return 0;
}