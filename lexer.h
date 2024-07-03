#ifndef LEXER_H
#define LEXER_H

#include <stdio.h>
#include <ctype.h>
#include <string.h>

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

extern int scanner(int c);
void mostrar(int);
int esPalabraReservada();


extern FILE *f;
extern char lexema[80];

#endif