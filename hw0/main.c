#include <stdio.h>
#include <string.h>

typedef struct Node {
    char ch;
    int count;
    struct Node *next;
} Node;

Node *head = NULL;

// 新增或更新鏈結串列中的字元節點
void addChar(char c) {
    Node *current = head, *prev = NULL;

    // 在鏈結串列中尋找該字元
    while (current) {
        if (current->ch == c) {
            current->count++;
            return;
        }
        prev = current;
        current = current->next;
    }

    // 若字元不存在，則新增節點
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (!newNode) return;
    newNode->ch = c;
    newNode->count = 1;
    newNode->next = NULL;

    if (prev)
        prev->next = newNode;
    else
        head = newNode;
}

// 讀取自身檔案
void readSelf() {
    FILE *file = fopen(__FILE__, "r");
    if (!file) {
        printf("無法開啟檔案\n");
        return;
    }
    
    char c;
    while ((c = fgetc(file)) != EOF) {
        addChar(c);
    }
    
    fclose(file);
}

// 輸出鏈結串列
void printList() {
    Node *current = head;
    while (current) {
        printf("%c: %d\n", current->ch, current->count);
        current = current->next;
    }
}

// 釋放鏈結串列記憶體
void freeList() {
    Node *current = head;
    while (current) {
        Node *temp = current;
        current = current->next;
        free(temp);
    }
}

int main() {
    readSelf();
    printList();
    freeList();
    return 0;
}
