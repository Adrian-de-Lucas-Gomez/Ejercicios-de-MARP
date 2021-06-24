/*@ <answer>
 *
 * Nombre y Apellidos: Adrian de Lucas Gomez
 *
 *@ </answer> */

#include <iostream>
#include <fstream>

using namespace std;

#include "EnterosInf.h"  // propios o los de las estructuras de datos de clase
#include "Matriz.h"
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

struct tesoro {
    int profundidad;
    int valor;
};

int rec_Resuelve(int i, int j, const vector<tesoro>& tesoros, Matriz<int>& tabla) {

    if (tabla[i][j] != -1) {    //Este caso ya se ha hecho
        return tabla[i][j];
    }
    else if (tesoros[i - 1].profundidad * 3 > j) {  //Si no podemos bajar a por el
        tabla[i][j] = rec_Resuelve(i-1, j, tesoros, tabla);    //La j no cambia porque no bajas a por el
    }
    else {  //Si puede bajar elegimos que nos conviene mas
        tabla[i][j] = std::max(rec_Resuelve(i - 1, j, tesoros, tabla),
            rec_Resuelve(i - 1, j - 3* tesoros[i - 1].profundidad, tesoros, tabla) + tesoros[i - 1].valor);
    }

    return tabla[i][j];
}

void encuentraSolucion(int tiempo,const vector<tesoro>& tesoros) {

    int numTesoros = tesoros.size();
    Matriz<int> tabla(numTesoros + 1, tiempo + 1, -1);

    for (int i = 0; i <= numTesoros; i++) {     //Rellenamos casos base
        tabla[i][0] = 0;    //Quedarte sin tiempo
    }
    for (int j = 0; j <= tiempo; j++) {     //Rellenamos casos base
        tabla[0][j] = 0;    //Quedarte sin objetos
    }

    int valorRecogido = rec_Resuelve(numTesoros, tiempo, tesoros, tabla);

    //Reconstruimos la solución
    vector<bool> cofresElegidos = vector<bool>(numTesoros, false);

    int i = numTesoros;
    int j = tiempo;

    int contTesoros=0;

    while (i > 0 && j > 0)
    {
        if (tabla[i][j] != tabla[i - 1][j]) {   //Pillaste ese objeto
            cofresElegidos[i - 1] = true;
            j -= 3 * tesoros[i - 1].profundidad;
            contTesoros++;
        }
        i--;
    }


    std::cout << valorRecogido << "\n";
    std::cout << contTesoros << "\n";
    for (int i = 0; i < numTesoros; i++) {
        if (cofresElegidos[i]) {
            std::cout << tesoros[i].profundidad << " " << tesoros[i].valor << "\n";
        }
    }
    std::cout << "---\n";
}

bool resuelveCaso() {

    // leer los datos de la entrada
    int tiempo, cofres;

    std::cin >> tiempo >> cofres;

    if (!std::cin)  // fin de la entrada
        return false;

    vector<tesoro> tesoros;

    for (int i = 0; i < cofres; i++) {
        int profundidad, valor;

        std::cin >> profundidad >> valor;

        tesoros.push_back({ profundidad, valor });
    }

    // resolver el caso posiblemente llamando a otras funciones
    encuentraSolucion(tiempo, tesoros);

    // escribir la solución

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