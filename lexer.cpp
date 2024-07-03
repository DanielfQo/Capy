#include "lexer.h"


char lexema[80]; // Definición del arreglo lexema

int scanner(int c){
    int i;
    
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