#include <iostream>
#include "grafo.hpp"

using namespace std;

int main() {

    Grafo grafo;

    grafo.lerArquivo("dados/grafo.txt");

    cout << "Numero de vertices:"
    << grafo.getNumeroVertices() << endl;
    cout << "Numero de aresta:"
    << grafo.getNumeroArestas() << endl;

    return 0;
}