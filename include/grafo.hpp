#ifndef GRAFO_HPP
#define GRAFO_HPP

#include <vector>
#include <string>

using namespace std;

class Grafo {
private:
    int numeroVertices;
    int numeroArestas;

    vector<pair<int, int>> arestas;

    public:
    Grafo();

    void lerArquivo(const string& nomeArquivo);

    int getNumeroVertices() const;
    int getNumeroArestas() const;
};

#endif