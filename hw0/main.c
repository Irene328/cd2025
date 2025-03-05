#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Node {
    char ch;
    int count;
    struct Node *next;
} Node;

// 在 linked list 中查找字元，若找到則增加計數，否則新增節點
void insert(Node **head, char ch) {
    Node *current = *head;
    while (current != NULL) {
        if (current->ch == ch) {
            current->count++;
            return;
        }
        current = current->next;
    }
    // 若未找到則新增節點
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->ch = ch;
    newNode->count = 1;
    newNode->next = *head;
    *head = newNode;
}

// 列印 linked list
void printList(Node *head) {
    Node *current = head;
    while (current != NULL) {
        printf("%c : %d\n", current->ch, current->count);
        current = current->next;
    }
}

// 釋放 linked list
void freeList(Node *head) {
    Node *current = head;
    while (current != NULL) {
        Node *temp = current;
        current = current->next;
        free(temp);
    }
}

int main() {
    Node *head = NULL;
    char input[1000]; // 假設輸入最多 1000 個字元
    fgets(input, sizeof(input), stdin);
    
    for (int i = 0; i < strlen(input); i++) {
        if (input[i] != '\n') { // 忽略換行符
            insert(&head, input[i]);
        }
    }
    
    printList(head);
    freeList(head);
    
    return 0;
}
