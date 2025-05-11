#include <stdio.h>
#include <string.h>

#define MAX_TOKEN_LEN 100
#define MAX_LINE_LEN 200

char token_type[MAX_TOKEN_LEN]; // LITERAL_TOKEN, PLUS_TOKEN, etc.
char token_lexeme[MAX_TOKEN_LEN]; // actual string like "1", "+", etc.
FILE *tokenFile;

int nextToken() {
    char line[MAX_LINE_LEN];
    if (fgets(line, sizeof(line), tokenFile)) {
        // e.g., "(1: LITERAL_TOKEN)" or "(+: PLUS_TOKEN)"
        sscanf(line, "(%[^:]: %[^\n)])", token_lexeme, token_type);
        // printf("DEBUG: lexeme=%s, type=%s\n", token_lexeme, token_type);
        return 1;
    } else {
        strcpy(token_type, "EOF");
        return 0;
    }
}

void error(const char *msg) {
    printf("Parse error: %s (token = '%s')\n", msg, token_type);
}

// Grammar:
// S  → E S′
// S′ → + S | ε
// E  → num | ( S )

void parse_S();
void parse_Sprime();
void parse_E();

void parse_S() {
    printf("S -> E S'\n");
    parse_E();
    parse_Sprime();
}

void parse_Sprime() {
    if (strcmp(token_type, "PLUS_TOKEN") == 0) {
        printf("S' -> + S\n");
        nextToken();
        parse_S();
    } else if (strcmp(token_type, "REFTPAREN_TOKEN") == 0 || strcmp(token_type, "EOF") == 0) {
        printf("S' -> ε\n");
        // epsilon production
    } else {
        error("Expected '+' or ')' or EOF in S'");
    }
}

void parse_E() {
    if (strcmp(token_type, "LITERAL_TOKEN") == 0) {
        printf("E -> num (%s)\n", token_lexeme);
        nextToken();
    } else if (strcmp(token_type, "LEFTPAREN_TOKEN") == 0) {
        printf("E -> ( S )\n");
        nextToken();
        parse_S();
        if (strcmp(token_type, "REFTPAREN_TOKEN") == 0) {
            nextToken();
        } else {
            error("Expected ')'");
        }
    } else {
        error("Expected number or '(' in E");
    }
}

int main() {
    tokenFile = fopen("tokens.txt", "r");
    if (!tokenFile) {
        printf("Cannot open tokens.txt\n");
        return 1;
    }

    nextToken();
    parse_S();

    if (strcmp(token_type, "EOF") != 0) {
        error("Unexpected token after parsing complete");
    }

    fclose(tokenFile);
    return 0;
}
