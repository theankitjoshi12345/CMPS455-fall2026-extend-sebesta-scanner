// Sebesta scanner starter code (C)
// Based on p. 172 of Concepts of Programming Languages, Robert Sebesta, 10th ed.

#include <stdio.h>
#include <ctype.h>
#include <unistd.h>

/* Global variables */
int charClass;
char lexeme[100];
char nextChar;
int lexLen;
int token;
int nextToken;
FILE *in_fp;

/* Function declarations */
void addChar(void);
void getChar(void);
void getNonBlank(void);
int lookup(char ch);
int lex(void);

/* Character classes */
#define LETTER 0
#define DIGIT 1
#define UNKNOWN 99

/* Token codes */
#define INT_LIT 10
#define IDENT 11
#define ASSIGN_OP 20
#define ADD_OP 21
#define SUB_OP 22
#define MULT_OP 23
#define DIV_OP 24
#define LEFT_PAREN 25
#define RIGHT_PAREN 26

int main(int argc, const char *argv[])
{
    char cwd[1024];

    (void)argc;
    (void)argv;
    if ((in_fp = fopen("test data.in", "r")) == NULL) {
        printf("ERROR: cannot open test data.in \n");
        if (getcwd(cwd, sizeof(cwd)) != NULL)
            printf("Current working dir: %s\n", cwd);
        else
            perror("getcwd() error");
        return -1;
    }

    getChar();
    do {
        lex();
    } while (nextToken != EOF);

    return 0;
}

void addChar(void)
{
    if (lexLen <= 98) {
        lexeme[lexLen++] = nextChar;
        lexeme[lexLen] = '\0';
    } else {
        printf("Error: lexeme is too long.");
    }
}

void getChar(void)
{
    if ((nextChar = getc(in_fp)) != EOF) {
        if (isalpha((unsigned char)nextChar))
            charClass = LETTER;
        else if (isdigit((unsigned char)nextChar))
            charClass = DIGIT;
        else
            charClass = UNKNOWN;
    } else {
        charClass = EOF;
    }
}

void getNonBlank(void)
{
    while (isspace((unsigned char)nextChar))
        getChar();
}

int lookup(char ch)
{
    switch (ch) {
    case '(':
        addChar();
        nextToken = LEFT_PAREN;
        break;
    case ')':
        addChar();
        nextToken = RIGHT_PAREN;
        break;
    case '+':
        addChar();
        nextToken = ADD_OP;
        break;
    case '-':
        addChar();
        nextToken = SUB_OP;
        break;
    case '*':
        addChar();
        nextToken = MULT_OP;
        break;
    case '/':
        addChar();
        nextToken = DIV_OP;
        break;
    default:
        addChar();
        nextToken = EOF;
        break;
    }
    return nextToken;
}

int lex(void)
{
    lexLen = 0;
    getNonBlank();

    switch (charClass) {
    case LETTER:
        addChar();
        getChar();
        while (charClass == LETTER || charClass == DIGIT) {
            addChar();
            getChar();
        }
        nextToken = IDENT;
        break;
    case DIGIT:
        addChar();
        getChar();
        while (charClass == DIGIT) {
            addChar();
            getChar();
        }
        nextToken = INT_LIT;
        break;
    case UNKNOWN:
        lookup(nextChar);
        getChar();
        break;
    case EOF:
        nextToken = EOF;
        lexeme[0] = 'E';
        lexeme[1] = 'O';
        lexeme[2] = 'F';
        lexeme[3] = '\0';
        break;
    }

    printf("Next token is: %d, Next lexeme is %s\n", nextToken, lexeme);
    return nextToken;
}
