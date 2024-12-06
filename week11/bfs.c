#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// 간선 구조체
typedef struct Edge {
    struct Edge *next;    
    struct Vertex *start;
    struct Vertex *end;
} edge;

// 정점 구조체
typedef struct Vertex {
    int data;
    bool visited;           
    struct Vertex *next;    
    struct Edge *edges;     
} vertex;

// 그래프 구조체
typedef struct Graph {
    int numVertices;       
    int numEdges;          
    vertex *vertices;      
} graph;

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
    queue *q = (queue*)malloc(sizeof(queue));
    if (q == NULL) {
        printf("메모리 할당 실패\n");
        exit(EXIT_FAILURE);
    }
    q->size = 0;
    q->head = NULL;
    q->tail = NULL;
    q->head_index = -1;
    q->tail_index = -1;
    return q;
}

// 큐가 비어있는지 확인
bool isEmptyQ(queue* q) {
    if (q->size == 0)
        return true;
    else
        return false;
}

// 큐에 요소 추가
void enqueue(queue* q, char data) {
    node *newNode = (node*)malloc(sizeof(node));
    newNode->data = data;
    newNode->next = NULL;

    if (isEmptyQ(q))
        q->head = newNode;
    else 
        q->tail->next = newNode;

    q->tail = newNode;
    q->size++;
    q->tail_index++;
}

// 큐에서 요소 제거
int dequeue(queue* q) {
    if (isEmptyQ(q)) {
        printf("Error (nothing to dequeue)\n");
        return -1;
    }
    node *temp = q->head;
    int data = temp->data;
    q->head = q->head->next;

    if (q->head == NULL) {
        q->tail = NULL;
    }

    free(temp);
    q->size--;
    return data;
}

// 그래프 출력
void printGraph(graph* graph) {
    vertex *v = graph->vertices; // 순회 위한 포인터를 첫 정점에 연결
    int isFirstV = 1;            // 첫 번째 정점인지 체크

    printf("(");
    while (v != NULL) {
        if (!isFirstV)
            printf(", ");       // 첫 번째 정점 아니라면 쉼표 출력
        printf("%c", v->data);  // 정점의 데이터 출력

        edge *e = v->edges;     // 간선 위한 포인터
        if (e != NULL) {
            printf("(");
            int isFirstE = 1;   // 첫 번째 간선인지 체크
            while (e != NULL) {
                if (!isFirstE)
                    printf(",");
                printf("%c", e->end->data);
                e = e->next;
                isFirstE = 0;
            }
            printf(")");
        }
        v = v->next;
        isFirstV = 0;
    }
    printf(")\n");
}

// 정점 추가
void addVertex(graph* g, int data) {
    vertex *newV = (vertex *)malloc(sizeof(vertex));
    if (newV == NULL) {
        printf("메모리 할당 실패\n");
        return;
    }

    newV->data = data;
    newV->edges = NULL;          
    newV->next = g->vertices;    // new 정점이 정점 리스트의 첫 번째가 됨

    g->vertices = newV;          // 정점 리스트에 새 정점 추가
    g->numVertices++;
}

// 간선 추가
void addEdge(graph *g, int start, int end) {
    if (start == end) {
        printf("Error\n");
        return;
    }

    vertex *startV = NULL;
    vertex *endV = NULL;
    vertex *current = g->vertices;

    while (current != NULL) {   // 두 정점 찾기
        if (current->data == start)
            startV = current;
        if (current->data == end)
            endV = current;
        if (startV != NULL && endV != NULL)
            break;
        current = current->next;
    }

    if (startV == NULL || endV == NULL) {
        printf("찾을 수 없습니다.\n");
        return;
    }
    // 간선 생성, 연결
    edge *new1 = (edge *)malloc(sizeof(edge));
    edge *new2 = (edge *)malloc(sizeof(edge));
    if (new1 == NULL || new2 == NULL) {
        printf("Error\n");
        return;
    }

    new1->start = startV;
    new1->end = endV;
    new1->next = startV->edges;
    startV->edges = new1;

    new2->start = endV;
    new2->end = startV;
    new2->next = endV->edges;
    endV->edges = new2;

    g->numEdges++;
}

// 큐 사용한 너비 우선 탐색
void bfs(graph *g, int start) {
    if (g->numVertices == 0) {
        printf("빈 그래프입니다.\n");
        return;
    }

    vertex *v = g->vertices;    // 정점의 방문 상태 초기화
    while (v != NULL) {
        v->visited = false;
        v = v->next;
    }

    queue *q = create();        // 큐 생성
    vertex *startV = NULL;

    v = g->vertices;            // 시작 정점 찾기
    while (v != NULL) {
        if (v->data == start) {
            startV = v;
            break;
        }
        v = v->next;
    }

    if (startV == NULL) {
        printf("존재하지 않는 정점\n");
        return;
    }

    enqueue(q, startV->data);   // 시작 정점 큐에 추가
    startV->visited = true;

    while (!isEmptyQ(q)) {      // bfs 실행
        int currentData = dequeue(q);
        vertex *currentV = g->vertices;

        // 현재 정점 찾기
        while (currentV != NULL && currentV->data != currentData)
            currentV = currentV->next;

        if (currentV == NULL)
            continue;

        printf("%c ", currentV->data);

        // 인접 정점 탐색
        edge *e = currentV->edges;
        while (e != NULL) {
            if (!e->end->visited) {
                enqueue(q, e->end->data);
                e->end->visited = true;
            }
            e = e->next;
        }
    }
    printf("\n");
}

int main() {
    graph *myGraph = (graph *)malloc(sizeof(graph));
    myGraph->numVertices = 0;
    myGraph->numEdges = 0;
    myGraph->vertices = NULL;

    addVertex(myGraph, 'P');
    addVertex(myGraph, 'Q');
    addVertex(myGraph, 'R');
    addVertex(myGraph, 'A');
    addVertex(myGraph, 'B');
    addVertex(myGraph, 'C');

    printf("정점 추가 완료\n");
    printGraph(myGraph);
    printf("\n");

    addEdge(myGraph, 'P', 'Q');
    addEdge(myGraph, 'P', 'R');
    addEdge(myGraph, 'Q', 'A');
    addEdge(myGraph, 'Q', 'B');
    addEdge(myGraph, 'R', 'C');

    printf("간선 추가 완료\n");
    printGraph(myGraph);
    printf("\n");

    printf("BFS:\n");
    bfs(myGraph, 'Q');

    return 0;
}