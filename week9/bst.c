#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

// 노드 구조체
typedef struct node {
    int data;
    struct node *left;
    struct node *right;
} node;

// 트리 구조체
typedef struct tree {
    node *root;
    int count;
} t;

// 새 노드를 생성하고 루트로 만드는 함수
void create(t* tree, int data) {
    node *newNode = (node *)malloc(sizeof(node));
    tree->root = newNode;
    tree->root->left = NULL;
    tree->root->right = NULL;
    tree->root->data = data;
    tree->count = 0;
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

// 자식 노드 추가
node* insert_node(t* tree, node* root, int data) {
    if (root == NULL) {
        node *newNode = createNode(data);
        if (tree->root == NULL)
            tree->root = newNode;
        return newNode;
    }
    if (data < root->data)
        root->left = insert_node(tree, root->left, data);
    else
        root->right = insert_node(tree, root->right, data);
    return root;
}

// 트리 출력
void print(node* root) {
    if (root == NULL) {
        //printf("빈 트리입니다.\n");
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

// 노드 개수 출력
void count_node(t* tree) {
    printf("%d\n", tree->count);
}

// 트리 비우기
void clear(node* root) {
    if (root == NULL)
        return;

    clear(root->left);
    clear(root->right);

    free(root);
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

// 트리의 높이 출력
int height(node* root) {
    if (root == NULL)
        return -1;

    int left_height = height(root->left);
    int right_height = height(root->right);

    return (left_height > right_height) ? left_height + 1 : right_height + 1;
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

// 후계자 반환
node* find_successor(node* root) {
    if (root == NULL)
        return NULL;
    
    root = root->right; 
    if (root == NULL) return NULL; 
    while (root->left != NULL) 
        root = root->left;


    return root;
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

// 노드 탐색 경로 출력
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

// 노드 삭제
void delete_node(t* tree, node* target) {
    if (tree == NULL || tree->root == NULL || target == NULL) {
        printf("빈 트리이거나 삭제할 노드가 존재하지 않습니다.\n");
        return;
    }

    node *parent = get_parent(tree->root, target->data);
    node *delete = target;
    bool isLeftChild = (parent && parent->left == target);

    // 두 자식이 모두 있는 경우
    if (target->left != NULL && target->right != NULL) {
        // 후계자 찾기
        node *successor = find_successor(target);
        int successorData = successor->data;  
        delete_node(tree, successor);        
        target->data = successorData;        
        return;
    }

    // 한 자식 또는 자식이 없는 경우
    node *subtree = (target->left != NULL) ? target->left : target->right;
    
    if (parent == NULL) { 
        tree->root = subtree;
    } else {
        if (isLeftChild) {
            parent->left = subtree;
        } else {
            parent->right = subtree;
        }
    }

    free(delete);
    tree->count--;
}


// 창작 기능
// 1. 트리 노드의 합 구하기
int sum_tree(node* root) {
    if (root == NULL)
        return 0;

    return root->data + sum_tree(root->left) + sum_tree(root->right);
}

// 2. 트리 평균 구하기
double average_tree(t* tree, node* root) {
    if (root == NULL)
        return 0;

    int sum = sum_tree(root);
    return (double)sum / tree->count;
}

// 3. 모든 값 1 증가
void increase_tree(node* root) {
    if (root == NULL)
        return;

    root->data++;

    increase_tree(root->left);
    increase_tree(root->right);
}

int main() {
    int exit_loop = 0;

    t *myTree = (t *)malloc(sizeof(t));
    myTree->root = NULL;
    myTree->count = 0;

    printf("노드 추가:\t\t+\n");
    printf("노드 삭제:\t\t-\n");
    printf("전위 순회:\t\tI\n");
    printf("right root left 순회:\tR\n");
    printf("최솟값 출력:\t\tN\n");
    printf("최댓값 출력:\t\tX\n");
    printf("노드 찾기:\t\tF요소\n");
    printf("트리 높이 출력:\t\tH\n");
    printf("오른쪽 자식 출력:\tG(요소)\n");
    printf("왼쪽 자식 출력:\t\tL(요소)\n");
    printf("노드 개수 출력:\t\t#\n");
    printf("트리 노드의 합 구하기:\tS\n");
    printf("트리 노드의 평균 구하기:A\n");
    printf("모든 노드 값 1 증가:\tO\n");
    printf("트리 출력:\t\tP\n");
    printf("트리 비우기:\t\tC\n");
    printf("종료:\t\t\tQ\n");

    while (!exit_loop) {
        char input[30] = {0};

        printf("명령어를 입력하세요: ");
        fgets(input, sizeof(input), stdin);
        input[strlen(input) - 1] = '\0';
        int inputLength = strlen(input);
        int data, min, max, tree_height, sum;
        double avg;
        node *parentNode = NULL;
        node *current = NULL;

        for (int i = 0; i < inputLength; i++) {
            switch(input[i]) {
                case '+':
                    data = atoi(&input[i + 1]);
                    if (myTree->root == NULL)
                        create(myTree, data);
                    else 
                        insert_node(myTree, myTree->root, data);
                    myTree->count++;
                    i += 4;
                    break;
                case '-':
                    data = atoi(&input[i + 1]);
                    current = get_current(myTree->root, data);
                    delete_node(myTree, current);
                    i += 4;
                    break;
                case '#':
                    count_node(myTree);
                    break;
                case 'P':
                    printf("(");
                    print(myTree->root);
                    printf(")\n");
                    break;
                case 'I':
                    inorder_traversal(myTree->root);
                    printf("\n");
                    break;
                case 'R':
                    right_root_left_traversal(myTree->root);
                    printf("\n");
                    break;
                case 'N':
                    min = get_min(myTree->root);
                    printf("%d\n", min);
                    break;
                case 'X':
                    max = get_max(myTree->root);
                    printf("%d\n", max);
                    break;
                case 'H':
                    tree_height = height(myTree->root);
                    printf("%d\n", tree_height);
                    break;
                case 'L':
                    data = atoi(&input[i + 2]);
                    parentNode = get_current(myTree->root, data);
                    get_left_child(parentNode);
                    i += 6;
                    break;
                case 'G':
                    data = atoi(&input[i + 2]);
                    parentNode = get_current(myTree->root, data);
                    get_right_child(parentNode);
                    i += 6;
                    break;
                case 'F':
                    data = atoi(&input[i + 1]);
                    if (is_member(myTree->root, data))
                        find_node(myTree->root, data);
                    else
                        printf("Error\n");
                    i += 4;
                    break;
                case 'S':
                    sum = sum_tree(myTree->root);
                    printf("%d\n", sum);
                    break;
                case 'A':
                    avg = average_tree(myTree, myTree->root);
                    printf("%.2lf\n", avg);
                    break;
                case 'O':
                    increase_tree(myTree->root);
                    break;
                case 'C':
                    clear(myTree->root);
                    myTree->count = 0;
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