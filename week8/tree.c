#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

// 노드 구조체
typedef struct node {
    char data;
    struct node *left;
    struct node *right;
    int level;
} node;

// 트리 구조체
typedef struct tree {
    node *root;
    int count;  // 노드 수
} t;

// 새 노드를 생성하고 루트로 만들기
void create(t* tree, char data) {
    node *newNode = (node *)malloc(sizeof(node));
    tree->root = newNode;
    tree->root->left = NULL;
    tree->root->right = NULL;
    tree->root->data = data;
    tree->root->level = 0;
    tree->count = 1;
}

// 자식 노드 추가
void insertChild(t* tree, node* parentNode, char data, bool isBT) {
    node *temp = parentNode->left;

    node *newNode = (node *)malloc(sizeof(node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->level = parentNode->level + 1;

    // 이진 트리인 경우
    if (isBT) {
        if (parentNode->left == NULL)
            parentNode->left = newNode;
        else if (parentNode->right == NULL)
            parentNode->right = newNode;
        else {
            printf("노드 추가 불가\n");
            return;
        }
    }

    // 이진 트리가 아닌 경우
    else {
        // 현재 노드의 첫 번째 자식 노드 없으면 왼쪽에 추가
        if (parentNode->left == NULL)
            parentNode->left = newNode;
        else if (temp->right == NULL)
            temp->right = newNode;
        else {  // 일반 트리일때는 왼쪽 자식의 right가 형제 노드
            while (temp->right != NULL)
                temp = temp->right;
            temp->right = newNode;
        }
    }
    tree->count++;
}

// 해당 데이터를 가진 노드를 찾기 (해당 노드를 반환)
node* search(node* parentNode, char data) {
    if (parentNode == NULL)
        return NULL;
    else if (parentNode->data == data)
        return parentNode;

    node *newNode = search(parentNode->left, data);

    if (newNode != NULL)
        return newNode;

    newNode = search(parentNode->right, data);
    if (newNode != NULL)
        return newNode;

    return NULL;
}

// 부모 노드 반환 
node* get_parent(node* currentNode, char data) {
    if (currentNode == NULL)
        return NULL;
    if (currentNode->left == NULL)   // 
        return NULL;

    node *child = currentNode->left; // left child

    if (child->data == data)        // left child이 찾고자 하는 데이터 가진다면 부모 노드 반환
        return currentNode;          

    node *newNode = get_parent(child, data);    // 재귀적으로 left child 통해 함수 호출
    if (newNode != NULL)
        return newNode;

    while (child->right != NULL) {              // left child의 right child들 순회하면서 데이터 찾음
        if (child->right->data == data)
            return currentNode;
        node *newNode2 = get_parent(child->right, data);
        if (newNode2 != NULL)
            return newNode2;
        child = child->right;                   // 계속해서 right child로 이동
    }
    return NULL;
}

node* get_parent_bn(node *currentNode, char data) {
    if (currentNode == NULL)     
        return NULL;
    if (currentNode->left == NULL)
        return NULL;
    if (currentNode->left->data == data)
        return currentNode;
    if (currentNode->right != NULL) {
        if (currentNode->right->data == data)
            return currentNode;
    }

    node *newNode = get_parent_bn(currentNode->left, data);
    if (newNode != NULL)
        return newNode;
    newNode = get_parent_bn(currentNode->right, data);
    if (newNode != NULL)
        return newNode;
    return NULL;
}

// 일반 트리에서 형제 노드 출력
void get_sibling(t* tree, char data) {
    node *parent = get_parent(tree->root, data);
    node *child = parent->left;
    int count = 0;

    // 형제 노드 개수 확인
    while (child != NULL) {
        count++;
        child = child->right;
    }
    if (count <= 1) {
        printf("형제 노드가 존재하지 않습니다.\n");
        return;
    }

    child = parent->left;       // child는 부모 노드의 왼쪽 자식 가리킴
    printf("{");
    while (child != NULL) {     // 형제노드가 NULL일 때 중지
        if (child->data != data) 
            printf("%c, ", child->data);
        child = child->right;   // 오른쪽 형제노드로 이동
    }
    printf("}\n");
}

// 이진 트리에서 형제 노드 출력
void get_sibling_bn(t* tree, char data) {
    node *parent = get_parent(tree->root, data);

    if (parent->left->data == data) {
        if (parent->right != NULL)
            printf("{%c}\n", parent->right->data);
        else
            printf("형제 노드가 존재하지 않습니다.\n");
    }
    else if (parent->right->data == data)
        printf("{%c}\n", parent->left->data);
    else
        return;
}

// 노드 개수 출력
void count_node(t* tree) {
    printf("%d\n", tree->count);
}

// 트리 출력
void print(node* root) {
    if (root == NULL) {
        printf("빈 트리입니다.\n");
        return;
    }

    printf("%c", root->data);  // 현재 노드 출력

    if (root->left != NULL) {
        printf("(");
        print(root->left);
    }

    if (root->right != NULL) {
        printf(",");
        print(root->right);
    }
    else
        printf(")");
}

// 이진 트리 출력 
void printbn(node* root) {
    if (root == NULL) {
        printf("빈 트리입니다.\n");
        return;
    }

    printf("%c", root->data);
    
    if (root->left != NULL || root->right != NULL) {
        printf("(");
        printbn(root->left);
        if (root->right != NULL) {
            printf(",");
            printbn(root->right);
        }
        printf(")");
    }
}

// 노드의 차수
int degree_of_node(node* parentNode, bool isBT) {
    if (isBT) {
        if (parentNode->left != NULL && parentNode->right != NULL) // 왼쪽 자식과 오른쪽 자식이 모두 있으면
            return 2;
        else if (parentNode->left != NULL || parentNode->right != NULL) // 한 쪽 자식만 있으면
            return 1;
        else // 자식이 없으면
            return 0;
    } 
    else {
        int count = 0;
        node *childNode = parentNode->left;
        while (childNode != NULL) {
            count++;
            childNode = childNode->right;
        }
        return count;
    }
}

// 트리의 차수 
int degree_of_tree(node *root, bool isBT) {
    if (root == NULL)
        return 0;

    int maxDegree = degree_of_node(root, isBT); // 현재 노드의 차수
    node* child = root->left; // 첫 번째 자식 노드

    while (child != NULL) {
        int childDegree = degree_of_tree(child, isBT); // 자식의 차수를 재귀적으로 계산
        if (childDegree > maxDegree)
            maxDegree = childDegree;
        child = child->right; // 다음 형제 노드로 이동
    }

    return maxDegree;
}

// 자식 노드 출력 (쉼표제거하기!!)
void get_child(node* parentNode, bool isBT) {
    if (parentNode == NULL)
        return;

    int count = degree_of_node(parentNode, isBT);
    if (count == 0) {
        printf("자식 노드 존재하지 않음\n");
        return;
    }
    else {
        if (isBT) { // 이진트리인 경우
            if (parentNode->right == NULL)
                printf("{%c}", parentNode->left->data);
            else
                printf("{%c, %c}", parentNode->left->data, parentNode->right->data);
        }
        else {      // 일반트리인 경우
            node *childNode = parentNode->left; 
            printf("{");
            printf("%c, ", childNode->data);
            while (childNode->right != NULL) {   
                childNode = childNode->right;
                printf("%c, ", childNode->data);        
            }
            printf("}\n");
        }
    }
    
}

// 형제 노드 삽입 
void insert_sibling(t* tree, node* siblingNode, char data, bool isBT) {
    if (siblingNode->data == tree->root->data) {
        printf("루트 노드에는 형제 노드 추가 불가\n");
        return;
    }

    node *parentNode = get_parent(tree->root, siblingNode->data);
    node *newNode = (node *)malloc(sizeof(node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->level = siblingNode->level;

    if (isBT) {     // 이진트리인 경우
        if (parentNode->right == NULL)
            parentNode->right = newNode;
        else {
            printf("노드 추가 불가\n");
            return;
        }
    }
    else {          // 일반트리인 경우
        node *temp = parentNode->left;  // 첫번째 자식
        if (temp->right != NULL) {      // 노드가 두 개 이상일 때 맨 끝 자식노드로 이동
            while (temp->right != NULL)
                temp = temp->right;
        }
        temp->right = newNode;
    }
    tree->count++;
}

// 조상 노드 출력 
void get_ancestors(t* tree, node* currentNode) {
    node *temp = currentNode;
    node *parentNode;

    while (temp != NULL) {
        parentNode = get_parent(tree->root, temp->data); // 부모 노드 찾기
        if (parentNode != NULL)
            printf("%c ", parentNode->data); // 부모 노드 출력
        else
            break;
        temp = parentNode;
    }
    printf("\n");
}

// 자손 노드 출력 
void get_descendants(node* parentNode, int isRecursive) {
    if (parentNode == NULL) return;

    if (!isRecursive && (parentNode->left == NULL)) {
        printf("자식 노드 존재하지 않음\n");
        return;
    }

    node *currentNode = parentNode->left;

    // 처음 호출 시 첫 자식 노드의 존재 여부 검사 후 있으면 해당 노드부터 자손 출력 시작
    while (currentNode != NULL) {
        printf("%c ", currentNode->data);
        get_descendants(currentNode, 1);  // 재귀 호출이면 isRecursive=1
        currentNode = currentNode->right;
    }
    if (!isRecursive) {
        printf("\n");  // 첫 호출에서만 줄바꿈
    }
}

// 노드의 레벨
int level_of_node(t* tree, node* currentNode, bool isBT) {
    node *temp = currentNode;
    int count = 0;
    while (temp != NULL) {
        node *parentNode = (isBT) ? get_parent_bn(tree->root, temp->data) : get_parent(tree->root, temp->data);
        if (parentNode != NULL)
            count++;
        else
            break;
        temp = parentNode;
    }
    return count;
}

// 깊이 우선 탐색 
void dfs(node* currentNode, int level, int* max) {
    if (currentNode == NULL) return;

    currentNode->level = level;

    if (level > *max)
        *max = level;

    dfs(currentNode->left, level + 1, max);
    dfs(currentNode->right, level + 1, max);
}

// 트리의 레벨 
int level_of_tree(node* root) {
    if (root == NULL)
        return -1;

    int max = 0;
    dfs(root, 0, &max);

    return max;
}

// 후속자 노드 찾기
node* find_successor(node* currentNode) {
    currentNode = currentNode->right;
    while (currentNode->left != NULL)
        currentNode = currentNode->left;
    return currentNode;
}

// 노드 삭제 
void delete_node(t* tree, node* currentNode) {
    if (tree == NULL || tree->root == NULL) {
        printf("빈 트리입니다.\n");
        return;
    }

    if (currentNode == NULL) {
        printf("노드를 찾을 수 없습니다.\n");
        return;
    }

    node *parentNode = get_parent(tree->root, currentNode->data);

    // 삭제할 노드가 리프인 경우
    if (currentNode->left == NULL && currentNode->right == NULL) {
        // 루트 노드인 경우
        if (parentNode == NULL) {
            free(tree->root);
            tree->root = NULL;
            return;
        }
        else if (parentNode->left == currentNode)
            parentNode->left = NULL;
        else if (parentNode->left->right == currentNode)
            parentNode->left->right = NULL;
        free(currentNode);
    }
    // 삭제할 노드가 부모 노드인 경우
    else {
        printf("Error\n");
        return;
    }
    tree->count--;
}

// 트리 비우기
void clear(node* root) {
    if (root == NULL)
        return;

    clear(root->left);
    clear(root->right);

    free(root);
}

// 트리 합치기
void join_trees(node* newRoot, t* tree1, t* tree2) {
    newRoot->left = tree1->root;
    newRoot->right = tree2->root;
    tree1->root = NULL;
    tree2->root = NULL;
    int count = tree1->count + tree2->count;
    tree1->count = count + 1;
    tree2->count = count + 1;
}

int main() {
    int exit_loop = 0;

    t *myTree = (t *)malloc(sizeof(t));
    t *newTree = (t *)malloc(sizeof(t));

    // join_trees에서 사용할 두 번째 트리 생성

    // 일반/이진 트리 선택하기
    int isBinary;
    printf("일반 트리 선택  0 / 이진 트리 선택  1: ");
    scanf("%d", &isBinary);
    while (getchar() != '\n');
    bool isBT = (isBinary == 1) ? true : false;

    printf("요소 추가:\t+\n");
    printf("형제 노드 출력:\tS\n");
    printf("부모 요소 출력:\tP\n");
    printf("노드 개수 출력:\t#\n");
    printf("전체 트리 출력:\tT\n");
    printf("노드의 차수 출력:\tG(요소)\n");
    printf("트리의 차수 출력:\tG\n");
    printf("노드의 레벨 출력:\tL(요소)\n");
    printf("트리의 레벨 출력:\tL\n");
    printf("자식 노드 출력:\tC\n");
    printf("형제 노드 추가:\t=\n");
    printf("조상 노드 출력:\tA\n");
    printf("자손 노드 출력:\tD\n");
    printf("노드 삭제하기:\t-\n");
    printf("트리 합치기:\tJ\n");
    printf("트리 비우기:\tK\n");
    //printf("이진트리로 변환:\tB\n");
    printf("종료:\t\tQ\n");

    while (!exit_loop) {
        char input[30] = {0};

        printf("명령어를 입력하세요: ");
        fgets(input, sizeof(input), stdin);
        input[strlen(input) - 1] = '\0';
        int inputLength = strlen(input);

        for (int i = 0; i < inputLength; i++) {
            node *parentNode = NULL;
            node *siblingNode = NULL;
            node *currentNode = NULL;
            int level;
 
            switch(input[i]) {
                case '+':
                    if (input[i + 2] == '(') {
                        parentNode = search(myTree->root, input[i + 1]);    // 부모노드인 A(B,C,D)의 A를 찾음
                        if (parentNode == NULL) {   // 트리에 없는 노드 하위에 노드 추가하려는 경우
                            printf("Error\n");
                            break;
                        }
                        i += 3;
                        while (input[i] != ')') {
                            if (input[i] == ',') {
                                i++;
                                continue;
                            }
                            insertChild(myTree, parentNode, input[i], isBT);
                            i++;
                        }
                        break;
                    }
                    else { // +A만 하는 경우는 루트 생성
                        create(myTree, input[i + 1]);
                    }
                    break;
                case 'S':
                    (isBT == true) ? get_sibling_bn(myTree, input[i + 2]) : get_sibling(myTree, input[i + 2]);
                    i += 5;
                    break;
                case 'P':
                    if (isBT == true) {
                        node *parentNode = get_parent_bn(myTree->root, input[i + 2]);
                        printf("%c\n", parentNode->data);
                    }
                    else {
                        node *parentNode = get_parent(myTree->root, input[i + 2]);
                        printf("%c\n", parentNode->data);
                    }
                    i += 5;
                    break;
                case 'C':
                    parentNode = search(myTree->root, input[i + 2]);
                    get_child(parentNode, isBT);
                    i += 5;
                    break;
                case '-':
                    currentNode = search(myTree->root, input[i + 1]);
                    delete_node(myTree, currentNode);
                    i += 2;
                    break;
                case 'L':
                    if (input[i + 1] == '(') {
                        currentNode = search(myTree->root, input[i + 2]);
                        level = level_of_node(myTree, currentNode, isBT);
                        printf("%d\n", level);
                        i += 5;
                    }
                    else {
                        int level = level_of_tree(myTree->root);
                        printf("%d\n", level);
                    }
                    break;
                case '=':
                    siblingNode = search(myTree->root, input[i + 2]);
                    i += 4;
                    while (input[i] != ')') {
                        if (input[i] == ',')
                        {
                            i++;
                            continue;
                        }
                        insert_sibling(myTree, siblingNode, input[i], isBT);
                        i++;
                    }
                    break;
                case '#':
                    count_node(myTree);
                    break;
                case 'T':
                    printf("(");
                    (isBT == true) ? printbn(myTree->root) : print(myTree->root);
                    printf("\n");
                    break;
                case 'A':
                    currentNode = search(myTree->root, input[i + 2]);
                    get_ancestors(myTree, currentNode);
                    i += 5;
                    break;
                case 'D':
                    parentNode = search(myTree->root, input[i + 2]);
                    get_descendants(parentNode, 0);
                    i += 5;
                    break;
                case 'G':
                    if (input[i + 1] == '(') {
                        currentNode = search(myTree->root, input[i + 2]);
                        int degree = degree_of_node(currentNode, isBT);
                        printf("%d\n", degree);
                        i += 5;
                    }
                    else {
                        int degree = degree_of_tree(myTree->root, isBT);
                        printf("%d\n", degree);
                    }
                    break;
                case 'J':
                    create(newTree, input[i + 2]);
                    join_trees(newTree->root, myTree, newTree);
                    i += 8;
                    break;
                case 'K':
                    clear(myTree->root);
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