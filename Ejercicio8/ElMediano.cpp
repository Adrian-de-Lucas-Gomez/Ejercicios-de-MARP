#include <vector>
#include <iostream>
#include <fstream>
#include <queue>

class ColaConMediana {
    // top es mayor
    using MinQueue = std::priority_queue<long int, std::vector<long int>, std::less<long int>>;
    // top es menor
    using MaxQueue = std::priority_queue<long int, std::vector<long int>, std::greater<long int>>;

    MinQueue min;
    MaxQueue max;   //El top de Max hará de mediana por lo general

public:
    void insetar(long int nuevo) {
        if( !max.empty() && nuevo > max.top()) {     //Si la cola de maximos no está vacia y el valor dado es mas grande
            max.push(nuevo);    //Lo metemos
        }
        else {
            min.push(nuevo);
        }

        equilibrar();
    }

    void quitarMediana() {
        if (min.size() >= max.size()) // La mediana es el valor de las colas mas grande (o el top la de mimimos en su defecto si son iguales)
            min.pop();
        else
            max.pop();
    }

    int muestraMediana() {
        if (min.size() >= max.size()) // La mediana es el valor de las colas mas grande (o el top la de mimimos en su defecto si son iguales)
            return min.top();
        else
            return max.top();
    }

    void equilibrar() {
        //Calculamos la diferencia de tamaño que hay en las colas
        long int diff = max.size() - min.size();

        if (diff > 1) { //de 2 a favor de la de maximos
            if (!max.empty()) {
                min.push(max.top());
                max.pop();
            }
        }

        else if (diff < -1) { //de 2 a favor de la de minimos
            if (!min.empty()) {
                max.push(min.top());
                min.pop();
            }
        }
    }

    bool sinElementos() {
        return min.empty() && max.empty();
    }
};

void resuelveEventos(std::vector<long int> casos) {
    ColaConMediana listaEspera;

    for (int i = 0; i < casos.size(); i++) {
        if (casos[i] == 0) { //Si el carnicero puede atender

            if (listaEspera.sinElementos()) {
                std::cout << "ECSA ";
            }
            else {
                std::cout << listaEspera.muestraMediana() << " ";
                listaEspera.quitarMediana();
            }
            
        }

        else if (casos[i] > 0) { //Si llega un nuevo cliente
            listaEspera.insetar(casos[i]);
        }
    }
    std::cout << "\n";
}

bool resuelveCaso()
{
    if (!std::cin.eof()) {
        long int eventos = 0;
        std::cin >> eventos;

        std::vector<long int> casos(eventos);
        for (int i = 0; i < eventos; i++) {
            long int aux;
            std::cin >> aux;
            casos[i] = aux;
        }

        resuelveEventos(casos);
        return true;
    }
    else return false;
}

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