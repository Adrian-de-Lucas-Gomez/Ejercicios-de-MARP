/*@ <answer>
 *
 * Nombre y Apellidos: Adrian de Lucas Gomez
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <queue>
#include <limits>

using namespace std;

//#include "..."  // propios o los de las estructuras de datos de clase

#include "DigrafoValorado.h"
#include "IndexPQ.h"

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================

class Dijkstra
{
public:
	Dijkstra(DigrafoValorado<int> const& g, int orig) :
		origen(orig), dist(g.V(), INF), pq(g.V()) {
		dist[origen] = 0;
		pq.push(origen, 0);
		while (!pq.empty()) {
			int v = pq.top().elem; pq.pop();
			for (auto a : g.ady(v))
				relajar(a);
		}
	}

	bool hayCamino(int v) const { return dist[v] != INF; }
	int64_t distancia(int v) const { return dist[v]; }

private:
	const int INF = 1000000000;
	int origen;
	std::vector<int> dist;
	IndexPQ<int> pq;

	void relajar(AristaDirigida<int> a) {
		int v = a.desde(), w = a.hasta();
		if (dist[w] > dist[v] + a.valor()) {
			dist[w] = dist[v] + a.valor();
			pq.update(w, dist[w]);
		}
	}
};

bool resuelveCaso() {

	// leer los datos de la entrada
	int casas;
	int conexiones;

	std::cin >> casas >> conexiones;

	if (!std::cin)
		return false;

	DigrafoValorado<int> mapaZona(casas);
	DigrafoValorado<int> mapaZonaInverso(casas);

	int inicio, fin, coste;

	for (int i = 0; i < conexiones; i++) {

		std::cin >> inicio >> fin >> coste;

		mapaZona.ponArista(AristaDirigida<int>(inicio - 1, fin - 1, coste));
		mapaZonaInverso.ponArista(AristaDirigida<int>(fin - 1, inicio - 1, coste));
	}

	int sedeMensajeria = 0;
	int nDestinos=0;
	int costeTrayectos = 0;

	cin >> sedeMensajeria >> nDestinos;

	Dijkstra resIda(mapaZona, sedeMensajeria - 1);	//Calculamos los caminos minimos desde la oficina de correos
	Dijkstra resVuelta(mapaZonaInverso, sedeMensajeria - 1);	//Calculamos las distancias minimas desde la oficina a la casa con el grafo inverso

	bool destinosAlcanzables = true;

	int casa =0;

	for (int i = 0; i < nDestinos; i++) {
		std::cin >> casa;

		if (resIda.hayCamino(casa - 1) && resVuelta.hayCamino(casa - 1)) {
			costeTrayectos += resIda.distancia(casa - 1);	//Coste de ir hasta la casa
			costeTrayectos += resVuelta.distancia(casa - 1);
		}
		else {
			destinosAlcanzables = false;
		}
	}
	//Si se pudo llegar a entregar todos los paquetes...
	if (destinosAlcanzables) {
		std::cout << costeTrayectos << "\n";
	}
	else {
		std::cout << "Imposible\n";
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
