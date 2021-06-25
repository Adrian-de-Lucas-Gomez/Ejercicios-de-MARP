
/*@ <answer>
 *
 * Nombre y Apellidos:
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include "Matriz.h"
using namespace std;

// propios o los de las estructuras de datos de clase
#include <vector>

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

struct dir {
    int x;
    int y;

    dir(int x, int y) : x(x), y(y) {}
};

vector<dir> direcciones = { dir(-1,0), dir(0,-1) };     //Para atras o para arriba

bool posValida(int x, int y, Matriz<int>& tabla) {
    return x >= 0 && y >= 0 && x < tabla.numfils() && y < tabla.numcols();
}

int resuelve(int x, int y, vector<string>& mapa, Matriz<int>& tabla) {
    if (x < 0 || y < 0) return 0;

    else if (x == 0 && y == 0) return 1;    //Estás en la casilla de salida

    else if (tabla[x][y] != -1) {   //Caso ya calculado
        return tabla[x][y];
    }

    else if (mapa[x][y] == 'P') tabla[x][y] = 0;
    
    else {
        tabla[x][y] = resuelve(x - 1, y, mapa, tabla) + resuelve(x, y - 1, mapa, tabla);
    }
    return tabla[x][y];
}

bool resuelveCaso() {

    // leer los datos de la entrada
    int filas, columnas;
    std::cin >> filas >> columnas;

    if (!std::cin)  // fin de la entrada
        return false;

    vector<string> mapa;

    for (int i = 0; i < filas; i++) {
        string intersecciones;

        std::cin >> intersecciones;

        mapa.push_back(intersecciones);
    }

    int x = filas;
    int y = columnas;
    // resolver el caso posiblemente llamando a otras funciones
    Matriz<int> tabla(filas, columnas, -1);

    int resultado = resuelve(x-1, y-1, mapa, tabla);

    std::cout << resultado << "\n";

    return true;
}

//@ </answer>
//  Lo que se escriba dejado de esta línea ya no forma parte de la solución.

int main() {
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    while (resuelveCaso());

    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif
    return 0;
}