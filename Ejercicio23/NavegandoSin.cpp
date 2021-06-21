/*@ <answer>
 *
 * Nombre y Apellidos: Adrian de Lucas Gomez
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <queue>
#include <limits>
#include <vector>

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

using Camino = std::deque<AristaDirigida<int>>;

class Dijkstra {
private:
    const int INF = 100000000000;
    int origen;
    std::vector<int> dist;
    std::vector<AristaDirigida<int>> ult;
    IndexPQ<int> pq;

    void relajar(AristaDirigida<int> a) {
        int v = a.desde(), w = a.hasta();
        if (dist[w] > dist[v] + a.valor()) {
            dist[w] = dist[v] + a.valor(); ult[w] = a;
            pq.update(w, dist[w]);
        }
    }

public:
    Dijkstra(DigrafoValorado<int> const& g, int orig) : origen(orig),
        dist(g.V(), INF), ult(g.V()), pq(g.V())
    {
        dist[origen] = 0;
        pq.push(origen, 0);
        while (!pq.empty()) {
            int v = pq.top().elem; pq.pop();
            for (auto a : g.ady(v))
                relajar(a);
        }
    }
    
    bool hayCamino(int v) const { return dist[v] != INF; }
    int distancia(int v) const { return dist[v]; }
    Camino camino(int v) const {
        Camino cam;
        // recuperamos el camino retrocediendo
        AristaDirigida<int> a;
        for (a = ult[v]; a.desde() != origen; a = ult[a.desde()])
            cam.push_front(a);
        cam.push_front(a);
        return cam;
    }
};

bool resuelveCaso() {

	// leer los datos de la entrada
	int paginas=0;

	std::cin >> paginas;

	if (paginas == 0)
		return false;

	DigrafoValorado<int> CaminosMinimos(paginas);

	int coste;

	vector<int> costesPaginas;

	for (int i = 0; i < paginas; i++) {
		std::cin >> coste;
		costesPaginas.push_back(coste);
	}

	int enlaces;

	std::cin >> enlaces;
	int inicio, fin, carga;

	for (int i = 0; i < enlaces; i++) {

		std::cin >> inicio >> fin >> carga;

		CaminosMinimos.ponArista(AristaDirigida<int>(inicio - 1, fin - 1, carga + costesPaginas[fin - 1]));	//Coste aristas = CosteArista normal + tiempo de la pagina a la que lleva
	}

	Dijkstra resIda(CaminosMinimos, 0);	//Calculamos los caminos minimos de origen a destino


	if (resIda.hayCamino(paginas - 1)) {
		std::cout << resIda.distancia(paginas - 1) + costesPaginas[0] << "\n";
	}
	else {
		std::cout << "IMPOSIBLE\n";
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
