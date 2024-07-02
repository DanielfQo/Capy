# Nombre del ejecutable
TARGET = capy

# Compilador
CC = g++

# Opciones de compilación
CFLAGS = -Wall -Wextra -std=c++11

# Archivos fuente
SOURCES = main.cpp parser.cpp lexer.cpp

# Archivos de encabezado
HEADERS = parser.h lexer.h 

# Objetos generados a partir de los archivos fuente
OBJECTS = $(SOURCES:.cpp=.o)

# Regla para construir el ejecutable
$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(TARGET)

# Regla para generar los archivos objeto
%.o: %.cpp $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

# Regla para limpiar los archivos generados
clean:
	rm -f $(OBJECTS) $(TARGET)