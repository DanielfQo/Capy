#include "parser.h"


void asignacion() {
    if (scanner() != ID) error();  
    if (scanner() != '=') error();
    expresion();
}

void expresion() {
    termino();
    while (1) {
        int token = scanner();  
        if (token != '+' && token != '-') {
            ungetc(token, stdin); 
            break;
        }
        termino();
    }
}

void termino() {
    factor();
    while (1) {
        int token = scanner();
        if (token != '*' && token != '/') {
            ungetc(token, stdin);
            break;
        }
        factor();
    }
}

void factor() {
    int token = scanner();
    if (token == ID || token == NUM) return; 
    else if (token == '(') {
        expresion();
        if (scanner() != ')') error();  
    } else {
        error();  
    }
}

void error() {
    printf("Error de sintaxis\n");
    exit(1);
}