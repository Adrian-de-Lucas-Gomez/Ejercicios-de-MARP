/*@ <answer>
 *
 * Nombre y Apellidos: Adrian de Lucas Gomez
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

struct charla {
    int horaIni;
    int horaFin;    //Inicio + duracion

    charla(int inicio, int final) : horaIni(inicio), horaFin(final) {}

};

bool operator <(const charla& a, const charla& b) {
    return  a.horaIni > b.horaIni;
}

bool resuelveCaso() {

    // leer los datos de la entrada
    int numCharlas;
    std::cin >> numCharlas;

    if (numCharlas == 0) return false;

    std::priority_queue<charla> listado;

    for (int i = 0; i < numCharlas; i++) {
        int inicio; int fin;

        std::cin >> inicio >> fin;

        charla peli(inicio, fin);

        listado.push(peli);
    }

    int amigosNecesarios = 0;

    std::priority_queue<int, std::vector<int>, std::greater<int>> libre; //Cuando estará libre la persona i

    bool nuevaPersona = true;

    while (!listado.empty()) {
        charla actual = listado.top();
        listado.pop();

        if (nuevaPersona) {
            ++amigosNecesarios;
            libre.push(actual.horaFin);
        }

        if (listado.empty()) {  //Si hemos extraido la ultima tarea
            break;
        }

        //Si la siguiente tarea acaba depues de en la que esta un compañero pues...
        if (listado.top().horaIni < libre.top()) {
            nuevaPersona = true;    //Se necesitan refuerzos
        }
        else {
            libre.pop();    //Esta charla se acaba
            libre.push(listado.top().horaFin);  //Se mete la siente a la que asistes
            nuevaPersona = false;   //No se añaden nuevos amigos
        }
    }

    std::cout << amigosNecesarios - 1 << "\n";    //Te quitamos para saber el numero de personas extra

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
