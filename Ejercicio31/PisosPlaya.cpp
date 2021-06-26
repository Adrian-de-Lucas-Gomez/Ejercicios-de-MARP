// Adriรกn de Lucas Gรณmez

// Comentario general sobre la soluciรณn,
// explicando cรณmo se resuelve el problema

#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
#include <limits>

struct piso {
	long int inicio;
	long int final;

	bool operator<(const piso& otra) const {
		return final > otra.final;
	}
};
// resuelve un caso de prueba, leyendo de la entrada la
// configuraciรณn, y escribiendo la respuesta

bool solapanEdificios(piso a, piso b) {
	return a.final > b.inicio;
}

bool resuelveCaso()
{
	long int edificios;
	std::cin >> edificios;
	if (!std::cin || edificios==0)  // fin de la entrada o caso 0
		return false;

	//Colas que ordenan de mayor a menor los datos que metamos
	std::priority_queue<piso> apartamentos;		//Ordenar los edificios por su inicio

	for (int k = 0; k < edificios; k++) {	//Los edificios
		long long int inicio, final;
		std::cin >> inicio >> final;
		piso aux;
		aux.inicio = inicio;
		aux.final = final;
		apartamentos.push(aux);
	}

	long int numTuneles = 0;

	while (!apartamentos.empty()) {
		piso edif = apartamentos.top();
		apartamentos.pop();

		while(!apartamentos.empty() && solapanEdificios(edif, apartamentos.top())) {	//Si hay todavia por procesar y
			apartamentos.pop();															//Mientras solapen con el edificio de referencia...
		}

		//Este ya no ha solapado por lo tanto ponemos un tunel para los que si lo hacian
		numTuneles++;
	}
	
	std::cout << numTuneles << "\n";	//Escribimos la suma total
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