#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct node {
    int data;
    int bf;
    int height;
    struct node *left, *right, *parent;    // 회전 연산 효율성 위해 parent 노드 추가
} node;

typedef struct tree {
    node *root;
    int count;
} t;

// 새 노드 생성
node* createNode(int data, node* parent) {
    node *newNode = (node *)malloc(sizeof(node));
    if (newNode == NULL) {
        printf("메모리 할당 오류\n");
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->bf = 0;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->parent = parent;
    return newNode;
}

// 새 노드를 루트로 만들기
void create(t* tree, int data, node* parent) {
    node *newNode = createNode(data, parent);
    tree->root = newNode;
    newNode->height = 0;
    tree->count = 0;
}

// 노드의 height 출력 (child의 수)
void height_node(node* current) {
    if (current->left != NULL && current->right != NULL)
        printf("2\n");
    else if (current->left == NULL && current->right == NULL)
        printf("0\n");
    else
        printf("1\n");
}

// 노드의 height 반환 (child의 수)
int node_height(node* current) {
    if (current == NULL)
        return 0;

    int leftHeight = node_height(current->left);
    int rightHeight = node_height(current->right);
    // 왼쪽 서브트리 / 오른쪽 서브트리 중 더 큰 값을 반환
    return (leftHeight > rightHeight) ? leftHeight + 1 : rightHeight + 1;
}

// 최댓값 계산
int max(int a, int b) {
    return (a > b) ? a : b;
}

// balance factor 구하기
int balance_factor(node* node) {
    return node_height(node->left) - node_height(node->right);
}

// 현재 요소의 주소 반환
node* get_current(node* parentNode, char data) {
    if (parentNode == NULL)
        return NULL;
    else if (parentNode->data == data)
        return parentNode;

    node *newNode = get_current(parentNode->left, data);

    if (newNode != NULL)
        return newNode;

    newNode = get_current(parentNode->right, data);
    if (newNode != NULL)
        return newNode;

    return NULL;
}

// 부모 노드 반환
node* get_parent(node *current, char data) {
    if (current == NULL)     
        return NULL;
    if (current->left == NULL)
        return NULL;
    if (current->left->data == data)
        return current;
    if (current->right != NULL) {
        if (current->right->data == data)
            return current;
    }

    node *newNode = get_parent(current->left, data);
    if (newNode != NULL)
        return newNode;
    newNode = get_parent(current->right, data);
    if (newNode != NULL)
        return newNode;
    return NULL;
}

// RR case: left rotation
node* rotateL(node* current) {
    node *child = current->right;
    current->right = child->left;       // child의 다른 쪽 서브트리를 current 하위로 연결
    if (child->left != NULL)            // child의 다른 쪽에 서브트리가 있었다면
        child->left->parent = current;  // 서브트리의 부모요소를 현재 노드로 설정

    child->left = current;              // current 노드를 L rotate
    child->parent = current->parent;    // 새 root의 부모 요소 자리에 current의 부모였던 노드 연결
    current->parent = child;            // current의 새 부모는 child가 됨

    return child;
}

// LL case: right rotation
node* rotateR(node* current) {
    node *child = current->left;
    current->left = child->right;
    if (child->right != NULL)
        child->right->parent = current;

    child->right = current;
    child->parent = current->parent;
    current->parent = child;

    return child;
}

// LR case: left right rotation
node* rotateLR(node* node) {                // node: 균형 잃은 노드
    if (node == NULL)
        return NULL;

    node->left = rotateL(node->left);       
    return rotateR(node);                  
}

// RL case: right left rotation
node* rotateRL(node* node) {
    if (node == NULL)
        return NULL;

    node->right = rotateR(node->right);     
    return rotateL(node);                   
}

// 트리 출력
void print(node* root) {
    if (root == NULL) {
        return;
    }

    printf("%d", root->data);

    if (root->left != NULL || root->right != NULL) {
        printf("(");
        if (root->left != NULL) { 
            print(root->left);
        }
        if (root->right != NULL) {
            printf(","); 
            print(root->right);
        }
        printf(")");
    }
}

// AVL tree 조건에 맞게 세팅
node* avl(node* node) {
    int depth = balance_factor(node);
    if (depth >= 2) {
        depth = balance_factor(node->left);
        if (depth >= 1)
            node = rotateR(node);
        else
            node = rotateLR(node);
    }
    else if (depth <= -2) {
        depth = balance_factor(node->right);
        if (depth <= -1)
            node = rotateL(node);
        else
            node = rotateRL(node);
    }
    return node;
}

// 노드 삽입
node* insert_node(node* current, int data) {   // main에서 tree->root를 node 파라미터로 줌
    // 빈 트리인 경우 루트 생성
    /*if (node == NULL) {
        node *newNode = createNode(data, NULL);
        if (tree->root == NULL) {
            tree->root = newNode;
            tree->count = 1;
        }
        return newNode;
    }*/

    // 파라미터의 left/right가 null인 경우(node의 left, right 모두 null인 경우)
    if (current == NULL) {
        node* newNode = createNode(data, NULL);
        return newNode;
    }

    // bst 규칙에 따라 삽입
    if (data < current->data) {
        current->left = insert_node(current->left, data);
        current->left->parent = current;
        current = avl(current);
    }
    else if (data > current->data) {
        current->right = insert_node(current->right, data);
        current->right->parent = current;
        current = avl(current);
    }
    else
        return current;

    // 높이 업데이트
    current->height = max(node_height(current->left), node_height(current->right));

    return current;
}

// 트리의 높이 출력
int height_tree(node* root) {
    return max(node_height(root->left), node_height(root->right));
}

// 전위 순회 출력
void inorder_traversal(node* root) {
    if (root == NULL)
        return;

    inorder_traversal(root->left);

    printf("%d ", root->data);

    inorder_traversal(root->right);
}

// right_root_left 순회
void right_root_left_traversal(node* root) {
    if (root == NULL)
        return;

    right_root_left_traversal(root->right);

    printf("%d ", root->data);

    right_root_left_traversal(root->left);
}

// 노드 개수 출력
void count_node(t* tree) {
    printf("%d\n", tree->count);
}

// 왼쪽 자식 출력
void get_left_child(node* parent) {
    if (parent == NULL) {
        printf("NULL\n");
        return;
    }

    if (parent->left == NULL)
        printf("NULL\n");
    else
        printf("%d\n", parent->left->data);
}

// 오른쪽 자식 출력
void get_right_child(node* parent) {
    if (parent == NULL) {
        printf("NULL\n");
        return;
    }

    if (parent->right == NULL)
        printf("NULL\n");
    else
        printf("%d\n", parent->right->data);
}

// 멤버인지 여부를 bool 값으로 반환
bool is_member(node* root, int data) {
    if (root == NULL)
        return false;
    node *current = root;

    while (current != NULL) {
        if (data == current->data)
            return true;
        else if (data < current->data) 
            current = current->left;
        else 
            current = current->right;
    }
    return false;
}

// 노드 탐색 경로 출력 ----- 아래의 숫자 2는 왜뜨는겨??
void find_node(node* root, int data) {
    node *current = root;
    printf("Root > ");

    while (current != NULL) {
        if (data == current->data) {
            printf("\n");
            return;
        }
        else if (data < current->data) {
            printf("Left");
            current = current->left;
        }
        else {
            printf("Right");
            current = current->right;
        }
        printf(" > ");
    }
}

// 트리 비우기
void clear(node* root) {
    if (root == NULL)
        return;

    clear(root->left);
    clear(root->right);

    free(root);
}

// 최솟값 출력
int get_min(node* root) {
    if (root == NULL)
        return -1;
    
    while (root->left != NULL)
        root = root->left;

    return root->data;
}

// 최댓값 출력
int get_max(node* root) {
    if (root == NULL)
        return -1;

    while (root->right != NULL)
        root = root->right;

    return root->data;
}

// 최대 노드 반환
node* get_max_node(node* current) {
    while (current && current->right != NULL) {
        current = current->right;
    }
    return current;
}

// 노드 삭제
node* delete_node(node* current, int data) {
    if (current == NULL) {
        return NULL;
    }

    if (data < current->data) {
        current->left = delete_node(current->left, data);
    } else if (data > current->data) {
        current->right = delete_node(current->right, data);
    } else {
        if (current->left == NULL) {
            node* temp = current->right;
            free(current);
            return temp;
        } else if (current->right == NULL) {
            node* temp = current->left;
            free(current);
            return temp;
        }

        // child 2
        node* maxNode = get_max_node(current->left);
        current->data = maxNode->data;
        current->left = delete_node(current->left, maxNode->data);
    }

    return avl(current);
}

int main() {
    int exit_loop = 0;

    t *Tree = (t *)malloc(sizeof(t));
    Tree->root = NULL;
    Tree->count = 0;

    printf("노드 추가:\t\t+\n");
    printf("노드 삭제:\t\t-\n");
    printf("balance factor 출력:\tB노드\n");
    printf("전위 순회:\t\tI\n");
    printf("right root left 순회:\tR\n");
    printf("최솟값 출력:\t\tN\n");
    printf("최댓값 출력:\t\tX\n");
    printf("노드 찾기:\t\tF요소\n");
    printf("트리 높이 출력:\t\tT\n");
    printf("노드 높이 출력:\t\tH요소\n");
    printf("오른쪽 자식 출력:\tG요소\n");
    printf("왼쪽 자식 출력:\t\tL요소\n");
    printf("노드 개수 출력:\t\t#\n");
    printf("트리 출력:\t\tP\n");
    printf("트리 비우기:\t\tC\n");
    printf("종료:\t\t\tQ\n");

    while (!exit_loop) {
        char input[30] = {0};

        printf("명령어를 입력하세요: ");
        fgets(input, sizeof(input), stdin);
        input[strlen(input) - 1] = '\0';
        int inputLength = strlen(input);

        int data, min, max, tree_height, node_height, bf;
        node *parent = NULL;
        node *current = NULL;

        for (int i = 0; i < inputLength; i++) {
            switch(input[i]) {
                case '+':
                    data = atoi(&input[i + 1]);
                    if (Tree->root == NULL) {
                        create(Tree, data, NULL);
                        Tree->root->left = NULL;
                        Tree->root->right = NULL;
                    }
                    else {
                        Tree->root = insert_node(Tree->root, data);
                    }
                    Tree->count++;
                    i += 4;
                    break;
                case '-':  
                    data = atoi(&input[i + 1]);
                    //current = get_current(Tree->root, data);
                    if (is_member(Tree->root, data))
                        Tree->root = delete_node(Tree->root, data);
                    else
                        printf("Error\n");
                    break;
                case 'P':
                    printf("(");
                    print(Tree->root);
                    printf(")\n");
                    break;
                case 'B': 
                    data = atoi(&input[i + 1]);
                    current = get_current(Tree->root, data);
                    bf = balance_factor(current);
                    printf("%d\n", bf);
                    i += 2;
                    break;
                case 'I':
                    inorder_traversal(Tree->root);
                    printf("\n");
                    break;
                case 'R':
                    right_root_left_traversal(Tree->root);
                    printf("\n");
                    break;
                case 'N':
                    min = get_min(Tree->root);
                    printf("%d\n", min);
                    break;
                case 'X':
                    max = get_max(Tree->root);
                    printf("%d\n", max);
                    break;
                case 'F':
                    data = atoi(&input[i + 1]);
                    if (is_member(Tree->root, data))
                        find_node(Tree->root, data);
                    else
                        printf("Error\n");
                    i += 4;
                    break;
                case 'T':
                    tree_height = height_tree(Tree->root);
                    printf("%d\n", tree_height);
                    break;
                case 'H':   
                    data = atoi(&input[i + 1]);
                    current = get_current(Tree->root, data);
                    height_node(current);
                    i += 2;
                    break;
                case 'G':
                    data = atoi(&input[i + 1]);
                    parent = get_current(Tree->root, data);
                    get_right_child(parent);
                    i += 5;
                    break;
                case 'L':
                    data = atoi(&input[i + 1]);
                    parent = get_current(Tree->root, data);
                    get_left_child(parent);
                    i += 5;
                    break;
                case '#':
                    count_node(Tree);
                    break;
                case 'C':
                    clear(Tree->root);
                    break;
                case 'Q':
                case 'q':
                    exit_loop = 1;
                    break;
                default:
                    break;
            }
        }
    }
    return 0;
}