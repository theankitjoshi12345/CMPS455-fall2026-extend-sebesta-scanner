# 1st Programming Assignment: Extend Sebesta Scanner in C and C++

**Course:** CMPS 450 / CMPS 450G  
**Instructor:** Dr. Maida  
**Version:** Final Draft — September 12, 2026

## 1. Assignment

Modify the scanner from Sebesta, *Concepts of Programming Languages* (10th ed.), Chapter 4, page 172. The textbook program is written in C. A C++ translation and Sebesta's C source are also available on Moodle.

The textbook scanner recognizes `IDENT` and `INT_LIT`. Implement the extensions below. The regular expressions use Python syntax and are specifications; they do not need to be used in the implementation unless a regular-expression interpreter is used.

1. Replace `INT_LIT` with `FLOAT_LIT`.

   ```text
   r'\d+(\.\d*)?'
   ```

   A float is one or more digits, optionally followed by a decimal point and zero or more digits. Legal examples: `25`, `25.`, `25.05`.

2. Replace `IDENT` with `VARNAME`.

   ```text
   r'[A-Za-z][A-Za-z0-9]*'
   ```

   A variable name must begin with a letter and may then contain any combination of letters and digits. Legal examples: `Tom`, `t`, `Tom29`.

3. Recognize the Algol assignment operator `ASSIGN_OP`.

   ```text
   r':='
   ```

4. Recognize arithmetic operators.

   ```text
   r'[+\-*/]'
   ```

5. Recognize the `if` and `else` keywords as `IF_KEY` and `ELSE_KEY`.

   ```text
   r'if'
   r'else'
   ```

6. Handle any input character that does not match a token as `UNKNOWN`.

   ```text
   r'.'
   ```

   This matches any non-newline character.

Both programs must accept one line of input from `test data.in` in the same directory as the source code. Their output must match the specified C++ output for the given input.

## 2. Input File

The contents of `test data.in` are below. It contains 16 legal tokens and one illegal token. `1plus` splits into tokens `1` and `plus`; spaces are not always required between tokens, though they are highly recommended. The illegal token is `=` and its token number is `99`.

```text
25 25. 25.05 Tom t tom29 := if else + - * / = 1plus tom29A
```

## 3. Required Command-Line Output

The required output has 18 lines: 16 legal-token lines, one illegal-token line, and one EOF line.

```text
Next token is: 10, Next lexeme is: 25
Next token is: 10, Next lexeme is: 25.
Next token is: 10, Next lexeme is: 25.05
Next token is: 11, Next lexeme is: Tom
Next token is: 11, Next lexeme is: t
Next token is: 11, Next lexeme is: tom29
Next token is: 29, Next lexeme is: :=
Next token is: 27, Next lexeme is: if
Next token is: 28, Next lexeme is: else
Next token is: 21, Next lexeme is: +
Next token is: 22, Next lexeme is: -
Next token is: 23, Next lexeme is: *
Next token is: 24, Next lexeme is: /
Next token is: 99, Next lexeme is: =
Next token is: 10, Next lexeme is: 1
Next token is: 11, Next lexeme is: plus
Next token is: 11, Next lexeme is: tom29A
Next token is: -1, Next lexeme is: EOF
```

In practice, the output-token sequence would be sent to a parser.

## 4. Required Constant Declarations

Use these declarations so that all submissions produce the same output. `DEC_POINT`, `COLON_CHAR`, and `EQUAL_CHAR` may not be needed in the implementation.

```cpp
const int LETTER = 0; // class of current char is LETTER
const int DIGIT = 1; // class of current char is DIGIT
const int DEC_POINT = 2;
const int COLON_CHAR = 3;
const int EQUAL_CHAR = 4;
const int UNKNOWN = 99; // means current is not LETTER or DIGIT
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
```

## 5. C++ Implementation Warning

Do not use the following in `my_getChar()`:

```cpp
in_fp >> nextChar;
```

It handles spaces unexpectedly. Instead, read one character with:

```cpp
in_fp.get(nextChar);
```

This puts one character from the file into `nextChar` and returns `true` if successful. It is analogous to `getc()` in C.

## 6. Compiling and Running

The C and C++ programs should be named `scanner.c` and `scanner.cpp`, respectively. Both read `test data.in`.

On macOS or Linux, compile the C++ version with:

```sh
g++ scanner.cpp -o scanner
```

Run it with:

```sh
./scanner
```

This assumes a GNU C++ compiler is installed; another suitable C++ compiler may be used.

## 7. Grading Criteria

The C and C++ programs will be run from the command line. Both must be converted to this specification.

- C program: 50% of the assignment grade.
- C++ program: 50% of the assignment grade.
- A program that runs and produces the correct output receives 100% for its part.

Assignments and projects together are worth 45% of the final course grade. This assignment is worth about 5% of the final grade; larger assignments will be worth close to 15%.

## 8. Due Date, Submission, and Late Policy

Each program's source code must reside in one file.

- C filename: `scanner_ULID.c`
- C++ filename: `front_ULID.cpp`

Zip the two files together and submit one ZIP file through the Moodle Turnitin portal.

**Due:** Wednesday, September 30, 2026, at 11:59 PM.

Late submissions lose 10% of the assignment grade. Submissions more than one week late lose 50%.

> Note: The assignment brief contains an earlier naming reference to `scanner.c` and `scanner.cpp` for compiling/running; its submission section specifies `scanner_ULID.c` and `front_ULID.cpp`.

## 9. Academic Honesty

You must write your own programs. Identical programs submitted by different students may be treated as academic dishonesty and can result in penalties.

Large language models may be used similarly to Google: to ask specific questions. Do not ask a language model to write the complete program.
