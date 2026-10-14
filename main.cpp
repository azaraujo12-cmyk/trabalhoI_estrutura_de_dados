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

    grafo.criarMatrizAdjacencia();
    grafo.imprimirMatrizAdjacencia();

    grafo.criarListaAdjacencia();
    grafo.imprimirListaAdjacencia();


    return 0;
}