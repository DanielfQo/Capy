#include "parser.h"

void error() {
    printf("Error de sintaxis\n");
    exit(1);
}

void asignacion(FILE *f) {

    if (scanner(fgetc(f)) != ID) error(); 
    if (scanner(fgetc(f)) != '=') error();  
    
    expresion(f);
    printf("Asignacion");
}

void expresion(FILE *f) {
    termino(f);
    while (1) {
        int token = scanner(fgetc(f));  
        if (token != '+' && token != '-') {
            ungetc(token, f);
            break;
        }
        termino(f);
    }
}

void termino(FILE *f) {
    factor(f);
    while (1) {
        int token = scanner(fgetc(f));  
        if (token != '*' && token != '/') {
            ungetc(token, f);
            break;
        }
        factor(f);
    }
}

void factor(FILE *f) {
    int token = scanner(fgetc(f));  
    if (token == ID || token == NUM) return;
    else if (token == '(') {
        expresion(f);
        if (scanner(fgetc(f)) != ')') error();  
    } else {
        error();
    }
}
