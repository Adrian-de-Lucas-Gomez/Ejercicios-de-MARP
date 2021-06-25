
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

struct festival {
    int artistas;
    int precio;

    festival(int art, int pre) : artistas(art), precio(pre) {}
};

int resuelve(int i, int j, vector<festival>& festivales, Matriz<int>& tabla) {
    if (i == 0 || j == 0) {
        return 0;
    }
    else if (tabla[i][j] != -1) {
        return tabla[i][j];
    }
    else if (festivales[i -1].precio > j) { //Si la entrada cuesta mas que lo que tenemos...
        tabla[i][j] = resuelve(i - 1, j, festivales, tabla);    //No asistimos
    }
    else {  //Si nos da el dinero para comprar la entrada
        tabla[i][j] = std::max( resuelve(i - 1, j, festivales, tabla), resuelve(i - 1, j - festivales[i-1].precio, festivales, tabla) + festivales[i - 1].artistas);
    }

    return tabla[i][j];
}

bool resuelveCaso() {

    // leer los datos de la entrada
    int dinero, festivales;
    std::cin >> dinero >> festivales;

    if (!std::cin)  // fin de la entrada
        return false;

    vector<festival> listado;

    for (int i = 0; i < festivales; i++) {
        int artistas, precio;

        std::cin >> artistas >> precio;

        listado.push_back(festival(artistas, precio));
    }


    // resolver el caso posiblemente llamando a otras funciones
    Matriz<int> tabla(festivales + 1, dinero + 1, -1);

    int resultado = resuelve(festivales, dinero, listado, tabla);

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