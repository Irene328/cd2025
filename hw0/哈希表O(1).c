#include <stdio.h>
#include <stdlib.h>

#define ASCII_SIZE 256  // 假設 ASCII 字元範圍

void readSelf(int hashTable[]) {
    FILE *file = fopen(__FILE__, "r");
    if (!file) {
        printf("無法開啟檔案\n");
        return;
    }

    char c;
    while ((c = fgetc(file)) != EOF) {
        hashTable[(unsigned char)c]++;  // 直接存入哈希表
    }

    fclose(file);
}

void printHashTable(int hashTable[]) {
    for (int i = 0; i < ASCII_SIZE; i++) {
        if (hashTable[i] > 0) {
            printf("%c: %d\n", i, hashTable[i]);
        }
    }
}

int main() {
    int hashTable[ASCII_SIZE] = {0};  // 初始化哈希表
    readSelf(hashTable);
    printHashTable(hashTable);
    return 0;
}
