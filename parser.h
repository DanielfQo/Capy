#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include "lexer.h"

void asignacion();
void expresion();
void termino();
void factor();
void numero();
void digito();
void error();

#endif
