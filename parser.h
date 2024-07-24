#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"

// Function prototypes for the parser
void parseProgram();
void parseDeclaration();
void parseExpression();
void parseSimpleExpression();
void parseCompoundExpression();
void parseFunctionApplication();
void parseLambdaExpression();
void parseIfExpression();
void parseLetExpression();
void parseInfixExpression();

// Utility functions
void match(int expectedToken);
int getToken();

extern int currentToken;

#endif
