#ifndef LEXER_H
#define LEXER_H

#include <stdio.h>
#include <ctype.h>
#include <string.h>

// Tokens de identificadores y números
#define ID 256        // Identificador
#define NUM 257       // Número

// Tokens de palabras reservadas
#define LET 258       // let
#define IN 259        // in
#define IF 260        // if
#define THEN 261      // then
#define ELSE 262      // else
#define CASE 263      // case
#define OF 264        // of
#define LAMBDA 265    // \ (lambda)
#define WHERE 266     // where
#define DO 267        // do
#define DERIVING 268  // deriving
#define CLASS 269     // class
#define INSTANCE 270  // instance
#define TYPE 271      // type
#define MODULE 272    // module
#define NEWTYPE 273   // newtype
#define DEFAULT 274   // default
#define IMPORT 275    // import
#define INFIX 276     // infix
#define INFIXL 277    // infixl
#define INFIXR 278    // infixr
#define FOREIGN 279   // foreign
#define FORALL 280    // forall
#define MDO 281       // mdo
#define REC 282       // rec
#define PROC 283      // proc

// Tokens de operadores y símbolos especiales
#define ASIG '='             // =
#define IGUAL 284            // ==
#define DIFERENTE 285        // !=
#define MENOR '<'            // <
#define MENORIGUAL 286       // <=
#define MAYOR '>'            // >
#define MAYORIGUAL 287       // >=
#define DOS_PUNTOS_DOS_PUNTOS 288  // ::
#define FLECHA_FUNCION 289   // ->
#define FLECHA_TIPO 290      // =>

// Tokens de puntuación
#define PARI '('        // (
#define PARD ')'        // )
#define CORCHETEI '['   // [
#define CORCHETED ']'   // ]
#define LLAVEI '{'      // {
#define LLAVED '}'      // }
#define PUNTOYCOMA ';'  // ;
#define COMA ','        // ,
#define PUNTO '.'       // .
#define DOS_PUNTOS ':'  // :
#define BARRA_VERTICAL '|'  // |

// Tokens de operadores aritméticos
#define SUMA '+'  // +
#define RESTA '-' // -
#define MULT '*'  // *
#define DIV '/'   // /

extern int scanner(int c);
void mostrar(int);
int esPalabraReservada();

extern FILE *f;
extern char lexema[80];

#endif
