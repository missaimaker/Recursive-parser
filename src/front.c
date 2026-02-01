#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "front.h"
#define NUM_KEYWORDS 8

/*Global variable*/
int nextToken; 

/*Local Variables*/
static int charClass;
static char lexeme [100];
static char nextChar;
static int lexLen;
static FILE *in_fp;

/*Local Function Declarations*/
static void addChar();
static void getChar();
static void getNonBlank();

/*array of keywords*/
char *keywords[] = { "read", "print",  "if", "else", "begin", "end" };



/*main driver*/
int main(int argc, char *argv[])
{
    printf ("Cooke Analyzer :: R11846096\n") ;
       
    /*Open the input data and process its contents*/
    if ((in_fp=fopen("input.txt","r"))==NULL) {
        printf("ERROR- cannot open input file");
        return 1;
        } else {
            getChar();
            do{
                lex();
        } while (nextToken!=EOF);
    }
    fclose(in_fp);
    return 0;
}

/*lookup- a function to lookup operators and parentheses and return the * token */
static int lookup(char ch){
    switch (ch){
        case '(':
            addChar();
            nextToken= LEFT_PAREN;
            break;
        case ')':
            addChar();
            nextToken= RIGHT_PAREN;
            break;
        case '+':
            addChar();
            getChar();
            if (nextChar =='+')
            {
                addChar();
                nextToken= INC_OP;
            } else
            {
                ungetc(nextChar, in_fp);
                nextToken= ADD_OP;
            }
            break;
        case '-':
            addChar();
            getChar();
            if (nextChar =='-')
            {
                addChar();
                nextToken= DEC_OP;
            } else
            {
                ungetc(nextChar, in_fp);
                nextToken= SUB_OP;
            }
            break;
        case '*':
            addChar();
            getChar();
            if (nextChar =='*')
            {
                addChar();
            nextToken= POW_OP;
            } else
            {
                ungetc(nextChar, in_fp);
                nextToken= MULT_OP;
            }
            
            break;
        case '/':
            addChar();
            nextToken=DIV_OP;
            break;
        case ';':
            addChar();
            nextToken=SEMICOLON;
            break;
        case ':':
            addChar();
            getChar();
            if (nextChar ='=')
            {
                addChar();
                nextToken= ASSIGN_OP;
            } else
            {
                ungetc(nextChar, in_fp);
                nextToken= COLON;
            }
                break;
            
        case '<':
            addChar();
            getChar();
            if (nextChar =='=')
            {
                addChar();
                nextToken= LEQUAL_OP;
            } else if (nextChar == '>') {
                addChar();
                 nextToken = NEQUAL_OP;
            } else
            {
                ungetc(nextChar, in_fp);
                nextToken= LESSER_OP;
                break;
            }
        case '>':
            addChar();
            getChar();
            if (nextChar =='=')
            {
                addChar();
            nextToken= GEQUAL_OP;
            } else
            {
                ungetc(nextChar, in_fp);
                nextToken= GREATER_OP;
                break;
            }
         case '=':
            addChar();
            nextToken= EQUAL_OP;
            break;
        default:
            addChar();
            nextToken= EOF;
            break;
    }
    return nextToken;
}

static void getNonBlank(){
    while (isspace (nextChar))
     getChar();
}
static int checkKeyword(char*ident){
    int i;
    for(i=0; i<NUM_KEYWORDS; i++){
        if (strcmp(ident, keywords [i])==0){
            switch (i) {
                case 0:
                    return KEY_READ;
                case 1:
                    return KEY_PRINT;
                case 2:
                    return KEY_IF; 
                case 3:
                    return KEY_ELSE;
                case 4:
                    return KEY_BEGIN;
                case 5: 
                    return KEY_END;


            }
    }
}
    return IDENT; /*return IDENT if it's not a keyword*/
}

/*addChar- a function to add nextChar to lexeme*/
static void addChar() {
    if (lexLen <= 98) {
        lexeme[lexLen++] = nextChar;
        lexeme[lexLen] = '\0' ;
    } else {
        printf("Error - Lexeme is too long\n");
    }
}

/*getChar- a function to get the next character input and determine its character class */
static void getChar(){
    if ((nextChar=getc(in_fp)) !=EOF){
        if (isalpha(nextChar))
            charClass= LETTER;
        else if (isdigit(nextChar))
            charClass=DIGIT;
        else charClass= UNKNOWN;
    } else{
            charClass=EOF;
        }
}


/*lex- a simple lexical analyzer for arithmetic expressions*/
int lex(){
    lexLen= 0;
    getNonBlank();
    switch (charClass){
        case LETTER: 
            addChar();
            getChar();
            while (charClass==LETTER || charClass==DIGIT){
                addChar();
                getChar();
            }
            nextToken = checkKeyword(lexeme); 
            break;
    
        case DIGIT:
            addChar();
            getChar();
            while (charClass == DIGIT){
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
                nextToken= EOF; 
                lexeme[0]= 'E';
                lexeme[1]= 'O';
                lexeme[2]= 'F';
                lexeme[3]= '\0';
                break;
    }
    if (nextToken != EOF){
    printf ("Lexeme: %s \tToken: %d\n", lexeme, nextToken);
    }
    return nextToken;

}
