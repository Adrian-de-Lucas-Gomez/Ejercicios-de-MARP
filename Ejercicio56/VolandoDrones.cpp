/*@ <answer>
 *
 * Nombre y Apellidos:  Adrian de Lucas Gomez
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <queue>
//#include <...>
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

struct dron {
    int pilasGrandes;
    int pilasChicas;
};

bool resuelveCaso() {

    // leer los datos de la entrada
    int numDrones, pilasGrandes, pilasChicas;

    std::cin >> numDrones >> pilasGrandes >> pilasChicas;

    if (!std::cin)  // fin de la entrada
        return false;

    priority_queue<int> nueveV;
    priority_queue<int> unoYmedioV;

    vector<dron> drones;

    for (int i = 0; i < pilasGrandes; i++) {
        int horasPila;

        std::cin >> horasPila;

        nueveV.push(horasPila);
    }

    for (int i = 0; i < pilasChicas; i++) {
        int horasPila;

        std::cin >> horasPila;

        unoYmedioV.push(horasPila);
    }


    // resolver el caso posiblemente llamando a otras funciones
    while (!nueveV.empty() && !unoYmedioV.empty()) {
        int numDronesAux = numDrones;

        while (numDronesAux > 0 && !nueveV.empty() && !unoYmedioV.empty()) {
            drones.push_back({ nueveV.top(), unoYmedioV.top() });
            nueveV.pop();   unoYmedioV.pop();
            numDronesAux--;
        }

        int horas = 0;
        
        while (!drones.empty()) {   //Recorremos los drones contando las horas de vuelo conseguidas
            int pilaNueve = drones.back().pilasGrandes;
            int pilaUno = drones.back().pilasChicas;

            if (pilaNueve > pilaUno) {
                nueveV.push(pilaNueve - pilaUno);
                horas += pilaUno;
            }
            else if (pilaNueve < pilaUno) {
                unoYmedioV.push(pilaUno - pilaNueve);
                horas += pilaNueve;
            }
            else {//Si son de la misma duracion ambas se desechan pero se cuentan las horas
                horas += pilaNueve; //O se suma la de uno, da igual
            }
            drones.pop_back();
        }

        std::cout << horas << " ";
    }

    std::cout << "\n";

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
