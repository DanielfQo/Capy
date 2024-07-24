import matplotlib.pyplot as plt

def leer_datos(archivo):
    """
    Lee los datos del archivo y devuelve dos listas: x y y.
    """
    x = []
    y = []
    with open(archivo, 'r') as f:
        for linea in f:
            partes = linea.strip().split()
            x.append(int(partes[0]))
            y.append(float(partes[1]))
    return x, y

# Leer datos de los archivos
x_pila, y_pila = leer_datos('pila.txt')
x_paralelo, y_paralelo = leer_datos('paralelo.txt')

# Verificar que ambos archivos tienen el mismo rango de x
if x_pila != x_paralelo:
    raise ValueError("Los valores de x en 'pila.txt' y 'paralelo.txt' no coinciden.")

# Crear el gráfico lineal
plt.figure(figsize=(12, 6))

# Gráfico para el método de pila
plt.plot(x_pila, y_pila, marker='o', linestyle='-', color='b', label='Método Pila')

# Gráfico para el método paralelo
plt.plot(x_paralelo, y_paralelo, marker='x', linestyle='--', color='r', label='Método Paralelo')

# Etiquetas y título
plt.xlabel('Índice')
plt.ylabel('Tiempo (segundos)')
plt.title('Comparación de Tiempos de Ejecución: Método Pila vs Paralelo')
plt.legend()
plt.grid(True)
plt.show()
