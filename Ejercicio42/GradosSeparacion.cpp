
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
using namespace std;

#include "Matriz.h"  // propios o los de las estructuras de datos de clase
#include "EnterosInf.h"
#include <unordered_map>

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

void Floyd(Matriz<EntInf> const& G, Matriz<EntInf>& C, Matriz<int>& A) {
	int V = G.numfils();
	C = G;
	A = Matriz<int>(V, V, -1);
	for (int i = 0; i < V; ++i) {
		for (int j = 0; j < V; ++j) {
			if (i != j && G[i][j] != Infinito)
				A[i][j] = i;
		}
	}

	for (int k = 0; k < V; ++k) {
		for (int i = 0; i < V; ++i) {
			for (int j = 0; j < V; ++j) {
				auto temp = C[i][k] + C[k][j];
				if (temp < C[i][j]) {
					if (i == j)C[i][j] = 0;
					else C[i][j] = temp;
					A[i][j] = A[k][j];
				}
			}
		}
	}
}

bool resuelve(Matriz<EntInf>& conexiones, EntInf& maxSeparacion) {
	Matriz<EntInf> C;
	Matriz<int> A;

	Floyd(conexiones, C, A);

	maxSeparacion = 0;

	for (int i = 0; i < C.numfils(); i++) {
		for (int j = 0; j < C.numcols(); j++) {
			if (i != j && C[i][j] == Infinito)	return false;	//Si no es a si mismo y vale infinito es que no están conectados
			
			else if (i != j && C[i][j] > maxSeparacion) {	//Si no es autoArista
				maxSeparacion = C[i][j];	//Calculas el máximo
			}
		}
	}

	return true;
}

bool resuelveCaso() {

	// leer los datos de la entrada
	int personas, relaciones;

	std::cin >> personas >> relaciones;

	if (!std::cin)
		return false;

	Matriz<EntInf>conexiones(personas, personas, Infinito);
	
	std::unordered_map<std::string, int> listado;
	int id = 0;

	for (int i = 0; i < relaciones; i++) {
		string persona1, persona2;

		cin >> persona1 >> persona2;

		if (listado.find(persona1) == listado.end()) {	//Si no está en la lista
			listado.insert({ persona1, id });
			id++;
		}

		if (listado.find(persona2) == listado.end()) {	//Si no está en la lista
			listado.insert({ persona2, id });
			id++;
		}

		int a = listado.at(persona1);
		int b = listado.at(persona2);

		conexiones[a][b] = 1;	//Conectados directamente por lo que la distancia es 1

		conexiones[b][a] = 1;	//A la inversa tambien tienen conexion
		
	}

	EntInf maxSeparacion;

	bool conectados = resuelve(conexiones, maxSeparacion);
	
	// escribir la solución

	if (conectados) {
		std::cout << maxSeparacion << "\n";
	}
	else {
		std::cout << "DESCONECTADA\n";
	}

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