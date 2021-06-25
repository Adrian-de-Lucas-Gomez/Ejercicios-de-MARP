
/*@ <answer>
 *
 * Nombre y Apellidos:  Adrian de Lucas Gomez
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include "Matriz.h"
using namespace std;

// propios o los de las estructuras de datos de clase
#include <vector>
#include "EnterosInf.h"

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

EntInf resuelve(vector<int>& cortes, Matriz<EntInf>& tabla) {
    int n = cortes.size();

    for (int d = 2; d <= n; ++d) { // d = 2 porque los casos base son d = 1
        for (int i = 0; i < n - d; ++i) { // recorre elementos de diagonal
            int j = i + d;
            tabla[i][j] = Infinito;
            for (int k = i + 1; k < j; ++k) {
                EntInf temp = tabla[i][k] + tabla[k][j] + 2 * (cortes[j] - cortes[i]);
                if (temp < tabla[i][j]) {
                    tabla[i][j] = temp;
                }
            }
        }
    }
    return tabla[0][n - 1]; //De 0 a L
}


bool resuelveCaso() {

    // leer los datos de la entrada
    int longitud, cortes;
    std::cin >> longitud >> cortes;

    if (longitud == 0 && cortes == 0)  // fin de la entrada
        return false;

    vector<int> posCortes;

    posCortes.push_back(0);

    for (int i = 0; i < cortes; i++) {
        int marca;

        std::cin >> marca;

        posCortes.push_back(marca);
    }

    posCortes.push_back(longitud);

    // resolver el caso posiblemente llamando a otras funciones
    Matriz<EntInf> tabla(cortes+2, cortes+2, 0);

    EntInf resultado = resuelve(posCortes, tabla);

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