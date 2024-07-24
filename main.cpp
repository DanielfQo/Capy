#include <stdio.h>
#include <stdlib.h>
#include "lexer.h"
#include "parser.h"

FILE *inputFile;
FILE *outputFile;

int main() {
    inputFile = fopen("input.txt", "r");
    if (inputFile == NULL) {
        printf("Error: Could not open input file\n");
        exit(1);
    }

    outputFile = fopen("tokens.txt", "w");
    if (outputFile == NULL) {
        printf("Error: Could not open output file\n");
        exit(1);
    }

    // Run lexer
    while (scanner(inputFile) != EOF);

    fclose(inputFile);
    fclose(outputFile);

    // Open tokens file for reading
    inputFile = fopen("tokens.txt", "r");
    if (inputFile == NULL) {
        printf("Error: Could not open tokens file\n");
        exit(1);
    }

    // Run parser
    currentToken = getToken();
    parseProgram();

    fclose(inputFile);

    printf("Parsing completed successfully\n");

    return 0;
}
