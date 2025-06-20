Genera un laberinto aleatorio y encuentra un camino desde la entrada hasta la salida usando BFS (búsqueda en anchura), todo gestionado con punteros.
🔍 Descripción general paso a paso
Entrada del usuario
Pide el tamaño del laberinto (una sola dimensión, es un cuadrado).

Si el usuario ingresa un número par, lo ajusta a impar automáticamente para que el laberinto tenga pasillos válidos.

Inicialización del laberinto
Crea una matriz (char**) de tamaño dimension x dimension.

Llena toda la matriz con bloques ('▢') que representan muros.

Generación del laberinto (DFS recursivo con saltos de 2)
Comienza desde la esquina superior izquierda.

Usa un algoritmo de tipo DFS (búsqueda en profundidad) que salta de dos en dos y rompe muros en el camino, formando pasillos ('.').

Esto genera un laberinto con ramas y caminos aleatorios.

Marca la entrada y la salida
Coloca 'E' en la esquina superior izquierda.

Coloca 'S' en la esquina inferior derecha.

Búsqueda de camino (BFS con punteros)
Usa una cola implementada con una lista enlazada de nodos (Nodo) para realizar BFS.

Cada nodo lleva su posición y el camino recorrido hasta él.

Recorre el laberinto desde 'E' hasta 'S', evitando muros ('▢').

Cuando encuentra 'S', devuelve el camino completo como un array de posiciones.

Marcado del camino encontrado
Recorre el camino devuelto por BFS y marca cada celda con un '*' si no es la salida.

Así se puede visualizar por dónde pasó el algoritmo.

Impresión del laberinto final
Muestra el laberinto con muros, pasillos, la entrada (E), la salida (S) y el camino (*).

Limpieza de memoria
Libera toda la memoria dinámica usada: el laberinto, los nodos y el array del camino.

🧠 Conceptos aplicados en este código
Punteros y memoria dinámica (new, delete)

Estructuras personalizadas (struct)

Algoritmos de generación y recorrido de laberintos (DFS y BFS)

Programación estructurada

Gestión manual de memoria y estructuras de datos con listas enlazadas
