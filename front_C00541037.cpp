// Sebesta scanner starter code (C++)
// Based on p. 172 of Concepts of Programming Languages, Robert Sebesta, 10th ed.

#include <iostream>
#include <fstream>
#include <cctype>
#include <unistd.h>

using namespace std;

int charClass;
string lexeme;
char nextChar;
int token;
int nextToken;
ifstream in_fp;

void my_addChar();
void my_getChar();
void getNonBlank();
int lookup(char ch);
int lex();

const int LETTER = 0;
const int DIGIT = 1;
const int DEC_POINT = 2;
const int COLON_CHAR = 3;
const int EQUAL_CHAR = 4;
const int UNKNOWN = 99;

const int FLOAT_LIT = 10;
const int VARNAME = 11;
const int ADD_OP = 21;
const int SUB_OP = 22;
const int MULT_OP = 23;
const int DIV_OP = 24;
const int LEFT_PAREN = 25;
const int RIGHT_PAREN = 26;
const int IF_KEY = 27;
const int ELSE_KEY = 28;
const int ASSIGN_OP = 29;

int main(int argc, const char *argv[])
{
    (void)argc;
    (void)argv;
    in_fp.open("test data.in");

    if (in_fp.is_open()) {
        my_getChar();
        do {
            lex();
        } while (nextToken != EOF);
    } else {
        cout << "Cannot open test data.in" << endl;
        char cwd[1024];
        if (getcwd(cwd, sizeof(cwd)) != NULL)
            cout << "Current working dir: " << cwd << endl;
    }

    return 0;
}

void my_addChar()
{
    lexeme += nextChar;
}

void my_getChar()
{
    if (!in_fp.get(nextChar)) {
        charClass = EOF;
    } else if (isalpha((unsigned char)nextChar)) {
        charClass = LETTER;
    } else if (isdigit((unsigned char)nextChar)) {
        charClass = DIGIT;
    } else if (nextChar == '.') {
        charClass = DEC_POINT;
    } else {
        charClass = UNKNOWN;
    }
}

void getNonBlank()
{
    while (charClass != EOF && isspace((unsigned char)nextChar))
        my_getChar();
}

int lookup(char ch)
{
    switch (ch) {
    case '(':
        my_addChar();
        nextToken = LEFT_PAREN;
        break;
    case ')':
        my_addChar();
        nextToken = RIGHT_PAREN;
        break;
    case '+':
        my_addChar();
        nextToken = ADD_OP;
        break;
    case '-':
        my_addChar();
        nextToken = SUB_OP;
        break;
    case '*':
        my_addChar();
        nextToken = MULT_OP;
        break;
    case '/':
        my_addChar();
        nextToken = DIV_OP;
        break;
    default:
        my_addChar();
        nextToken = EOF;
        break;
    }
    return nextToken;
}

int lex()
{
    lexeme = "";
    getNonBlank();

    switch (charClass) {
    case LETTER:
        my_addChar();
        my_getChar();
        while (charClass == LETTER || charClass == DIGIT) {
            my_addChar();
            my_getChar();
        }
        nextToken = VARNAME;
        break;
    case DIGIT:
        my_addChar();
        my_getChar();
        while (charClass == DIGIT) {
            my_addChar();
            my_getChar();
        }
        if (charClass == DEC_POINT) {
            my_addChar();
            my_getChar();
            while (charClass == DIGIT) {
                my_addChar();
                my_getChar();
            }
        }
        nextToken = FLOAT_LIT;
        break;
    case DEC_POINT:
        lookup(nextChar);
        my_getChar();
        break;
    case UNKNOWN:
        lookup(nextChar);
        my_getChar();
        break;
    case EOF:
        nextToken = EOF;
        lexeme = "EOF";
        break;
    }

    cout << "Next token is: " << nextToken
         << ", Next lexeme is: " << lexeme << endl;
    return nextToken;
}
