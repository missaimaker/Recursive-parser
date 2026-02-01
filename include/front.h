#ifndef FRONT_H
#define FRONT_H

/*character classes*/
#define LETTER 0
#define DIGIT 1
#define UNKNOWN 99

/*Token Codes*/
#define INT_LIT 10
#define IDENT 11
#define ASSIGN_OP 12
#define ADD_OP 13
#define SUB_OP 14
#define MULT_OP 15
#define DIV_OP 16
#define LEFT_PAREN 17
#define RIGHT_PAREN 18
#define LESSER_OP 19
#define GREATER_OP 20
#define EQUAL_OP 21
#define NEQUAL_OP 22
#define LEQUAL_OP 23
#define GEQUAL_OP 24
#define POW_OP 25
#define INC_OP 26
#define DEC_OP 27
#define SEMICOLON 28
#define COLON 29
#define KEY_READ 30
#define KEY_PRINT 31
#define KEY_IF 32
#define KEY_ELSE 33
#define KEY_BEGIN 34
#define KEY_END 35

int lex();
#endif
