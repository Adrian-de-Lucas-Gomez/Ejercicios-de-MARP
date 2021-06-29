/*
 * MUY IMPORTANTE: Solo se corregirán los comentarios y el código
 * contenidos entre las etiquetas <answer> y </answer>.
 * Toda modificación fuera de esas etiquetas no será corregida.
 */

 /*@ <answer>
  *
  * Nombre y Apellidos: Adrian de Lucas Gomez
  *
  *@ </answer> */

#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <vector>
#include <queue>
#include "ConjuntosDisjuntos.h"
using namespace std;


/*@ <answer>

 Para resolver este problema he usado el TAD de conjuntos disjuntos ya que esto nos permite comprobar
 si un nodo está conectado a otro. En este caso es mucho mas eficiento ya que esto se calcula al principio y en las
 colsultas solo vemos si el nodo dado esta conectado a alguno de los supers que tenemos.

 Para evitar comparar con los supers en los que el papel vale mucho mas que en los otros el vector de supermercados se ordena de 
 mas barato a mas caro ya que es lo que nos interesa y comprobará si puede llegar a a ellos desde el nodo - 1 que nos den.

 El coste del algoritno es la suma del coste de crear los conjuntos (con compresion de caminos y union por tamaños) que es Coste O(N + M lg* N)
 segun el numero de llamadas a unir y buscar, el coste de la ordenacion de los supers O(N * log N) siendo N el numero de supers y el coste de realizar
 las consultas que esta en el orden de O(Nconsultas * log N) siendo Nconsultas las consultas que realizamos y log N el coste de la operacion buscar en
 los conjuntos disjuntos

 @ </answer> */

 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>


struct Supermercado {
    int pos;
    int precioRollo;
};

bool operator < (const Supermercado& a, const Supermercado& b) {    //Coste O(1)
    return a.precioRollo < b.precioRollo;
}

bool resuelveCaso() {   //O(N + M lg* N) + O(Nsuper * log  Nsuper) + O(Nsuper)

    // leemos la entrada
    int N, C;
    cin >> N >> C;
    if (!cin)
        return false;

    ConjuntosDisjuntos conexiones(N);

    for (int i = 0; i < C; i++) {   //Coste O(N + M lg* N)
        int a, b;

        std::cin >> a >> b;

        conexiones.unir(a - 1, b - 1);
    }

    int supermercados;

    vector<Supermercado> supers;

    std::cin >> supermercados;

    for (int i = 0; i < supermercados; i++) {   //Coste O(Nsuper)
        int pos, precio;

        std::cin >> pos >> precio;

        supers.push_back({ pos-1, precio });    

    }

    sort(supers.begin(), supers.end());     //Coste O(Nsuper * log  Nsuper)
    // leer el resto del caso y resolverlo

    int consultas;

    std::cin >> consultas;

    int precioMinimo=-1;

    for (int i = 0; i < consultas; i++) {   //O(Nconsultas * log N)
        int nodo;
        std::cin >> nodo;

        precioMinimo = -1;

        for (int j = 0; j < supers.size(); j++) {   
            if (conexiones.unidos(nodo-1, supers[j].pos)) {     //O(log N)
                precioMinimo = supers[j].precioRollo;   //O(1)
                break;
            }
        }

        // resolvemos

        if (precioMinimo >= 0) {    //O(1)
            std::cout << precioMinimo << "\n";  
        }
        else std::cout << "MENUDO MARRON\n";
    }

    cout << "---\n";
    return true;
}

//@ </answer>
//  Lo que se escriba dejado de esta línea ya no forma parte de la solución.

int main() {
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    std::ifstream in("casos2.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    // Resolvemos
    while (resuelveCaso());

    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif
    return 0;
}