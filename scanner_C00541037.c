// Sebesta scanner starter code (C)
// Based on p. 172 of Concepts of Programming Languages, Robert Sebesta, 10th ed.

#include <stdio.h>
#include <ctype.h>
#include <string.h>
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
#define DEC_POINT 2
#define COLON_CHAR 3
#define EQUAL_CHAR 4
#define UNKNOWN 99

/* Token codes */
#define FLOAT_LIT 10
#define VARNAME 11
#define ADD_OP 21
#define SUB_OP 22
#define MULT_OP 23
#define DIV_OP 24
#define LEFT_PAREN 25
#define RIGHT_PAREN 26
#define IF_KEY 27
#define ELSE_KEY 28
#define ASSIGN_OP 29

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
        else if (nextChar == '.')
            charClass = DEC_POINT;
        else if (nextChar == ':')
            charClass = COLON_CHAR;
        else
            charClass = UNKNOWN;
    } else {
        charClass = EOF;
    }
}

void getNonBlank(void)
{
    while (charClass != EOF && isspace((unsigned char)nextChar))
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
        nextToken = UNKNOWN;
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
        if (strcmp(lexeme, "if") == 0)
            nextToken = IF_KEY;
        else if (strcmp(lexeme, "else") == 0)
            nextToken = ELSE_KEY;
        else
            nextToken = VARNAME;
        break;
    case DIGIT:
        addChar();
        getChar();
        while (charClass == DIGIT) {
            addChar();
            getChar();
        }
        if (charClass == DEC_POINT) {
            addChar();
            getChar();
            while (charClass == DIGIT) {
                addChar();
                getChar();
            }
        }
        nextToken = FLOAT_LIT;
        break;
    case DEC_POINT:
        lookup(nextChar);
        getChar();
        break;
    case COLON_CHAR:
        addChar();
        getChar();
        if (nextChar == '=') {
            addChar();
            getChar();
            nextToken = ASSIGN_OP;
        } else {
            nextToken = UNKNOWN;
        }
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
