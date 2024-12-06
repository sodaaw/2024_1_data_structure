#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// 노드 구조체
typedef struct Node {
    char data;
    struct Node *next;
} node;

// 연결리스트 구조체
typedef struct linkedlist {
    node* head;
    node *position;    
    int current;
    int len;
} linkedList;
 
// 연결리스트 생성
linkedList* create() {
    linkedList *list = (linkedList*)malloc(sizeof(linkedList));
    if (list == NULL) {
        printf("메모리 할당에 실패했습니다.\n");
        exit(EXIT_FAILURE);
    }
    list->head = NULL;
    list->position = NULL;
    list->current = 0;
    list->len = 0;
    return list;
}

// 맨 뒤에 요소 삽입
void addTail(linkedList* myList, char data) {
    node *newNode = (node *)malloc(sizeof(node));
    if (newNode == NULL) {
        printf("메모리 할당에 실패했습니다.\n");
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->next = NULL;

    // 빈 리스트인 경우
    if (myList->head == NULL) {
        myList->head = newNode;
        myList->position = newNode;
    } else {
        if (myList->position->next != NULL) {
            node *currentNode = myList->head;     
            while (currentNode->next != NULL) {
                currentNode = currentNode->next;    
            }
            myList->position = currentNode;        
        }
        myList->position->next = newNode;
        myList->position = newNode;
    }

    myList->len++;
    myList->current++;
}

// 현재 위치가 맨 앞이 아닌 경우 리스트에 요소 삽입
void add(linkedList* myList, char data) {
    node *newNode = (node *)malloc(sizeof(node));
    if (newNode == NULL) {
        printf("메모리 할당에 실패했습니다.\n");
        exit(EXIT_FAILURE);
    }
    newNode->data = data;

    // 현재 노드가 마지막 노드인 경우
    if (myList->position == NULL) {
        myList->head = newNode;
        myList->position = newNode;
        newNode->next = NULL;
        myList->current = 0;
    }
    else {
        newNode->next = myList->position->next;
        myList->position->next = newNode;
        myList->position = newNode;
        myList->current++;
    }

    myList->len++;
}

// 명령어가 < 일때 쓰이는 맨 앞에 요소 추가 함수
void addHead(linkedList* myList, char data) {
    node* newNode = (node *)malloc(sizeof(node));
    if (newNode == NULL) {
        printf("메모리 할당에 실패했습니다.\n");
        exit(EXIT_FAILURE);
    }
    newNode->data = data;

    if (myList->head != NULL) {
        newNode->next = myList->head;
    } else {
        newNode->next = NULL;
    }
    myList->head = newNode;
    myList->position = newNode;
    myList->len++;
    myList->current = 0;
}

// 리스트 출력
void print(linkedList* myList) {
    node *currentNode = myList->head;     
    if (currentNode == NULL)
        printf("빈 배열입니다. ");
    else {
        printf("현재 배열: ");
        while (currentNode != NULL) {
            if (currentNode == myList->position)
                printf("(%c) ", currentNode->data);
            else
                printf("%c ", currentNode->data);
            currentNode = currentNode->next;
        }
        printf("\n");
    }
}

// 현재 요소 출력
void getData(linkedList* myList) {
    printf("현재 요소: %c (", myList->position->data);
    node *currentNode = myList->head;
    while (currentNode != NULL) {
            if (currentNode == myList->position)
                printf("(%c) ", currentNode->data);
            else
                printf("%c ", currentNode->data);
            currentNode = currentNode->next;
        }
    printf(")\n");
}

// 맨 앞으로 이동
void traverseFront(linkedList* myList) {
    myList->position = myList->head;
    myList->current = 0;
}

// 맨 뒤로 이동
void traverseRear(linkedList* myList) {
    node *currentNode = myList->head;
    while (currentNode->next != NULL) {
        currentNode = currentNode->next;
    }
    myList->position = currentNode;
    myList->current = myList->len;
}

// 앞으로 1 이동
void goPrevious(linkedList* myList) {
    // 현재 노드가 헤드인 경우 종료
    if (myList->position == myList->head)
        return;

    node *previous = myList->head;
    while (previous->next != myList->position) {
        previous = previous->next;
    }

    myList->position = previous;
    myList->current--;
}

// 뒤로 1 이동
void goNext(linkedList* myList) {
    myList->position = myList->position->next;
    myList->current++;
}

// 현재 요소 삭제
void deleteNode(linkedList* myList) {
    node *toDelete = myList->position;
    node *previous = NULL;

    // 현재 노드가 헤드 노드일 경우 다음 노드를 새 헤드 노드로 설정
    if (toDelete == myList->head) {
        myList->head = myList->head->next;
    }
    else {
        node *currentNode = myList->head;
        while (currentNode != NULL && currentNode != myList->position) {
            previous = currentNode;
            currentNode = currentNode->next;
        }
        if (previous != NULL) {
            previous->next = toDelete->next;
        }
    }

    // 삭제된 노드가 마지막 노드일 경우
    if (toDelete->next == NULL) {
        myList->position = myList->head;
        myList->current = 0;
    }
    else {
        myList->position = toDelete->next;
    }

    free(toDelete);
    myList->len--;
}

// 현재 요소를 다른 요소로 대체
void replace(linkedList* myList, char newData) {
    myList->position->data = newData;
}

// 현재 리스트의 요소 개수 출력
void dataCount(linkedList* myList) {
    printf("현재 요소 개수: %d\n", myList->len);
}

// 해당 요소가 리스트에 존재하는지, 존재한다면 몇 번째 요소인지
void isMember(linkedList* myList, char data) {
    node *currentNode = myList->head->next;
    int index = 1;
    int found = 0;
    while (currentNode != NULL) {
        if (currentNode->data == data) {
            printf("%d: ", index + 1);
            node *printNode = myList->head;
            while (printNode != NULL) {
                if (printNode->data == data)
                    printf("(%c) ", printNode->data);
                else
                    printf("%c ", printNode->data);
                printNode = printNode->next;
            }
            printf("\n");
            found = 1;
            break;
        }
        currentNode = currentNode->next;
        index++;
    }
    if (!found)
        printf("%c는 리스트에 존재하지 않습니다.\n", data);
}

// 리스트가 비어있는지 확인
void isEmpty(linkedList* myList) {
    if (myList->head == NULL) {
        printf("True\n");
    } else {
        printf("False\n");
    }
}

// 리스트 비우기
void emptyList(linkedList* myList) {
    if (myList == NULL || myList->head == NULL) {
        printf("리스트가 이미 비어 있거나 유효하지 않습니다.\n");
        return;
    }

    node* currentNode = myList->head;
    node* nextNode;

    while (currentNode->next != NULL) {
        nextNode = currentNode->next;
        free(currentNode);
        currentNode = nextNode;
    }

    myList->head = NULL; 
    myList->position = NULL;
    myList->len = 0;
    myList->current = 0;
}

// 창작 기능
// 1. 중복된 요소를 첫 번째만 남기고 제거하는 함수 (현재 포지션은 맨 앞으로)
void removeSame(linkedList* myList) {
    node *currentNode = myList->head;

    while (currentNode != NULL) {
        node *runner = currentNode;

        while (runner->next != NULL) {
            if (runner->next->data == currentNode->data) {
                node *temp = runner->next;
                runner->next = runner->next->next;
                free(temp);
                myList->len--;
            }
            else {
                runner = runner->next;
            }
        }
        currentNode = currentNode->next;
    }
    myList->position = myList->head;
    myList->current = 0;
}

// 2. 리스트의 요소를 역순으로 출력 (재귀함수 이용)
void printReverse(linkedList* myList, int count) {
    if (count == -1)
        return;
    node *currentNode = myList->head;
    for (int i = 0; i < count; i++) {
        currentNode = currentNode->next;
    }
    printf("%c ", currentNode->data);
    printReverse(myList, --count);
}

// 3. 리스트에 해당 요소가 몇개인지 세기
void howMuchData (linkedList* myList, char data) {
    node* currentNode = myList->head;
    int count = 0;
    while (currentNode != NULL) {
        if (currentNode->data == data) {
            count++;
        }
        currentNode = currentNode->next;
    }
    if (count == 0)
        printf("%c는 리스트 내에 존재하지 않습니다.\n", data);
    printf("리스트 내에 %c가 %d개 있습니다.\n", data, count);
}

int main() {
    linkedList *list = (linkedList*)malloc(sizeof(linkedList));
    node *newnode = (node*)malloc(sizeof(node));

    list->head = NULL;
    list->position = list->head;
    list->current = 0;
    list->len = 0;

    int exit_loop = 0;

    printf("-----------------명령어 목록----------------\n");
    printf("리스트 끝에 추가: +\n");
    printf("리스트 출력: L\n");
    printf("맨 앞으로 이동: <\n");
    printf("맨 뒤로 이동: >\n");
    printf("요소 삭제: -\n");
    printf("앞으로 1 이동: P\n");
    printf("뒤로 1 이동: N\n");
    printf("요소 개수 출력: #\n");
    printf("해당 요소가 몇 번째 요소인지: ?\n");
    printf("리스트 비우기: C\n");
    printf("리스트가 비어있는지 확인: E\n");
    printf("중복된 요소를 첫 번째만 남기고 제거(현재 포지션은 맨 앞으로): ~\n");
    printf("리스트 역순 출력: R\n");
    printf("리스트 내에서 요소 개수 세기: !요소\n");

    while (!exit_loop) {
        char input[30] = {0};

        if (list->head == NULL)
            printf("빈 배열입니다. ");

        printf("명령어를 입력하세요 : ");
        fgets(input, sizeof(input), stdin);
        int inputLength = strlen(input);

        // 입력 숫자 마이너스인 경우도 구현?
        for (int i = 0; i < inputLength; i++) {
            switch (input[i]) {
            case '+':
                add(list, input[i + 1]);
                i++;
                break;
            case 'L':
                print(list);
                break;
            case 'G':
                getData(list);
                break;
            case '<':
                traverseFront(list);
                if (input [i + 1] == 'N') {
                    goNext(list);
                    i += 1;
                }
                else if (input[i + 1] == '+') {
                    addHead(list, input[i + 2]);
                    i += 2;
                }
                break;
            case '>':
                traverseRear(list);
                break;
            case 'P':
                goPrevious(list);
                break;
            case 'N':
                goNext(list);
                break;
            case '-':
                deleteNode(list);
                break;
            case '=':
                replace(list, input[i + 1]);
                break;
            case '#':
                dataCount(list);
                break;
            case '?':
                isMember(list, input[i + 1]);
                break;
            case 'E':
                isEmpty(list);
                break;
            case 'C':
                emptyList(list);
                break;
            case '~':
                removeSame(list);
                break;
            case 'R':
                printReverse(list, list->len - 1);
                break;
            case '!':
                howMuchData(list, input[i + 1]);
                break;
            case 'Q':
            case 'q':
                emptyList(list);
                exit_loop = 1;
            default:
                if (isdigit(input[i])) {
                    int num = input[i] - '0';
                    traverseFront(list);
                    for (int j = 0; j < num - 1; j++) {
                        goNext(list);
                    }
                }
                break;
            }
        }
    }
    return 0;
}