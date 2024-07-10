#include "parser.h"

static int token;
static char lexema[80];

void obtenerToken(FILE *f) {
    token = scanner(f);
}

void error(const char *msg) {
    printf("Error de sintaxis: %s\n", msg);
    exit(1);
}

void programa(FILE *f) {
    obtenerToken(f);
    while (token != EOF) {
        declaracion(f);
        obtenerToken(f);
    }
    printf("Programa correctamente analizado\n");
}

void declaracion(FILE *f) {
    if (token == LET) {
        obtenerToken(f);
        if (token != ID) error("Se esperaba un identificador después de 'let'");
        obtenerToken(f);
        if (token != ASIG) error("Se esperaba '='");
        obtenerToken(f);
        expresion(f);
    } else {
        asignacion(f);
    }
    printf("Declaración válida\n");
}

void asignacion(FILE *f) {
    if (token != ID) error("Se esperaba un identificador");
    obtenerToken(f);
    if (token != ASIG) error("Se esperaba '='");
    obtenerToken(f);
    expresion(f);
    printf("Asignación válida\n");
}

void expresion(FILE *f) {
    termino(f);
    while (token == SUMA || token == RESTA || token == FLECHA_FUNCION || token == FLECHA_TIPO) {
        int op = token;
        obtenerToken(f);
        termino(f);
        printf("Operador %d\n", op);
    }
}

void termino(FILE *f) {
    factor(f);
    while (token == MULT || token == DIV) {
        int op = token;
        obtenerToken(f);
        factor(f);
        printf("Operador %d\n", op);
    }
}

void factor(FILE *f) {
    if (token == ID || token == NUM) {
        printf("Factor: %s\n", lexema);
        obtenerToken(f);
    } else if (token == PARI) {
        obtenerToken(f);
        expresion(f);
        if (token != PARD) error("Se esperaba ')'");
        obtenerToken(f);
    } else if (token == LAMBDA) {
        obtenerToken(f);
        if (token != ID) error("Se esperaba un identificador después de '\\'");
        obtenerToken(f);
        if (token != FLECHA_FUNCION) error("Se esperaba '->' después del identificador en una expresión lambda");
        obtenerToken(f);
        expresion(f);
    } else {
        error("Se esperaba un factor");
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Uso: %s <nombre_archivo>\n", argv[0]);
        return 1;
    }

    FILE *f = fopen(argv[1], "r");
    if (f == NULL) {
        printf("Error al abrir el archivo %s\n", argv[1]);
        return 1;
    }

    programa(f);
    fclose(f);
    return 0;
}
