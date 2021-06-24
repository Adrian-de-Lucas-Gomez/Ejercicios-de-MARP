/*@ <answer>
 *
 * Nombre y Apellidos: Adrian de Lucas Gomez
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <queue>
#include <algorithm>

using namespace std;

#include "Matriz.h"
//#include "..."  // propios o los de las estructuras de datos de clase

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

struct pelicula {
    int horaIni;
    int horaFin;    //Inicio + duracion
    int duracion;

    pelicula(int inicio, int _duracion) : horaIni(inicio), horaFin(inicio + _duracion), duracion(_duracion) {}
};

bool operator <(const pelicula& a ,const pelicula& b) {
    return a.horaIni < b.horaIni;
}

int resolver(std::vector<pelicula> const& pelis) {
    int n = pelis.size();
    int T = 24 * 60 + 10; //10 minutos extra
    std::vector<int> sol(T + 1, 0);

    for (int i = n - 1; i >= 0; --i) {
        for (int j = 0; j <= T; ++j) {
            if (pelis[i].horaIni < j)
                break;
            sol[j] = std::max(sol[pelis[i].horaFin + 10] + pelis[i].duracion, sol[j]);
        }
    }
    return sol[0];
}

int resolverRec(int i, int j, const vector<pelicula>& pelis, Matriz<int>& mat)
{
    if (i >= pelis.size()) return 0;
    if (pelis[i].horaIni < j) return resolverRec(i + 1, j, pelis, mat);

    if (mat[i][j] == -1)
    {
        int noVer = resolverRec(i + 1, j, pelis, mat);
        int ver = resolverRec(i + 1, pelis[i].horaFin + 10, pelis, mat) + pelis[i].duracion;
        mat[i][j] = max(noVer, ver);
    }
    return mat[i][j];
}

bool resuelveCaso() {

    // leer los datos de la entrada
    int numPelis;
    std::cin >> numPelis;

    if (numPelis == 0) return false;

    vector<pelicula> listado;

    for (int i = 0; i < numPelis; i++) {
        int h; int m; int duracion; char aux;

        std::cin >> h >> aux >> m >> duracion;

        pelicula peli((h * 60 + m), duracion);

        listado.push_back(peli);
    }

    std::sort(listado.begin(), listado.end());   //Ordenamos el vector

    int tiempoVisto = resolver(listado);
    //Matriz<int> tabla = Matriz<int>(numPelis + 1, 60 * 24 + 1, -1);

    //int tiempoVisto = resolverRec(0, 0, listado, tabla);

    std::cout << tiempoVisto << "\n";

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
