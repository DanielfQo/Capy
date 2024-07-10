#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define ID 256
#define NUM 257
#define LET 258
#define IN 259
#define IF 260
#define THEN 261
#define ELSE 262
#define CASE 263
#define OF 264
#define LAMBDA 265
#define IO 266

#define ASIG '='
#define IGUAL 266
#define DIFERENTE 267
#define MENOR '<'
#define MENORIGUAL 268
#define MAYOR '>'
#define MAYORIGUAL 269
#define DOS_PUNTOS_DOS_PUNTOS 270

#define PARI '('
#define PARD ')'
#define CORCHETEI '['
#define CORCHETED ']'
#define LLAVEI '{'
#define LLAVED '}'
#define PUNTOYCOMA ';'
#define COMA ','

#define SUMA '+'
#define RESTA '-'
#define MULT '*'
#define DIV '/'

FILE *f;
char lexema[80];

int scanner();
int esPalabraReservada();
void mostrar(int token);

int scanner() {
    int i;
    int c;

    do 
        c=fgetc(f);
    while(isspace(c));  

    if (c == EOF)
        return EOF;

    if (isalpha(c)) // Regla del ID
    {
        i = 0;
        do
        {
            lexema[i++] = c;
            c = fgetc(f);
        } while (isalnum(c) || c == '_');

        lexema[i] = 0;
        ungetc(c, f); // Se devuelve c al flujo de entrada
        i = esPalabraReservada(); // Verifica si es palabra reservada
        if (i >= 0)
            return i;
        return ID; // Se trata de un ID
    }

    if (isdigit(c)) // Regla del NUM
    {
        i = 0;
        do
        {
            lexema[i++] = c;
            c = fgetc(f);
        } while (isdigit(c));

        lexema[i] = 0;
        ungetc(c, f);
        return NUM;
    }

    if ((c == ';') || (c == '(') || (c == ')') || (c == ',') || (c == '{') || (c == '}') || (c == '[') || (c == ']'))
        return c; // Regla del ";" y "(" ")" ","

    if ((c == '+') || (c == '-') || (c == '*') || (c == '/'))
        return c; // Regla de "+ - * /"

    if (c == '>') // Regla de ">" o ">="
    {
        c = fgetc(f);
        if (c == '=')
        { // return MAYORIGUAL
            lexema[0] = '>';
            lexema[1] = '=';
            lexema[2] = 0;
            return MAYORIGUAL;
        }
        ungetc(c, f);
        return MAYOR; // return MAYOR
    }

    if (c == '<') // Regla de "<" o "<="
    {
        c = fgetc(f);
        if (c == '=')
        { // return MENORIGUAL
            lexema[0] = '<';
            lexema[1] = '=';
            lexema[2] = 0;
            return MENORIGUAL;
        }
        ungetc(c, f);
        return MENOR; // return MENOR
    }

    if (c == '=') // Regla de "=" o "=="
    {
        c = fgetc(f);
        if (c == '=')
        { // return IGUAL
            lexema[0] = '=';
            lexema[1] = '=';
            lexema[2] = 0;
            return IGUAL;
        }
        ungetc(c, f);
        return ASIG; // return ASIG
    }

    if (c == '!') // Regla de "!="
    {
        c = fgetc(f);
        if (c == '='){ // return DIFERENTE
            lexema[0] = '!';
            lexema[1] = '=';
            lexema[2] = 0;
            return DIFERENTE;
        }
        ungetc(c, f);
        return -1; // return -1
    }

    if (c == ':') {
        c = fgetc(f);
        if (c == ':') {
            lexema[0] = ':';
            lexema[1] = ':';
            lexema[2] = 0;
            return DOS_PUNTOS_DOS_PUNTOS;
        }
        ungetc(c, f);
        // Devuelve el token para :
        return ':';
    }

    return -1; // Si no se reconoce el carácter, devuelve un error
} // Fin de scanner

int esPalabraReservada()
{
    if (strcmp(lexema, "let") == 0)
        return LET;
    if (strcmp(lexema, "in") == 0)
        return IN;
    if (strcmp(lexema, "if") == 0)
        return IF;
    if (strcmp(lexema, "then") == 0)
        return THEN;
    if (strcmp(lexema, "else") == 0)
        return ELSE;
    if (strcmp(lexema, "case") == 0)
        return CASE;
    if (strcmp(lexema, "of") == 0)
        return OF;
    if (strcmp(lexema, "\\") == 0)
        return LAMBDA;
    if (strcmp(lexema, "IO") == 0)
        return IO;
    return -1;
}

