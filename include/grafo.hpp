#ifndef GRAFO_HPP
#define GRAFO_HPP

#include <vector>
#include <string>
#include <utility>
#include <chrono>
using namespace std;

// Representa uma aresta com peso
struct Aresta {
    int origem;
    int destino;
    double peso;
};

class Grafo {
private:
// Guada a quantidade de vertices e arestas.
    int numeroVertices;
    int numeroArestas;

    // Armazena as arestas com seus pesos
    vector<Aresta> arestas;

    // Representacoes do grafo
    vector<vector<double>> matrizAdjacencia;
    vector<vector<pair<int, double>>> listaAdjacencia;


    public:
    Grafo();

    // lê os vertces e as arestas de um arquivo
    void lerArquivo(const string& nomeArquivo);

    void criarMatrizAdjacencia();
    void imprimirMatrizAdjacencia() const;

    void criarListaAdjacencia();
    void imprimirListaAdjacencia() const;


    int getNumeroVertices() const;
    int getNumeroArestas() const;

    void gerarEstatisticas(const string& nomeArquivoSaida);

// executa a busca em largura (BFS) a parti de um vertice inicial
    void buscaLargura(int verticeInicial,
                  const string& nomeArquivoSaida,
                  int representacao);

double testarTempoBFS(int representacao, int repeticoes);                  

int calcularDistancia(int origem, int destino, int representacao);

void dijkstraVetor(
    int verticeInicial,
    int representacao,
    const string& nomeArquivoSaida
);

   
};

#endif