#ifndef GRAFO_HPP
#define GRAFO_HPP

#include <vector>
#include <string>
#include <utility>

using namespace std;

class Grafo {
private:
    int numeroVertices;
    int numeroArestas;

    vector<pair<int, int>> arestas;
    vector<vector<int>> matrizAdjacencia;

    public:
    Grafo();

    void lerArquivo(const string& nomeArquivo);
    void criarMatrizAdjacencia();
    void imprimirMatrizAdjacencia() const;

    int getNumeroVertices() const;
    int getNumeroArestas() const;
};

#endif