void mostrar(int token)
{
    switch (token)
    {
        case ID: printf("token = ID [%s] \n", lexema); break;
        case NUM: printf("token = NUM [%s] \n", lexema); break;
        case LET: printf("token = LET [%s] \n", lexema); break;
        case IN: printf("token = IN [%s] \n", lexema); break;
        case IF: printf("token = IF [%s] \n", lexema); break;
        case THEN: printf("token = THEN [%s] \n", lexema); break;
        case ELSE: printf("token = ELSE [%s] \n", lexema); break;
        case CASE: printf("token = CASE [%s] \n", lexema); break;
        case OF: printf("token = OF [%s] \n", lexema); break;
        case LAMBDA: printf("token = LAMBDA [%s] \n", lexema); break;
        case PARI: printf("token = PARI [%c] \n", token); break;
        case PARD: printf("token = PARD [%c] \n", token); break;
        case MAYOR: printf("token = MAYOR [%c] \n", token); break;
        case PUNTOYCOMA: printf("token = PUNTOYCOMA [%c] \n", token); break;
        case ASIG: printf("token = ASIG [%c] \n", token); break;
        case IGUAL: printf("token = IGUAL [%s] \n", lexema); break;
        case DIFERENTE: printf("token = DIFERENTE [%s] \n", lexema); break;
        case MENOR: printf("token = MENOR [%c] \n", token); break;
        case MENORIGUAL: printf("token = MENORIGUAL [%s] \n", lexema); break;
        case CORCHETEI: printf("token = CORCHETEI [%c] \n", token); break;
        case CORCHETED: printf("token = CORCHETED [%c] \n", token); break;
        case LLAVEI: printf("token = LLAVEI [%c] \n", token); break;
        case LLAVED: printf("token = LLAVED [%c] \n", token); break;
        case COMA: printf("token = COMA [%c] \n", token); break;
        case SUMA: printf("token = SUMA [%c] \n", token); break;
        case RESTA: printf("token = RESTA [%c] \n", token); break;
        case DIV: printf("token = DIV [%c] \n", token); break;
        case MULT: printf("token = MULT [%c] \n", token); break;
        case DOS_PUNTOS_DOS_PUNTOS: printf("token = DOS_PUNTOS_DOS_PUNTOS [%s] \n", lexema); break;
        default: printf("no existe");
    }
}

void bloque();
void funcion();
void asignacion();
void expresion();
void termino();
void factor();
void error();

void error() {
    printf("Error de sintaxis\n");
    exit(1);
}

void bloque(){
    funcion();
    asignacion();
    if(scanner() == EOF) return;
    else if(scanner() == ID){
        ungetc(ID, f);
        bloque();
    }
    else{
        ungetc(scanner(), f);
        return;
    }
}

void funcion(){
    if(scanner() != ID) error();
    if(scanner() != DOS_PUNTOS_DOS_PUNTOS) error();
    if(scanner() != IO ) error();
    if(scanner() != PARI) error();
    if(scanner() != PARD) error();
}

void asignacion() {

    if (scanner() != ID) error(); 
    if (scanner() != '=') error();  
    
    expresion();
    if (scanner() != PUNTOYCOMA) error();
}

void expresion() {
    termino();
    while (1) {
        int token = scanner();  
        if (token != '+' && token != '-') {
            ungetc(token, f);
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
            ungetc(token, f);
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

int main(int argc, char *argv[]) {
    f = stdin; // Por defecto, leer de la entrada estándar

    if (argc == 2) {
        f = fopen(argv[1], "r"); // Intentar abrir el archivo especificado en argv[1]
        if (f == NULL) {
            perror("Error al abrir el archivo de entrada");
            return 1;
        }
    }
    
    bloque(); // Llamar al parser
    printf("Sintaxis correcta\n");

    if (f != stdin) {
        fclose(f); // Cerrar el archivo solo si no es stdin
    }
    
    return 0;
}



