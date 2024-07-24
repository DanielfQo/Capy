#include "lexer.h"
#include <ctype.h>
#include <string.h>

char lexema[80];

const char* tokenNames[] = {
    "ID", "NUM", "LET", "IN", "IF", "THEN", "ELSE", "CASE", "OF", "LAMBDA",
    "WHERE", "DO", "DERIVING", "CLASS", "INSTANCE", "TYPE", "MODULE", "NEWTYPE",
    "DEFAULT", "IMPORT", "INFIX", "INFIXL", "INFIXR", "FOREIGN", "FORALL",
    "MDO", "REC", "PROC", "ASIG", "IGUAL", "DIFERENTE", "MENOR", "MENORIGUAL",
    "MAYOR", "MAYORIGUAL", "DOS_PUNTOS_DOS_PUNTOS", "FLECHA_FUNCION", "FLECHA_TIPO",
    "PARI", "PARD", "CORCHETEI", "CORCHETED", "LLAVEI", "LLAVED", "PUNTOYCOMA",
    "COMA", "PUNTO", "DOS_PUNTOS", "BARRA_VERTICAL", "SUMA", "RESTA", "MULT", "DIV"
};

void writeToken(const char* tokenName) {
    fprintf(outputFile, "%s ", tokenName);
}

int scanner(FILE *f) {
    int c, i;

    while ((c = fgetc(f)) != EOF) {
        if (isspace(c)) {
            fputc(c, outputFile); // Preserva los espacios en blanco
            continue;
        }

        if (isalpha(c)) {
            i = 0;
            do {
                lexema[i++] = c;
                c = fgetc(f);
            } while (isalnum(c) || c == '_');

            lexema[i] = 0;
            
            ungetc(c, f);
            i = esPalabraReservada();
            if (i >= 0) {
                writeToken(tokenNames[i - 256 ]);
                return i;
            }
            writeToken("ID");
            return ID;
        }

        if (isdigit(c)) {
            i = 0;
            do {
                lexema[i++] = c;
                c = fgetc(f);
            } while (isdigit(c));

            lexema[i] = 0;
            ungetc(c, f);
            writeToken("NUM");
            return NUM;
        }

        switch (c) {
            case ';': case '(': case ')': case ',': case '{': case '}': case '[': case ']':
            case '+': case '-': case '*': case '/': case '<': case '>': case '=': case '!': case ':':
                {
                    int next = fgetc(f);
                    if (c == '>' && next == '=') {
                        writeToken("MAYORIGUAL");
                        return MAYORIGUAL;
                    }
                    if (c == '<' && next == '=') {
                        writeToken("MENORIGUAL");
                        return MENORIGUAL;
                    }
                    if (c == '=' && next == '=') {
                        writeToken("IGUAL");
                        return IGUAL;
                    }
                    if (c == '!' && next == '=') {
                        writeToken("DIFERENTE");
                        return DIFERENTE;
                    }
                    if (c == ':' && next == ':') {
                        writeToken("DOS_PUNTOS_DOS_PUNTOS");
                        return DOS_PUNTOS_DOS_PUNTOS;
                    }
                    if (c == '-' && next == '>') {
                        writeToken("FLECHA_FUNCION");
                        return FLECHA_FUNCION;
                    }
                    ungetc(next, f);

                    // Manejo seguro de caracteres individuales
                    if (c >= 0 && c <= 255) {
                        char singleToken[2] = {static_cast<char>(c), '\0'};
                        writeToken(singleToken);
                    } else {
                        char singleToken[2] = {'?', '\0'};
                        writeToken(singleToken);
                    }
                    return c;
                }
        }
    }
    return EOF;
}
int esPalabraReservada() {
    if (strcmp(lexema, "let") == 0) return LET;
    if (strcmp(lexema, "in") == 0) return IN;
    if (strcmp(lexema, "if") == 0) return IF;
    if (strcmp(lexema, "then") == 0) return THEN;
    if (strcmp(lexema, "else") == 0) return ELSE;
    if (strcmp(lexema, "case") == 0) return CASE;
    if (strcmp(lexema, "of") == 0) return OF;
    if (strcmp(lexema, "\\") == 0) return LAMBDA;
    if (strcmp(lexema, "where") == 0) return WHERE;
    if (strcmp(lexema, "do") == 0) return DO;
    if (strcmp(lexema, "deriving") == 0) return DERIVING;
    if (strcmp(lexema, "class") == 0) return CLASS;
    if (strcmp(lexema, "instance") == 0) return INSTANCE;
    if (strcmp(lexema, "type") == 0) return TYPE;
    if (strcmp(lexema, "module") == 0) return MODULE;
    if (strcmp(lexema, "newtype") == 0) return NEWTYPE;
    if (strcmp(lexema, "default") == 0) return DEFAULT;
    if (strcmp(lexema, "import") == 0) return IMPORT;
    if (strcmp(lexema, "infix") == 0) return INFIX;
    if (strcmp(lexema, "infixl") == 0) return INFIXL;
    if (strcmp(lexema, "infixr") == 0) return INFIXR;
    if (strcmp(lexema, "foreign") == 0) return FOREIGN;
    if (strcmp(lexema, "forall") == 0) return FORALL;
    if (strcmp(lexema, "mdo") == 0) return MDO;
    if (strcmp(lexema, "rec") == 0) return REC;
    if (strcmp(lexema, "proc") == 0) return PROC;
    return -1;
}
void mostrar(int token) {
    switch (token) {
        case ID:                    printf("token = ID [%s] \n", lexema); break;
        case NUM:                   printf("token = NUM [%s] \n", lexema); break;
        case LET:                   printf("token = LET [%s] \n", lexema); break;
        case IN:                    printf("token = IN [%s] \n", lexema); break;
        case IF:                    printf("token = IF [%s] \n", lexema); break;
        case THEN:                  printf("token = THEN [%s] \n", lexema); break;
        case ELSE:                  printf("token = ELSE [%s] \n", lexema); break;
        case CASE:                  printf("token = CASE [%s] \n", lexema); break;
        case OF:                    printf("token = OF [%s] \n", lexema); break;
        case LAMBDA:                printf("token = LAMBDA [%s] \n", lexema); break;
        case WHERE:                 printf("token = WHERE [%s] \n", lexema); break;
        case DO:                    printf("token = DO [%s] \n", lexema); break;
        case DERIVING:              printf("token = DERIVING [%s] \n", lexema); break;
        case CLASS:                 printf("token = CLASS [%s] \n", lexema); break;
        case INSTANCE:              printf("token = INSTANCE [%s] \n", lexema); break;
        case TYPE:                  printf("token = TYPE [%s] \n", lexema); break;
        case MODULE:                printf("token = MODULE [%s] \n", lexema); break;
        case NEWTYPE:               printf("token = NEWTYPE [%s] \n", lexema); break;
        case DEFAULT:               printf("token = DEFAULT [%s] \n", lexema); break;
        case IMPORT:                printf("token = IMPORT [%s] \n", lexema); break;
        case INFIX:                 printf("token = INFIX [%s] \n", lexema); break;
        case INFIXL:                printf("token = INFIXL [%s] \n", lexema); break;
        case INFIXR:                printf("token = INFIXR [%s] \n", lexema); break;
        case FOREIGN:               printf("token = FOREIGN [%s] \n", lexema); break;
        case FORALL:                printf("token = FORALL [%s] \n", lexema); break;
        case MDO:                   printf("token = MDO [%s] \n", lexema); break;
        case REC:                   printf("token = REC [%s] \n", lexema); break;
        case PROC:                  printf("token = PROC [%s] \n", lexema); break;
        case PARI:                  printf("token = PARI [%c] \n", token); break;
        case PARD:                  printf("token = PARD [%c] \n", token); break;
        case MAYOR:                 printf("token = MAYOR [%c] \n", token); break;
        case PUNTOYCOMA:            printf("token = PUNTOYCOMA [%c] \n", token); break;
        case ASIG:                  printf("token = ASIG [%c] \n", token); break;
        case IGUAL:                 printf("token = IGUAL [%s] \n", lexema); break;
        case DIFERENTE:             printf("token = DIFERENTE [%s] \n", lexema); break;
        case MENOR:                 printf("token = MENOR [%c] \n", token); break;
        case MENORIGUAL:            printf("token = MENORIGUAL [%s] \n", lexema); break;
        case CORCHETEI:             printf("token = CORCHETEI [%c] \n", token); break;
        case CORCHETED:             printf("token = CORCHETED [%c] \n", token); break;
        case LLAVEI:                printf("token = LLAVEI [%c] \n", token); break;
        case LLAVED:                printf("token = LLAVED [%c] \n", token); break;
        case COMA:                  printf("token = COMA [%c] \n", token); break;
        case SUMA:                  printf("token = SUMA [%c] \n", token); break;
        case RESTA:                 printf("token = RESTA [%c] \n", token); break;
        case DIV:                   printf("token = DIV [%c] \n", token); break;
        case MULT:                  printf("token = MULT [%c] \n", token); break;
        case DOS_PUNTOS_DOS_PUNTOS: printf("token = DOS_PUNTOS_DOS_PUNTOS [%s] \n", lexema); break;
        case FLECHA_FUNCION:        printf("token = FLECHA_FUNCION [%s] \n", lexema); break;
        case FLECHA_TIPO:           printf("token = FLECHA_TIPO [%s] \n", lexema); break;
        default:                    printf("no existe");
    }
}
