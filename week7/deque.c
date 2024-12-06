// 양방향 연결리스트를 활용한 덱 구현
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// 노드 구조체
typedef struct node{    
    char data;
    struct node* next;
    struct node* prev;
}node;

// 덱 구조체
typedef struct deque{   
    node* front;
    node* rear;
    int size;
    int max_size;   // 덱의 최대 크기
}deque;

// 함수 사용 전 선언
bool is_empty(const deque* deq);
bool is_full(const deque* deq);

// 새로운 덱 만드는 함수 
deque* new_deque(int max_size) {
    deque* deq = (deque*)malloc(sizeof(deque));
    if (deq == NULL) {
        printf("Not enough memory");
        exit(EXIT_FAILURE);
    }
    deq->size = 0;      // 덱의 크기 0으로 초기화
    deq->front = NULL;      // 덱의 첫 요소 
    deq->rear = NULL;       // 덱의 마지막 요소
    deq->max_size = max_size;   // 덱의 최대 크기 초기화
    return deq;
}

// 새로운 데이터를 넣을 노드를 만드는 함수
node* new_node(const char data){
    node* another = (node*)malloc(sizeof(node));
    if (another == NULL){
        printf("Not enough memory");
        exit(EXIT_FAILURE);
    }
    another->data = data;
    another->next = NULL;
    another->prev = NULL;  
    return another;
}

// 1. 덱의 앞 부분에 새 노드 추가
void enqueue_front(deque* deq, const char data){
    if (deq == NULL){   // 예외처리: 덱이 유효하지 않은 경우
        printf("유효하지 않은 덱");
        exit(EXIT_FAILURE);
    }
    node* newnode = new_node(data);     // 새로운 덱 생성, 데이터 추가
    if (is_full(deq)) {     // 덱이 가득 찬 경우
        printf("덱이 가득 찼습니다");
        free(newnode);
        return;
    }
    if (is_empty(deq)) {    // 덱이 빈 경우 앞뒤에 새 노드의 주소 저장
        deq->front = deq->rear = newnode;
    }
    else {      // 덱이 비어있지 않은 경우
        newnode->next = deq->front;
        deq->front->prev = newnode;
        deq->front = newnode;
    }
    deq->size++;    // 덱의 크기 증가
}

// 2. 덱의 앞 부분에서 노드 삭제
void dequeue_front(deque* deq){
    if (deq == NULL){   
        printf("유효하지 않은 덱");
        exit(EXIT_FAILURE);
    }
    if (is_empty(deq)){
        printf("비어 있는 덱");
        return;
    }
    node* temp = deq->front;    // 이동 위한 임시 노드 temp
    if(deq->front == deq->rear){    // 덱에 노드가 하나 있는 경우
        deq->front = deq->rear = NULL;
    }
    else{
        deq->front = deq->front->next;
        deq->front->prev = NULL;
    }
    free(temp);
    deq->size--;
}


// 3. 덱의 뒷 부분에 새 노드 추가
void enqueue_rear(deque* deq, const char data){
    if (deq == NULL){   
        printf("유효하지 않은 덱");
        exit(EXIT_FAILURE);
    }
    node* newnode = new_node(data);     // 새로운 덱 생성, 데이터 추가
    if (is_full(deq)) {     // 덱이 가득 찬 경우
        printf("덱이 가득 찼습니다");
        free(newnode);
        return;
    }
    if (is_empty(deq)) {    // 덱이 빈 경우 앞뒤에 새 노드의 주소 저장
        deq->front = deq->rear = newnode;
    }
    else {      // 덱이 비어있지 않은 경우
        newnode->prev = deq->rear;
        deq->rear->next = newnode;
        deq->rear = newnode;
    }
    deq->size++;    // 덱의 크기 증가
}

// 4. 덱의 뒷 부분에서 노드 삭제
void dequeue_rear(deque* deq){
    if (deq == NULL){   
        printf("유효하지 않은 덱");
        exit(EXIT_FAILURE);
    }
    if (is_empty(deq)) {
        printf("비어 있는 덱");
        return;
    }
    node* temp = deq->rear;    // 이동 위한 임시 노드 temp
    if(deq->front == deq->rear){    // 덱에 노드가 하나 있는 경우
        deq->front = deq->rear = NULL;
    }
    else{
        deq->rear = deq->rear->prev;
        deq->rear->next = NULL;
    }
    free(temp);
    deq->size--;
}

