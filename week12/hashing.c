void delete_vertex(graph *g, int data) {
    vertex **prevV = &(g->vertices);
    vertex *v = g->vertices;

    while (v != NULL) {
        if (v->data == data) {
            edge *e = v->edges;
            while (e != NULL) {
                edge *next = e->next;
                delete_edge(g, e->end->data, data);
                free(e);
                e = next;
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


// 무방향 그래프 정점 삭제
void delete_vertex(graph *g, int data){
    vertex **prevV = &(g->vertices);
    vertex *v = g->vertices;

    while (v != NULL) {
        if (v->data == data) {
            edge *e = v->edges;
            while (e != NULL) {
                edge *next = e->next;
                delete_edge(g, e->end->data, data);
                free(e);
                e = next;
            }
            *prevV = v->next;
            free(v);
            g->numVertices--;
            return;
        }
        prevV = &(v->next);
        v = v->next;
    }

Accept suggestion 2
Suggestion 3
void delete_vertex(graph *g, int data){}

// 방향 그래프 정점 삭제
void delete_vertex(graph *g, int data) {
    vertex **prevV = &(g->vertices);
    vertex *v = g->vertices;

    while (v != NULL) {
        if (v->data == data) {
            edge *e = v->edges;
            while (e != NULL) {
                edge *next = e->next;
                delete_edge(g, e->start->data, e->end->data);
                free(e);
                e = next;
            }
            *prevV = v->next;
            free(v);
            g->numVertices--;
            return;
        }
        prevV = &(v->next);
        v = v->next;
    }

Accept suggestion 3
Suggestion 4
void delete_vertex(graph *g, int data){}

// 무방향 그래프 정점 삭제
void delete_vertex(graph *g, int data) {
    vertex **prevV = &(g->vertices);
    vertex *v = g->vertices;

    while (v != NULL) {
        if (v->data == data) {
            edge *e = v->edges;
            while (e != NULL) {
                edge *next = e->next;
                delete_edge(g, e->end->data, data);
                free(e);
                e = next;
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

// 무방향 그래프 정점 삭제
void delete_vertex(graph *g, int data) {
    vertex **prevV = &(g->vertices);
    vertex *v = g->vertices;

    while (v != NULL) {
        if (v->data == data) {
            edge *e = v->edges;
            while (e != NULL) {
                edge *next = e->next;
                delete_edge(g, e->end->data, data);
                free(e);
                e = next;
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

// 무방향 그래프 정점 삭제
void delete_vertex(graph *g, int data) {
    vertex **prevV = &(g->vertices);
    vertex *v = g->vertices;

    while (v != NULL) {
        if (v->data == data) {
            edge *e = v->edges;
            while (e != NULL) {
                edge *next = e->next;
                delete_edge(g, e->end->data, data);
                free(e);
                e = next;
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



// 하 제발..
// 간선 삭제 
void delete_edge(graph *g, int start, int end) {
    bool found = false;     // 간선 발견 여부
    vertex *v = g->vertices;

    while (v != NULL) {     // start-end 삭제
        if (v->data == start) {
            edge **prevE = &(v->edges);
            edge *e = v->edges;
            while (e != NULL) {
                if (e->end->data == end) {
                    *prevE = e->next;
                    free(e);
                    g->numEdges--;
                    found = true;
                    break;
                }
                prevE = &(e->next);
                e = e->next;
            }
        }
        v = v->next;
    }

    v = g->vertices;
    while (v != NULL) {     // end-start 삭제
        if (v->data == end) {
            edge **prevE = &(v->edges);
            edge *e = v->edges;
            while (e != NULL) {
                if (e->end->data == start) {
                    *prevE = e->next;
                    free(e);
                    g->numEdges--;
                    found = true;
                    break;
                }
                prevE = &(e->next);
                e = e->next;
            }
        }
        v = v->next;
    }

    if (!found)
        printf("ERROR!\n");
}

// 무방향 그래프 정점 삭제
void delete_vertex(graph *g, int data) {
    vertex **prevV = &(g->vertices);
    vertex *v = g->vertices;

    while (v != NULL) {
        if (v->data == data) {
            edge *e = v->edges;
            while (e != NULL) {
                edge *next = e->next;
                delete_edge(g, e->end->data, data);
                free(e);
                e = next;
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
