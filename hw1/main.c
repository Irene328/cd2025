#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_TOKEN_LEN 100

char token[MAX_TOKEN_LEN];
int pos = 0;

void resetToken() {
    token[0] = '\0';
    pos = 0;
}

void appendChar(char c) {
    if (pos < MAX_TOKEN_LEN - 1) {
        token[pos++] = c;
        token[pos] = '\0';
    }
}

void printToken(const char *str) {
    if (strcmp(str, "int") == 0)
        printf("(int: TYPE_TOKEN)\n");
    else if (strcmp(str, "main") == 0)
        printf("(main: MAIN_TOKEN)\n");
    else if (strcmp(str, "if") == 0)
        printf("(if: IF_TOKEN)\n");
    else if (strcmp(str, "else") == 0)
        printf("(else: ELSE_TOKEN)\n");
    else if (strcmp(str, "while") == 0)
        printf("(while: WHILE_TOKEN)\n");
    else
        printf("(%s: ID_TOKEN)\n", str);
}

void scanFile(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("無法開啟檔案 %s\n", filename);
        return;
    }

    char c, next;
    while ((c = fgetc(file)) != EOF) {
        if (isspace(c)) continue;

        resetToken();

        if (isalpha(c) || c == '_') {
            appendChar(c);
            while ((next = fgetc(file)), isalnum(next) || next == '_') {
                appendChar(next);
            }
            ungetc(next, file);
            printToken(token);
        } else if (isdigit(c)) {
            appendChar(c);
            while ((next = fgetc(file)), isdigit(next)) {
                appendChar(next);
            }
            ungetc(next, file);
            printf("(%s: LITERAL_TOKEN)\n", token);
        } else {
            switch (c) {
                case '=':
                    next = fgetc(file);
                    if (next == '=') printf("(==: EQUAL_TOKEN)\n");
                    else {
                        ungetc(next, file);
                        printf("(=: ASSIGN_TOKEN)\n");
                    }
                    break;
                case '+': printf("(+: PLUS_TOKEN)\n"); break;
                case '-': printf("(-: MINUS_TOKEN)\n"); break;
                case '<':
                    next = fgetc(file);
                    if (next == '=') printf("(<=: LESSEQUAL_TOKEN)\n");
                    else {
                        ungetc(next, file);
                        printf("(<: LESS_TOKEN)\n");
                    }
                    break;
                case '>':
                    next = fgetc(file);
                    if (next == '=') printf("(>=: GREATEREQUAL_TOKEN)\n");
                    else {
                        ungetc(next, file);
                        printf("(>: GREATER_TOKEN)\n");
                    }
                    break;
                case '(': printf("((: LEFTPAREN_TOKEN)\n"); break;
                case ')': printf("): REFTPAREN_TOKEN)\n"); break;
                case '{': printf("({: LEFTBRACE_TOKEN)\n"); break;
                case '}': printf("}: REFTBRACE_TOKEN)\n"); break;
                case ';': printf("(;: SEMICOLON_TOKEN)\n"); break;
                default: break;  // 可加錯誤訊息處理
            }
        }
    }

    fclose(file);
}

int main() {
    scanFile("source.c"); // 請確保 source.c 是你要分析的原始程式碼
    return 0;
}
