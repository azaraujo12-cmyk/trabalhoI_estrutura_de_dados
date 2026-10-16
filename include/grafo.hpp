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
    vector<vector<int>> listaAdjacencia;

    public:
    Grafo();

    void lerArquivo(const string& nomeArquivo);

    void criarMatrizAdjacencia();
    void imprimirMatrizAdjacencia() const;

    void criarListaAdjacencia();
    void imprimirListaAdjacencia() const;


    int getNumeroVertices() const;
    int getNumeroArestas() const;

    void gerarEstatisticas(const string& nomeArquivoSaida);

    void buscaLargura(int verticeInicial,
                  const string& nomeArquivoSaida,
                  int representacao);

                  int calcularDistancia(int origem, int destino, int representacao);
};

#endif