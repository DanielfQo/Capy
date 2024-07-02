#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

#include "lexer.cpp"
#include "parser.cpp"

int main(int n, char *pal[])
{
    int token;
    f = stdin; // Entrada estándar del teclado
    if (n == 2) // Si se especificó un archivo de lectura
    {
        f = fopen(pal[1], "rt"); // Lectura modo texto
        if (f == NULL)
            f = stdin;
    }
    if (f == stdin) // La lectura será desde la entrada estándar
        printf("Ingrese texto ........ termine con Ctrl z \n");

    while (1)
    {
        token = scanner();
        if (token == EOF)
            break;
        mostrar(token);
    }

    if (f != stdin) // Si la entrada fue de un archivo
        fclose(f); // Entonces cerrar el archivo.
        
    return 0;
}