#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct MenuItem {
    char name[50];
    int price;
    int is_seasonal;        // 제철 여부
    int is_market_price;    // 싯가 여부 
    struct MenuItem *next;  // 다음 회에 연결
} MenuItem;

MenuItem *head = NULL;
MenuItem *tail = NULL;

// 메뉴에 새로운 회 추가
void addMenuItem(char *name, int price, int is_seasonal, int is_market_price) {
    MenuItem *newItem = (MenuItem *)malloc(sizeof(MenuItem));
    if (newItem == NULL) {
        printf("메모리 할당 에러\n");
        return;
    }
    strcpy(newItem->name, name);
    newItem->price = price;
    newItem->is_seasonal = is_seasonal;
    newItem->is_market_price = is_market_price;
    newItem->next = NULL;

    if (head == NULL) {
        head = newItem;
        tail = newItem;
    } else {
        tail->next = newItem;
        tail = newItem;
    }
}

// 회 삭제
void deleteMenuItem(char *name) {
    MenuItem *temp = head, *prev = NULL;
    while (temp != NULL && strcmp(temp->name, name) != 0) {
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL) return;
    if (prev == NULL) head = temp->next;
    else prev->next = temp->next;
    free(temp);
}

// 회 이름 수정
void updateMenuItemName(char *currentName, char *newName) {
    MenuItem *temp = head;
    while (temp != NULL) {
        if (strcmp(temp->name, currentName) == 0) {
            strcpy(temp->name, newName);
            return;
        }
        temp = temp->next;
    }
}

// 회 가격 수정
void updateMenuItemPrice(char *name, int newPrice) {
    MenuItem *temp = head;
    while (temp != NULL) {
        if (strcmp(temp->name, name) == 0) {
            temp->price = newPrice;
            return;
        }
        temp = temp->next;
    }
}

// 제철 여부 수정
void updateIsSeasonal(char *name, int newIsSeasonal) {
    MenuItem *temp = head;
    while (temp != NULL) {
        if (strcmp(temp->name, name) == 0) {
            temp->is_seasonal = newIsSeasonal;
            return;
        }
        temp = temp->next;
    }
}

// 싯가 여부 수정
void updateIsMarketPrice(char *name, int newIsMarketPrice) {
    MenuItem *temp = head;
    while (temp != NULL) {
        if (strcmp(temp->name, name) == 0) {
            temp->is_market_price = newIsMarketPrice;
            return;
        }
        temp = temp->next;
    }
}

// 메뉴 출력
void printMenu() {
    MenuItem *temp = head;
    while (temp != NULL) {
        printf("이름: %s, 가격: %d원, 제철: %s, 싯가: %s\n",
               temp->name, temp->price, 
               temp->is_seasonal ? "O" : "X",
               temp->is_market_price ? "O" : "X");
        temp = temp->next;
    }
}

int main() {
    int choice, price, is_seasonal, is_market_price;
    char name[50];

    while (1) {
        printf("\n메뉴 관리 프로그램\n");
        printf("1. 회 추가\n");
        printf("2. 회 삭제\n");
        printf("3. 회 이름 수정\n");
        printf("4. 회 가격 수정\n");
        printf("5. 제철 여부 수정\n");
        printf("6. 싯가 여부 수정\n");
        printf("7. 전체 메뉴 출력\n");
        printf("8. 종료\n");
        printf("선택: ");
        scanf("%d", &choice);

        printf("\n");

        // switch문 사용해 사용자의 입력 처리
        switch (choice) {
            case 1:
                printf("회 이름: ");
                scanf("%s", name);
                printf("가격: ");
                scanf("%d", &price);
                printf("제철 여부 (0: 아니오, 1: 예): ");
                scanf("%d", &is_seasonal);
                printf("싯가 여부 (0: 아니오, 1: 예): ");
                scanf("%d", &is_market_price);
                addMenuItem(name, price, is_seasonal, is_market_price);
                break;
            case 2:
                printf("삭제할 회 이름: ");
                scanf("%s", name);
                deleteMenuItem(name);
                break;
            case 3: 
                {
                    char newName[50];
                    printf("현재 회 이름: ");
                    scanf("%s", name);
                    printf("새 회 이름: ");
                    scanf("%s", newName);
                    updateMenuItemName(name, newName);
                }
                break;
            case 4:
                printf("회 이름: ");
                scanf("%s", name);
                printf("새 가격: ");
                scanf("%d", &price);
                updateMenuItemPrice(name, price);
                break;
            case 5:
                printf("회 이름: ");
                scanf("%s", name);
                printf("새 제철 여부 (0: 아니오, 1: 예): ");
                scanf("%d", &is_seasonal);
                updateIsSeasonal(name, is_seasonal);
                break;
            case 6:
                printf("회 이름: ");
                scanf("%s", name);
                printf("새 싯가 여부 (0: 아니오, 1: 예): ");
                scanf("%d", &is_market_price);
                updateIsMarketPrice(name, is_market_price);
                break;
            case 7:
                printMenu();
                break;
            case 8:
                printf("프로그램을 종료합니다.\n");
                return 0;
            default:
                printf("잘못된 선택입니다. 다시 시도해주세요.\n");
        }
    }
    return 0;
}