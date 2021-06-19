#include <fstream>
#include <queue>
#ifndef GRAFO_H_
#define GRAFO_H_

#include <iostream>
#include <vector>
#include <iostream>
#include <stdexcept>
#include "DigrafoValorado.h"
#include "IndexPQ.h"

#endif /* GRAFO_H_ */

class RecorridoLucas {
public:
	RecorridoLucas(DigrafoValorado<int> const& g, int orig) :
		origen(orig), dist(g.V(), INF), ulti(g.V()), pq(g.V()), caminos(g.V(), 0) {

		dist[origen] = 0;
		caminos[origen] = 1;
		pq.push(origen, 0);
		while (!pq.empty()) {
			int v = pq.top().elem; pq.pop();
			for (auto a : g.ady(v))
				relajar(a);
		}
	}

	int64_t calculaCaminosPosibles(DigrafoValorado<int> const& g, int v) {
		if (!hayCamino(v)) return 0;	//Si no se puede llegar

		if (nCaminos(v) == 0) {		//Cuantos caminos hay a v
			int64_t min = distancia(v);
			for (auto a : g.ady(v)) {
				int w = a.hasta();
				if (dist[w] + a.valor() <= min) {	//Si no es el camino minimo no seguimos por ahi
					caminos[v] += calculaCaminosPosibles(g, w);		//Apuntamos los caminos que pueden llegar a w
				}
			}
		}
		return caminos[v];
	}

	bool hayCamino(int v) const { return dist[v] != INF; }
	int64_t distancia(int v) const { return dist[v]; }
	int64_t nCaminos(int v) const { return caminos[v]; }

private:
	const int INF = 1000000000;
	int origen;
	std::vector<int64_t> dist;
	std::vector<int64_t> caminos; //Caminos minimos a cada indice
	std::vector<AristaDirigida<int>> ulti;
	IndexPQ<int64_t> pq;

	void relajar(AristaDirigida<int> a) {
		int v = a.desde(), w = a.hasta();
		if (dist[w] > dist[v] + a.valor()) {
			dist[w] = dist[v] + a.valor(); ulti[w] = a;
			pq.update(w, dist[w]);
		}
	}
};

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {

	int nNodos, nAristas;
	std::cin >> nNodos;		//Las intersecciones

	if (!std::cin)  // fin de la entrada
		return false;

	std::cin >> nAristas;	//Las calles que las conectan

	DigrafoValorado<int> g(nNodos);

	for (int i = 0; i < nAristas; i++)
	{
		int u, w;	//Extremos
		int val;	//Valor de la arista
		std::cin >> u >> w >> val;

		AristaDirigida<int> a(u - 1, w - 1, val);
		g.ponArista(a);
		AristaDirigida<int> b(w - 1, u - 1, val);
		g.ponArista(b);
	}

	int consultas;
	
	RecorridoLucas mapa(g, 0);	//0 en el grafo interno y 1 en la representacion visual

	std::cout << mapa.calculaCaminosPosibles(g, nNodos - 1) << '\n';	//Caminos posibles hasta n-1 ---> el colegio

	return true;
}

int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("casos.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

	while (!std::cin.eof() && resuelveCaso());

	// para dejar todo como estaba al principio
#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	system("PAUSE");
#endif
	return 0;
}