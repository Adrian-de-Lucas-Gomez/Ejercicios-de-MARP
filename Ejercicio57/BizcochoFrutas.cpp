
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


int resuelve(int i, int j, vector<int>& porciones, Matriz<int>& tabla) {
    if (i >= j-1) {  //El igual por si acaso
        return 0;
    }
    else if (i == j-1 && i != 0) {  //Si son del mismo sabor y tiene fruta
        return 1;
    }
    else if (tabla[i][j] != -1) {   //Si ya se habia resuelto
        return tabla[i][j];
    }

    int valor = 0;
    if (porciones[j] == porciones[j - 1] && porciones[j - 1] != 0) valor = 1;
    int dosDerecha = resuelve(i, j-2, porciones, tabla) + valor;

    valor = 0;
    if (porciones[i] == porciones[i+1] && porciones[i] != 0) valor = 1;
    int dosIzquierda= resuelve(i+2, j, porciones, tabla) + valor;

    valor = 0;
    if (porciones[i] == porciones[j] && porciones[i] != 0) valor = 1;
    int ambosLados = resuelve(i+1, j-1, porciones, tabla) + valor;

    tabla[i][j] = std::max( std::max(dosDerecha, dosIzquierda), ambosLados);

    return tabla[i][j];
}



bool resuelveCaso() {

    // leer los datos de la entrada
    int trozos;
    std::cin >> trozos;

    if (!std::cin)  // fin de la entrada
        return false;

    vector<int> porciones;

    for (int i = 0; i < trozos; i++) {
        int fruta;

        std::cin >> fruta;

        porciones.push_back(fruta);
    }


    // resolver el caso posiblemente llamando a otras funciones
    Matriz<int> tabla(trozos, trozos, -1);

    int resultado = resuelve(0, porciones.size()-1 , porciones, tabla);

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