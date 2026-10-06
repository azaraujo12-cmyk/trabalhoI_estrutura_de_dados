#ifndef GRAFO_HPP
#define GRAFO_HPP

#include <vector>
#include <string>

using namespace std;

class Grafo {
private:
    int numeroVertices;

public:
    Grafo();

    void lerArquivo(const string& nomeArquivo);
};

#endif