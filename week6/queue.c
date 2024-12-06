#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define MAXSIZE 100

// 노드 구조체
typedef struct node{    
    char data;
    struct node* next;
}node;

// 큐 구조체
typedef struct queue{   
    node* head;
    node* tail;
    int size;
    int head_index;
    int tail_index;
} queue;

// 큐 생성
queue* create() {
    queue *que = (queue*)malloc(sizeof(queue));
    if (que == NULL) {
        printf("메모리 할당 실패\n");
        exit(EXIT_FAILURE);
    }
    que->size = 0;
    que->head = NULL;
    que->tail = NULL;
    que->head_index = -1;
    que->tail_index = -1;
    return que;
}

// 큐가 비어있는지 확인
bool is_empty(queue* que) {
    if (que->size == 0)
        return true;
    else
        return false;
}

// 큐가 꽉 찼는지 확인
bool is_full(queue* que) {
    if (que->size == MAXSIZE)
        return true;
    else
        return false;
}

// 큐에 요소 추가
void enqueue(queue* que, char data) {
    if (is_full(que)) {
        printf("큐가 꽉 찼습니다.\n");
        return;
    }

    node *newNode = (node*)malloc(sizeof(node));
    newNode->data = data;
    newNode->next = NULL;

    if (is_empty(que))
        que->head = newNode;
    else 
        que->tail->next = newNode;

    que->tail = newNode;
    que->size++;
    que->tail_index++;
}

// 큐의 head 요소 출력
void peek(queue* que) {
    printf("%c\n", que->head->data);
}

// 큐의 요소 개수 출력
void data_count(queue* que) {
    printf("%d\n", que->size);
}

// 큐의 요소 출력
void print(queue* que) {
    node *current = que->head;
    for (int i = 0; i < que->size; i++) {
        printf("%c ", current->data);
        current = current->next;
    }
    printf("\n");
}

// 큐에서 요소 제거
void dequeue(queue* que) {
    if (is_empty(que)) {
        printf("Error (nothing to dequeue)\n");
        return;
    }
    node *temp = que->head;
    que->head = que->head->next;

    free(temp);
    que->size--;

    if (is_empty(que))
        que->tail = NULL;
    else
        que->tail->next = que->head;

    que->head_index++;
}

// 큐에 존재하는 요소인지 판별
bool is_member(queue* que, char data) {
    node *current = que->head;
    while (current != NULL) {
        if (current->data == data)
            return true;
        current = current->next;
    }
    return false;
}

// 큐 비우기
void clear(queue* que) {
    if (is_empty(que)) {
        printf("이미 빈 큐입니다.\n");
        return;
    }
    node *current = que->head;
    node *nextNode;
    while (current->next != NULL) {
        nextNode = current->next;
        free(current);
        current = nextNode;
    }
    que->size = 0;
    que->head = NULL;
    que->tail = NULL;
    que->head_index = -1;
    que->tail_index = -1;
}

// tail 요소 대체
void replace(queue* que, char newData) {
    que->tail->data = newData;
}

// head 인덱스 출력
void head(queue* que) {
    printf("%d\n", que->head_index + 2);
}

// tail 인덱스 출력
void tail(queue* que) {
    printf("%d\n", que->tail_index + 1);
}

// 창작 기능
// 1. 해당 요소가 몇 개인지 세기
void countData(queue* que, char data) {
    if (is_empty(que)) {
        printf("빈 큐입니다.\n");
        return;
    }
    node *current = que->head;
    int count = 0;
    while (current != NULL) {
        if (current->data == data) 
            count++;
        current = current->next;
    }

    if (count == 0)
        printf("%c는 큐에 존재하지 않습니다.\n", data);
    else
        printf("%c는 큐에 %d개 존재합니다.\n", data, count);
}

// 2. 알파벳순으로 가장 뒤에 있는 문자 출력
void alphaSort(queue* que) {
    char maxChar = que->head->data;

    node *current = que->head;
    while (current->next != NULL)
    {
        char currentChar = current->data;
        if (currentChar > maxChar) {
            maxChar = current->data;
        }
        current = current->next;
    }
    printf("%c\n", maxChar);
}

// 3. 큐 요소를 대문자로 변경
void toUpper(queue* que) {
    node *current = que->head;
    while (current != NULL) {
        current->data = toupper(current->data);
        current = current->next;
    }
}

int main() {
    queue *myQueue = create();

    int exit_loop = 0;

    printf("명령어 목록\n");
    printf("enqueue: +\n");
    printf("dequeue: -\n");
    printf("큐의 요소 출력: L\n");
    printf("큐가 비어있는지 확인: E\n");
    printf("큐가 꽉 차있는지 확인: F\n");
    printf("큐의 head 요소 출력: P\n");
    printf("큐의 요소 개수 출력: #\n");
    printf("tail 요소 대체: =\n");
    printf("큐에 존재하는 요소인지 판별: ?\n");
    printf("해당 요소가 몇 개인지 세기: *\n");
    printf("알파벳순으로 가장 뒤에 있는 요소 출력: A\n");
    printf("큐의 요소 대문자로 변경: U\n");
    printf("head 인덱스 번호 출력: H\n");
    printf("tail 인덱스 번호 출력: T\n");
    printf("큐 비우기: C\n");
    printf("종료: Q\n");

    while (!exit_loop) {
        char input[30] = {0};

        printf("명령어를 입력하세요: ");
        fgets(input, sizeof(input), stdin);
        int inputLength = strlen(input);

        for (int i = 0; i < inputLength; i++) {
            bool isFull, isEmpty, isMember;

            switch(input[i]) {
                case '+':
                    enqueue(myQueue, input[i + 1]);
                    i++;
                    break;
                case '-':
                    dequeue(myQueue);
                    break;
                case 'L':
                    print(myQueue);
                    break;
                case 'E':
                    isEmpty = is_empty(myQueue);
                    printf("%s\n", isEmpty ? "True" : "False");
                    break;
                case 'F':
                    isFull = is_full(myQueue);
                    printf("%s\n", isFull ? "True" : "False");
                    break;
                case 'P':
                    peek(myQueue);
                    break;
                case '#':
                    data_count(myQueue);
                    break;
                case '=':
                    replace(myQueue, input[i + 1]);
                    break;
                case '?':
                    isMember = is_member(myQueue, input[i + 1]);
                    printf("%s\n", isMember ? "True" : "False");
                    break;
                case '*':
                    countData(myQueue, input[i + 1]);
                    break;
                case 'A':
                    alphaSort(myQueue);
                    break;
                case 'U':
                    toUpper(myQueue);
                    break;
                case 'H':
                    head(myQueue);
                    break;
                case 'T':
                    tail(myQueue);
                    break;
                case 'C':
                    clear(myQueue);
                    break;
                case 'Q':
                case 'q':
                    exit_loop = 1;
                default:
                    if (isdigit(input[i])) {
                        int num = input[i] - '0';
                        for (int j = 0; j < num - 1; j++)
                            dequeue(myQueue);
                    }
                    break;
            }
        }
    }
    return 0;
}