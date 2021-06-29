/*@ <answer>
 *
 * Nombre y Apellidos:  Adrian de Lucas Gomez
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

struct Paciente {
    int ticketLlegada;
    string nombre;
    int gravedad;

    bool operator<(const Paciente& b) const {   //Para comprobar si tu eres de mayor prioridad que el otro
        return gravedad < b.gravedad || gravedad == b.gravedad && ticketLlegada > b.ticketLlegada;
    }
};



bool resuelveCaso() {

    // leer los datos de la entrada
    int eventos;

    std::cin >> eventos;

    if (eventos == 0)  // No se procesa
        return false;

    std::priority_queue<Paciente> colaPacientes;

    for (int i = 0; i < eventos; i++) {
        char tipoEvento;
        string nombreAux;
        int gravedadAux;

        std::cin >> tipoEvento;

        if (tipoEvento == 'I') {    //Ingresa u paciente
            std::cin >> nombreAux >> gravedadAux;

            colaPacientes.push({ i,nombreAux,gravedadAux });
        }
        else if (tipoEvento == 'A') {   //Se atiende a un paciente y se saca de la cola

            std::cout << colaPacientes.top().nombre << "\n";
            colaPacientes.pop();
        }
    }

    std::cout << "---\n";

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
