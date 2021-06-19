/*@ <answer>
 *
 * Nombre y Apellidos:
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <queue>

using namespace std;

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

    pelicula(int inicio, int duracion) : horaIni(inicio), horaFin(inicio + duracion) {}

    bool operator <(const pelicula& other) const{
        return horaFin > other.horaFin;
    }
};

bool resuelveCaso() {

    // leer los datos de la entrada
    int numPelis;
    std::cin >> numPelis;

    if (numPelis == 0) return false;

    std::priority_queue<pelicula> listado;

    for (int i = 0; i < numPelis; i++) {
        int h; int m; int duracion; char aux;

        std::cin >> h >> aux >> m >> duracion;

        pelicula peli((h * 60 + m), duracion);

        listado.push(peli);
    }

    int pelisVistas = 0;
    int descanso = 10;

    while (!listado.empty()) {
        pelicula aux = listado.top();
        listado.pop();
        pelisVistas++;

        while (!listado.empty() && listado.top().horaIni < aux.horaFin + descanso) {
            listado.pop();  //Se descartan las pelis que comienzan antes de acabar la actual + el descanso
        }

    }

    std::cout << pelisVistas << "\n";

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
