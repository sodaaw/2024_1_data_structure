#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// 간선 구조체
typedef struct Edge {
    struct Edge *next;    // 다음 간선 위한 포인터
    struct Vertex *start;
    struct Vertex *end;
} edge;

// 정점 구조체
typedef struct Vertex {
    int data;
    bool visited;           // 방문 상태 저장 
    struct Vertex *next;    // 다음 정점 위한 포인터
    struct Edge *edges;     // 현재 정점에서 출발하는 간선 리스트
} vertex;

// 그래프 구조체
typedef struct Graph {
    int numVertices;       // 정점 수
    int numEdges;          // 간선 수
    vertex *vertices;      // 첫 번째 정점을 가리키는 포인터
} graph;

// 출력 위한 스택 구조체
typedef struct Stack{
    char *data;             // 출력할 데이터 저장하는 배열
    int top;                // 현재 위치
    int capacity;           // 용량
} stack;

// 스택 초기화
void initStack(stack *s, int capacity) {
    s->data = (char *)malloc(capacity * sizeof(char));
    s->top = -1;
    s->capacity = capacity;
}

// 스택에 요소 추가
void push(stack *s, char item) {
    if (s->top < s->capacity - 1) {
        s->data[++s->top] = item;
    }
}

// 스택에서 요소 제거
char pop(stack *s) {
    if (s->top >= 0) {
        return s->data[s->top--];
    }
    return '\0';
}

// 스택이 비어있는지 검사
bool isEmpty(stack *s) {
    return s->top == -1;
}

// 그래프 생성 및 초기화
void create(graph* graph) {
    graph->numVertices = 0;
    graph->numEdges = 0;
    graph->vertices = NULL;     // 정점 리스트 시작 null로 초기화
}

// 그래프 출력
void print(graph *g) {
    stack s;
    initStack(&s, 100);  // 100은 예제로 선택한 스택의 최대 크기

    vertex *v = g->vertices;
    while (v != NULL) {
        // 여기서 엣지 존재 여부 확인
        bool hasEdges = v->edges != NULL;
        
        if (hasEdges) {
            push(&s, ')');  // 정점의 정보 끝에 닫는 괄호 추가
        }

        edge *e = v->edges;
        if (e != NULL) {
            while (e != NULL) {
                push(&s, e->end->data);
                if (e->next != NULL) {
                    push(&s, ',');
                }
                e = e->next;
            }
        }
        
        if (hasEdges) {
            push(&s, '(');  // 간선 정보 시작에 여는 괄호 추가
        }
        
        push(&s, v->data);
        if (v->next != NULL) {
            push(&s, ',');
        }
        v = v->next;
    }

    // 전체 출력의 시작 괄호 추가
    push(&s, '(');  

    // 스택에서 모든 요소를 꺼내 출력
    while (!isEmpty(&s)) {
        printf("%c", pop(&s));
    }

    free(s.data);  // 사용한 메모리 해제
}

// 정점 추가
void insert_vertex(graph* g, int data) {
    vertex *newV = (vertex *)malloc(sizeof(vertex));
    if (newV == NULL) {
        printf("메모리 할당 실패\n");
        return;
    }

    newV->data = data;
    newV->edges = NULL;          // 아직 연결된 간선 없음
    newV->next = g->vertices;    // new 정점이 정점 리스트의 첫 번째가 됨

    g->vertices = newV;          // 정점 리스트에 새 정점 추가
    g->numVertices++;
}

