#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node *left;
    struct node *right;
} node;

typedef struct tree {
    node *root;
} tree;

// max heap에 요소 삽입
void insertHeap(int *heap, int size, int data) {
    heap[size] = data;      // 힙의 마지막에 삽입
    int current = size;     // current는 맨 끝
    while (current > 0) {   // 부모 노드와 비교해서 필요한 경우 자리 교환
        int parent = (current - 1) / 2;
        if (heap[parent] < heap[current]) {
            int temp = heap[current];
            heap[current] = heap[parent];
            heap[parent] = temp;
            current = parent;
        } else
            break;
    }
}

// 노드 생성 함수
node* createNode(int data) {
    node *newNode = (node *)malloc(sizeof(node));
    if (newNode == NULL) {
        printf("메모리 할당 오류\n");
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// bst에 요소 삽입
node* insertBST(tree* tree, node* root, int data) {
    if (root == NULL) {
        node *newNode = createNode(data);
        if (tree->root == NULL)
            tree->root = newNode;
        return newNode;
    }
    if (data < root->data)
        root->left = insertBST(tree, root->left, data);
    else
        root->right = insertBST(tree, root->right, data);
    return root;
}

// bst 출력
void printBST(node* root) {
    if (root == NULL) {
        return;
    }

    printf("%d", root->data);

    if (root->left != NULL || root->right != NULL) {
        printf("(");
        if (root->left != NULL) { 
            printBST(root->left);
        }
        if (root->right != NULL) {
            printf(","); 
            printBST(root->right);
        }
        printf(")");
    }
}

int main() {
    tree *t = (tree *)malloc(sizeof(tree));
    int heap[100];
    int elementNum;
    printf("요소의 개수를 입력하세요: ");
    scanf("%d", &elementNum);

    // max heap 생성
    for (int i = 0; i < elementNum; i++) {
        int data;
        printf("%d번째 요소를 입력하세요: ", i + 1);
        scanf("%d", &data);
        insertHeap(heap, i, data);
    }
    printf("\n");

    printf("max heap 출력: ");
    for (int i = 0; i < elementNum; i++) {
        printf("%d ", heap[i]);
    }
    printf("\n");

    // bst로 변환
    for (int i = 0; i < elementNum; i++)
        t->root = insertBST(t, t->root, heap[i]);

    printf("BST 출력: ");
    printBST(t->root);
    printf("\n");

    return 0;
}