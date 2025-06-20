#include <iostream>
#include <cstdlib> // rand, srand
#include <ctime>   // time
#include <cstring> // memset

using namespace std;

int dimension;
char **laberinto;

struct Posicion
{
    int fila;
    int columna;
};

struct Nodo
{
    Posicion pos;
    Nodo *siguiente;
    Posicion *camino;
    int longitud;
};

// Función para imprimir el laberinto
void imprimir_laberinto(char **lab, int dimension)
{
    for (int i = 0; i < dimension; i++)
    {
        for (int j = 0; j < dimension; j++)
        {
            cout << lab[i][j] << ' ';
        }
        cout << endl;
    }
}

// Inicializa el laberinto con muros
char **crear_laberinto(int dimension)
{
    char **lab = new char *[dimension];
    for (int i = 0; i < dimension; i++)
    {
        lab[i] = new char[dimension];
        for (int j = 0; j < dimension; j++)
        {
            lab[i][j] = '▢';
        }
    }
    return lab;
}

// DFS con punteros
void generar_laberinto_con_ramas(char **lab, int f, int c)
{
    int direcciones[4][2] = {{0, 2}, {2, 0}, {0, -2}, {-2, 0}};
    for (int i = 0; i < 4; i++)
    {
        int r = rand() % 4;
        swap(direcciones[i], direcciones[r]);
    }

    for (int i = 0; i < 4; i++)
    {
        int nf = f + direcciones[i][0];
        int nc = c + direcciones[i][1];

        if (nf >= 0 && nf < dimension && nc >= 0 && nc < dimension && lab[nf][nc] == '▢')
        {
            lab[f + direcciones[i][0] / 2][c + direcciones[i][1] / 2] = '.';
            lab[nf][nc] = '.';
            generar_laberinto_con_ramas(lab, nf, nc);
        }
    }
}

// Verifica si una celda fue visitada
bool ya_visitado(Posicion *visitados, int cantidad, int fila, int columna)
{
    for (int i = 0; i < cantidad; i++)
    {
        if (visitados[i].fila == fila && visitados[i].columna == columna)
        {
            return true;
        }
    }
    return false;
}

// BFS con punteros
Posicion *bfs(char **lab, Posicion inicio, Posicion fin, int &longitud_camino)
{
    Nodo *frente = nullptr;
    Nodo *fondo = nullptr;

    Posicion *visitados = new Posicion[dimension * dimension];
    int cantidad_visitados = 0;

    Posicion *camino_inicial = new Posicion[1];
    camino_inicial[0] = inicio;

    Nodo *nodo_inicial = new Nodo{{inicio.fila, inicio.columna}, nullptr, camino_inicial, 1};
    frente = fondo = nodo_inicial;

    while (frente != nullptr)
    {
        Nodo *actual = frente;
        frente = frente->siguiente;

        int f = actual->pos.fila;
        int c = actual->pos.columna;

        if (ya_visitado(visitados, cantidad_visitados, f, c))
        {
            delete[] actual->camino;
            delete actual;
            continue;
        }

        visitados[cantidad_visitados++] = {f, c};

        if (lab[f][c] == 'S')
        {
            longitud_camino = actual->longitud;
            delete[] visitados;
            return actual->camino;
        }

        int desplazamientos[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
        for (int i = 0; i < 4; i++)
        {
            int nf = f + desplazamientos[i][0];
            int nc = c + desplazamientos[i][1];

            if (nf >= 0 && nf < dimension && nc >= 0 && nc < dimension &&
                (lab[nf][nc] == '.' || lab[nf][nc] == 'S'))
            {

                Posicion *nuevo_camino = new Posicion[actual->longitud + 1];
                memcpy(nuevo_camino, actual->camino, actual->longitud * sizeof(Posicion));
                nuevo_camino[actual->longitud] = {nf, nc};

                Nodo *nuevo_nodo = new Nodo{{nf, nc}, nullptr, nuevo_camino, actual->longitud + 1};

                if (fondo)
                    fondo->siguiente = nuevo_nodo;
                fondo = nuevo_nodo;
                if (!frente)
                    frente = nuevo_nodo;
            }
        }

        delete[] actual->camino;
        delete actual;
    }

    delete[] visitados;
    return nullptr;
}

// Liberar la memoria del laberinto
void liberar_laberinto(char **lab, int dimension)
{
    for (int i = 0; i < dimension; i++)
    {
        delete[] lab[i];
    }
    delete[] lab;
}

int main()
{
    srand(time(NULL));

    cout << "Ingrese el tamaño del laberinto (impar recomendado):\n";
    cin >> dimension;
    if (dimension % 2 == 0)
    {
        dimension++;
        cout << "Dimensión ajustada a " << dimension << " para garantizar estructura adecuada.\n";
    }

    laberinto = crear_laberinto(dimension);

    Posicion inicio = {0, 0};
    Posicion fin = {dimension - 1, dimension - 1};

    laberinto[inicio.fila][inicio.columna] = '.';
    generar_laberinto_con_ramas(laberinto, inicio.fila, inicio.columna);
    laberinto[inicio.fila][inicio.columna] = 'E';
    laberinto[fin.fila][fin.columna] = 'S';

    int longitud_camino = 0;
    Posicion *camino = bfs(laberinto, inicio, fin, longitud_camino);

    if (camino != nullptr)
    {
        for (int i = 1; i < longitud_camino - 1; i++)
        {
            int x = camino[i].fila;
            int y = camino[i].columna;
            if (laberinto[x][y] != 'S')
            {
                laberinto[x][y] = '*';
            }
        }
        delete[] camino;
    }
    else
    {
        cout << "No se encontró un camino.\n";
    }

    cout << "\nCamino final encontrado:\n";
    imprimir_laberinto(laberinto, dimension);

    liberar_laberinto(laberinto, dimension);
    return 0;
}