// 간선 추가
void add_edge(graph *g, int start, int end) {
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

// 그래프가 비어있는지 확인
bool is_empty(graph* g) {
    if (g->vertices == NULL)
        return 1;
    else
        return 0;
}

// 인접 정점 출력
void adjacent(graph* g, int data) {
    vertex *v = g->vertices;
    while (v != NULL) {
        if (v->data == data) {
            edge *e = v->edges;
            if (e == NULL)
                printf("인접한 정점 없음\n");
            else {
                printf("{");
                while (e != NULL) {
                    printf("%c", e->end->data);
                    if (e->next != NULL) {
                        printf(", "); 
                    }
                    e = e->next;
                }
                printf("}\n");
            }
            return;
        }
        v = v->next;
    }
}

// 정점의 차수(간선 수) 출력
void degree_of_vertex(graph *g, int data) {
    vertex *v = g->vertices;
    int count = 0;

    while (v != NULL) { // 정점 탐색
        if (v->data == data) {
            edge *e = v->edges;
            while (e != NULL) { // 간선 카운트
                count++;
                e = e->next;
            }
        }
        v = v->next;
    }
    printf("%d\n", count);
}

// 정점 값 변경
void rename_vertex(graph *g, int data, int newData) {
    vertex *v = g->vertices;
    while (v != NULL) {
        if (v->data == data) {
            v->data = newData;
            break;
        }
        v = v->next;
    }
}

// 정점 개수 출력
void num_of_vertex(graph *g) {
    printf("%d\n", g->numVertices);
}

// 간선 개수 출력
void num_of_edge(graph *g) {
    printf("%d\n", g->numEdges/2);
}

// 경로 존재 여부 판단 위한 깊이 우선 탐색
bool dfs(vertex *v, int end) {
    if (v->data == end)     // 목표 정점 찾은 경우
        return true;

    v->visited = true;      // 현재 정점 방문했음을 표시

    edge *e = v->edges;
    while (e != NULL) {
        vertex *adjV = e->end;  // 인접 정점 포인터 (간선의 끝에는 정점이 있음)
        if (!adjV->visited && dfs(adjV, end))   // 방문되지 않은 정점이라면 다시 dfs
            return true;        // 경로 존재함
        e = e->next;
    }
    return false;
}

// 경로 존재 여부 출력
bool path_exist(graph *g, int start, int end) {
    vertex *v = g->vertices;
    while (v != NULL) {     // 모든 정점의 방문 상태 초기화
        v->visited = false;
        v = v->next;
    }

    vertex *startV = g->vertices;
    while (startV != NULL && startV->data != start) // 시작 정점 찾기
        startV = startV->next;

    if (startV == NULL)
        return false;

    return dfs(startV, end);    // 현재 정점에서 end로 가는 경로 있는지 dfs
}

void delete_edge(graph *g, char startData, char endData) {
    vertex *startVertex = g->vertices;
    // 이동하면서 시작 정점을 찾습니다.
    while (startVertex != NULL && startVertex->data != startData) {
        startVertex = startVertex->next;
    }

    // 시작 정점을 찾지 못한 경우, 정점이 존재하지 않음
    if (startVertex == NULL) {
        printf("ERROR!\n");
        return;
    }

    edge **prevEdge = &(startVertex->edges);
    edge *currentEdge = startVertex->edges;
    // 간선을 찾아 삭제합니다.
    while (currentEdge != NULL) {
        if (currentEdge->end->data == endData) {
            *prevEdge = currentEdge->next;
            free(currentEdge); // 메모리 해제
            return;
        }
        prevEdge = &currentEdge->next;
        currentEdge = currentEdge->next;
    }

    // 간선을 찾지 못했을 때의 에러 메시지 출력
    printf("ERROR!\n");
}

void delete_vertex(graph *g, char data) {
    vertex **prevV = &(g->vertices);
    vertex *v = g->vertices;

    while (v != NULL) {
        if (v->data == data) {
            edge *e = v->edges;
            while (e != NULL) {
                delete_edge(g, e->end->data, data);  // Delete the reciprocal edges first
                e = e->next;
            }
            *prevV = v->next;
            free(v);
            g->numVertices--;
            return;
        }
        prevV = &(v->next);
        v = v->next;
    }
}


// 모든 정점과 연결된 정점인지 확인
bool is_connected(graph *g, int data) {
    vertex *target = NULL;
    vertex *current = g->vertices;
    int connections = 0;

    while (current != NULL) {
        if (current->data == data) {
            target = current;
        }
        current = current->next;
    }

    if (target == NULL) return false;

    // 연결된 모든 정점 확인
    edge *e = target->edges;
    while (e != NULL) {
        connections++;  
        e = e->next;
    }

    // 자기 자신 제외
    return connections == (g->numVertices - 1);
}

// 그래프 비우기
void clear(graph *g) {
    vertex *currentV = g->vertices;
    while (currentV != NULL) {
        edge *currentE = currentV->edges;
        while (currentE != NULL) {  // 간선 삭제
            edge *tempE = currentE;
            currentE = currentE->next;
            free(tempE);
        }

        vertex *tempV = currentV;   // 정점 삭제
        currentV = currentV->next;
        free(tempV);
    }

    g->vertices = NULL;
    g->numEdges = 0;
    g->numVertices = 0;
}

int main(){
    int exit_loop = 0;

    graph *myGraph = (graph *)malloc(sizeof(graph));

    printf("그래프 생성:\t\tG\n");
    printf("정점 추가:\t\t+\n");
    printf("정점 삭제:\t\t-\n");
    printf("간선 추가:\t\tE(정점,정점)\n");
    printf("간선 삭제:\t\tD(정점,정점)\n");
    printf("정점의 차수:\t\tV(정점)\n");
    printf("연결된 정점?\t\t정점\n");
    printf("그래프 비었음?\t\tN\n");
    printf("경로 존재?\t\tP(정점,정점)\n");
    printf("정점 개수:\t\tX\n");
    printf("간선 개수:\t\tH\n");
    printf("정점 변경:\t\tR(정점,새 정점)\n");
    printf("인접한 정점:\t\tA(정점)\n");
    printf("그래프 출력:\t\tL\n");
    printf("그래프 비우기:\t\tK\n");
    printf("종료:\t\t\tQ\n");

    while (!exit_loop) {
        char input[30] = {0};

        printf("명령어를 입력하세요: ");
        fgets(input, sizeof(input), stdin);
        input[strlen(input) - 1] = '\0';
        int inputLength = strlen(input);

        for (int i = 0; i < inputLength; i++) {
            switch(input[i]) {
            case 'G':   // 그래프 생성 및 초기화
                create(myGraph);
                break;
            case '+':   // 노드 추가
                insert_vertex(myGraph, input[i + 1]);
                i += 2;
                break;
            case '-':
                delete_vertex(myGraph, input[i + 1]);
                i += 2;
                break;
            case 'E': // 간선 추가
                add_edge(myGraph, input[i + 2], input[i + 4]);
                i += 6;
                break;
            case 'L': // 그래프 출력
                print(myGraph);
                printf(")\n");
                break;
            case 'N':
                if (is_empty(myGraph))
                    printf("True\n");
                else
                    printf("False\n");
                break;
            case 'X':
                num_of_vertex(myGraph);
                break;
            case 'H':
                num_of_edge(myGraph);
                break;
            case 'A':
                adjacent(myGraph, input[i + 2]);
                i += 4;
                break;
            case 'V':
                degree_of_vertex(myGraph, input[i + 2]);
                i += 4;
                break;
            case 'R':
                rename_vertex(myGraph, input[i + 2], input[i + 4]);
                i += 6;
                break;
            case 'P':
                if (path_exist(myGraph, input[i + 2], input[i + 4]))
                    printf("True\n");
                else 
                    printf("False\n");
                i += 6;
                break;
            case 'D':
                delete_edge(myGraph, input[i + 2], input[i + 4]);
                i += 6;
                break;
            case 'K':
                clear(myGraph);
                break;
            case 'Q': // 종료
            case 'q':
                exit_loop = 1;
                break;
            default:
                if (is_connected(myGraph, input[i]))
                    printf("True\n");
                else
                    printf("False\n");
                break;
            }
            //print(myGraph);
            //printf(")\n");
        }
    }
    return 0;
}