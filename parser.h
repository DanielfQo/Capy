#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include "lexer.h"

void programa(FILE *f);
void declaracion(FILE *f);
void asignacion(FILE *f);
void expresion(FILE *f);
void termino(FILE *f);
void factor(FILE *f);
void error(const char *msg);

#endif