// 덱이 비어있는지 알려주는 함수
bool is_empty(const deque* deq){
    if (deq == NULL){   // 비어있는 덱인 경우
        printf("유효하지 않은 덱");
        return true;
    }
        return deq->front == NULL && deq->rear == NULL;  // 양방향 연결리스트라서 양쪽 모두 검사
}

// 덱이 가득 차 있는지 알려주는 함수
bool is_full(const deque* deq) {
    return deq->size == deq->max_size;
}

// 덱의 요소 출력
void display(deque *deq){
    node* temp;     // 이동 위한 임시 노드
    if(is_empty(deq)){
        printf("Deque is empty");
    }
    else{
        temp = deq->front;       // temp 노드가 맨 앞을 가리키게 설정
        while(temp != 0){   
            printf("%c", temp->data);   // 노드의 데이터 출력
            temp = temp->next;          // 다음 노드로 이동
        }
    }
}

// 덱의 front 요소 출력
void peek(const deque* deq){
    if(is_empty(deq)){
        printf("Deque is empty");
    }
    else{
        printf("%c", deq->front->data);
    }
}

// 덱 안에 값이 몇 개 들어 있는지 알려주는 함수
int size(const deque* deq){
    if (is_empty(deq)) return 0;
    return deq->size;
}

// target 문자가 덱 안에 존재하는지 알려주는 함수
bool is_member(const deque* deq, const char target){
    if(is_empty(deq)) return false;

    node* temp = deq->front;    // temp 노드에 맨 앞 주소 저장
    while (temp != NULL) {        
        if (temp->data == target) return true;    // 원하는 문자를 찾은 경우
        temp = temp->next;             // 찾지 못한 경우 다음 노드로 이동
    }

    if (temp) return true;      // null이 아닌 모든 값은 true 취급
    return false;               // 찾지 못했을 경우
}

// 다 쓴 덱을 삭제하는 함수
void clear_deque(deque** deq){
    while(!is_empty(*deq))
        dequeue_front(*deq);
    free(*deq);
    *deq = NULL;
}

// 마지막 값을 바꾸는 함수
void replace_rear(deque* deq, const char target){
    if(is_empty(deq)) return;
    deq->rear->data = target;
}

int main() {
    // 새로운 덱 생성 (최대 크기 5로 가정)
    deque* myDeque = new_deque(5);

    // 1. 덱의 앞 부분에 새 노드 추가
    enqueue_front(myDeque, 'A');
    enqueue_front(myDeque, 'B');
    enqueue_front(myDeque, 'C');

    // 2. 덱의 앞 부분에서 노드 삭제
    dequeue_front(myDeque);

    // 3. 덱의 뒷 부분에 새 노드 추가
    enqueue_rear(myDeque, 'D');
    enqueue_rear(myDeque, 'E');
    enqueue_rear(myDeque, 'F');

    // 4. 덱의 뒷 부분에서 노드 삭제
    dequeue_rear(myDeque);

    // 덱의 상태 출력
    printf("Deque after operations: ");
    display(myDeque);
    printf("\n");

    // 덱이 비어있는지 확인
    if (is_empty(myDeque)) {
        printf("Deque is empty.\n");
    } else {
        printf("Deque is not empty.\n");
    }

    // 덱 크기 출력
    printf("Deque size: %d\n", size(myDeque));

    // 덱의 front 요소 출력
    printf("Front element: ");
    peek(myDeque);
    printf("\n");

    // 특정 값으로 덱의 마지막 값을 바꾸기
    replace_rear(myDeque, 'X');

    // 덱의 상태 출력
    printf("Deque after replacing rear element: ");
    display(myDeque);
    printf("\n");
 
    // 특정 값이 덱에 존재하는지 확인
    char target = 'D';
    if (is_member(myDeque, target)) {
        printf("%c exists in the deque.\n", target);
    } else {
        printf("%c does not exist in the deque.\n", target);
    }

    // 다 쓴 덱 삭제
    clear_deque(&myDeque);

    return 0;
}