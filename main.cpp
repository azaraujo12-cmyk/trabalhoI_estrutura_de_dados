#include <iostream>
#include "grafo.hpp"

using namespace std;

int main() {

    Grafo grafo;
    int opcao;
    int verticeInicial;

    grafo.lerArquivo("dados/grafo.txt");

    cout << "Numero de vertices:"
    << grafo.getNumeroVertices() << endl;
    cout << "Numero de aresta:"
    << grafo.getNumeroArestas() << endl;

     cout << "\nEscolha a representacao do grafo:\n";
    cout << "1 - Matriz de adjacencia\n";
    cout << "2 - Lista de adjacencia\n";
    cout << "Opcao: ";
    cin >> opcao;

    if (opcao == 1) {
        grafo.criarMatrizAdjacencia();
        grafo.imprimirMatrizAdjacencia();
    }
    else if (opcao == 2) {
        grafo.criarListaAdjacencia();
        grafo.imprimirListaAdjacencia();
    }
    else {
        cout << "Opcao invalida." << endl;
        return 1;
    }

    grafo.gerarEstatisticas("dados/estatisticas.txt");

    cout << "\nDigite o vertice inicial da BFS: ";
    cin >> verticeInicial;

    grafo.buscaLargura(
        verticeInicial,
        "dados/resultado_bfs.txt",
        opcao
    );

    return 0;
}