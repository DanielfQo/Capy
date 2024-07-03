/*
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

#include "lexer.h"
#include "parser.h"

FILE *f;

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

    int c;

    while (1)
    {
        do
            c = fgetc(f);
        while (isspace(c));

        token = scanner(c);
        if (token == EOF)
            break;
        mostrar(token);
    }

    if (f != stdin) // Si la entrada fue de un archivo
        fclose(f); // Entonces cerrar el archivo.

    return 0;
}
//*/

#include <stdio.h>
#include "parser.h"

FILE *f;

int main(int argc, char *argv[]) {
    FILE *f = stdin; // Por defecto, leer de la entrada estándar

    if (argc == 2) {
        f = fopen(argv[1], "r"); // Intentar abrir el archivo especificado en argv[1]
        if (f == NULL) {
            perror("Error al abrir el archivo de entrada");
            return 1;
        }
    }
    printf("Sintaxis correcta\n");
    asignacion(f); // Llamar al parser con el archivo f
    

    if (f != stdin) {
        fclose(f); // Cerrar el archivo solo si no es stdin
    }
    
    return 0;
}

