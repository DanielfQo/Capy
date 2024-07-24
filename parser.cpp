#include "parser.h"
#include <stdlib.h>
#include <string.h>

int currentToken;
extern FILE *inputFile;

int getToken() {
    char token[80];
    int c;

    // Saltar espacios en blanco
    do {
        c = fgetc(inputFile);
        if (c == EOF) {
            return EOF;
        }
    } while (isspace(c));

    // Leer token
    int i = 0;
    while (!isspace(c) && c != EOF) {
        token[i++] = c;
        c = fgetc(inputFile);
    }
    token[i] = '\0';
    if (strcmp(token, "ID") == 0) return ID;
    if (strcmp(token, "NUM") == 0) return NUM;
    if (strcmp(token, "LET") == 0) return LET;
    if (strcmp(token, "IN") == 0) return IN;
    if (strcmp(token, "IF") == 0) return IF;
    if (strcmp(token, "THEN") == 0) return THEN;
    if (strcmp(token, "ELSE") == 0) return ELSE;
    if (strcmp(token, "CASE") == 0) return CASE;
    if (strcmp(token, "OF") == 0) return OF;
    if (strcmp(token, "LAMBDA") == 0) return LAMBDA;
    if (strcmp(token, "WHERE") == 0) return WHERE;
    if (strcmp(token, "DO") == 0) return DO;
    if (strcmp(token, "DERIVING") == 0) return DERIVING;
    if (strcmp(token, "CLASS") == 0) return CLASS;
    if (strcmp(token, "INSTANCE") == 0) return INSTANCE;
    if (strcmp(token, "TYPE") == 0) return TYPE;
    if (strcmp(token, "MODULE") == 0) return MODULE;
    if (strcmp(token, "NEWTYPE") == 0) return NEWTYPE;
    if (strcmp(token, "DEFAULT") == 0) return DEFAULT;
    if (strcmp(token, "IMPORT") == 0) return IMPORT;
    if (strcmp(token, "INFIX") == 0) return INFIX;
    if (strcmp(token, "INFIXL") == 0) return INFIXL;
    if (strcmp(token, "INFIXR") == 0) return INFIXR;
    if (strcmp(token, "FOREIGN") == 0) return FOREIGN;
    if (strcmp(token, "FORALL") == 0) return FORALL;
    if (strcmp(token, "MDO") == 0) return MDO;
    if (strcmp(token, "REC") == 0) return REC;
    if (strcmp(token, "PROC") == 0) return PROC;
    if (strcmp(token, "=") == 0) return ASIG;
    if (strcmp(token, "IGUAL") == 0) return IGUAL;
    if (strcmp(token, "DIFERENTE") == 0) return DIFERENTE;
    if (strcmp(token, "<") == 0) return MENOR;
    if (strcmp(token, "MENORIGUAL") == 0) return MENORIGUAL;
    if (strcmp(token, ">") == 0) return MAYOR;
    if (strcmp(token, "MAYORIGUAL") == 0) return MAYORIGUAL;
    if (strcmp(token, "DOS_PUNTOS_DOS_PUNTOS") == 0) return DOS_PUNTOS_DOS_PUNTOS;
    if (strcmp(token, "FLECHA_FUNCION") == 0) return FLECHA_FUNCION;
    if (strcmp(token, "FLECHA_TIPO") == 0) return FLECHA_TIPO;
    if (strcmp(token, "(") == 0) return PARI;
    if (strcmp(token, ")") == 0) return PARD;
    if (strcmp(token, "[") == 0) return CORCHETEI;
    if (strcmp(token, "]") == 0) return CORCHETED;
    if (strcmp(token, "{") == 0) return LLAVEI;
    if (strcmp(token, "}") == 0) return LLAVED;
    if (strcmp(token, ";") == 0) return PUNTOYCOMA;
    if (strcmp(token, ",") == 0) return COMA;
    if (strcmp(token, ".") == 0) return PUNTO;
    if (strcmp(token, ":") == 0) return DOS_PUNTOS;
    if (strcmp(token, "|") == 0) return BARRA_VERTICAL;
    if (strcmp(token, "+") == 0) return SUMA;
    if (strcmp(token, "-") == 0) return RESTA;
    if (strcmp(token, "*") == 0) return MULT;
    if (strcmp(token, "/") == 0) return DIV;

    return EOF;
}

void match(int expectedToken) {
    if (currentToken == expectedToken) {
        currentToken = getToken();
    } else {
        printf("Syntax error: expected %d but found %d\n", expectedToken, currentToken);
        exit(1);
    }
}
void parseProgram() {
    while (currentToken == LET) {
        parseDeclaration();
    }
    parseExpression();
}

void parseDeclaration() {
    match(LET);
    match(ID);
    match(ASIG);
    parseExpression();
    match(IN);
    parseExpression();
}

void parseExpression() {
    if (currentToken == ID || currentToken == NUM || currentToken == '(' || currentToken == LAMBDA || currentToken == IF || currentToken == LET) {
        if (currentToken == ID || currentToken == NUM || currentToken == '(') {
            parseSimpleExpression();
            if (currentToken == '+' || currentToken == '-' || currentToken == '*' || currentToken == '/') {
                parseInfixExpression();
            }
        } else {
            parseCompoundExpression();
        }
    } else {
        printf("Syntax error: Expected expression\n");
        exit(1);
    }
}

void parseSimpleExpression() {
    if (currentToken == ID) {
        match(ID);
    } else if (currentToken == NUM) {
        match(NUM);
    } else if (currentToken == '(') {
        match('(');
        parseExpression();
        match(')');
    } else {
        printf("Syntax error: Expected simple expression\n");
        exit(1);
    }
}

void parseCompoundExpression() {
    switch (currentToken) {
        case ID:
            parseFunctionApplication();
            break;
        case LAMBDA:
            parseLambdaExpression();
            break;
        case IF:
            parseIfExpression();
            break;
        case LET:
            parseLetExpression();
            break;
        default:
            printf("Syntax error: Expected compound expression\n");
            exit(1);
    }
}

void parseFunctionApplication() {
    match(ID);
    while (currentToken == ID || currentToken == NUM || currentToken == '(') {
        parseSimpleExpression();
    }
}

void parseLambdaExpression() {
    match(LAMBDA);
    match(ID);
    match(FLECHA_FUNCION);
    parseExpression();
}

void parseIfExpression() {
    match(IF);
    parseExpression();
    match(THEN);
    parseExpression();
    match(ELSE);
    parseExpression();
}

void parseLetExpression() {
    match(LET);
    parseDeclaration();
    match(IN);
    parseExpression();
}

void parseInfixExpression() {
    while (currentToken == '+' || currentToken == '-' || currentToken == '*' || currentToken == '/') {
        match(currentToken);
        parseSimpleExpression();
    }
}