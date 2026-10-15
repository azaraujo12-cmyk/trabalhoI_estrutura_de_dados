#include "grafo.hpp"

#include <fstream>
#include <iostream>

Grafo::Grafo(){
    numeroVertices = 0;
    numeroArestas = 0;
}

void Grafo::lerArquivo(const string& nomeArquivo) {

    ifstream arquivo(nomeArquivo);

    if(!arquivo.is_open()) {
        cout<< "Erro ao abrir o arquivo." << endl;
        return;
    }

    // Limpa os dados caso o arquivo seja lido novamente
    arestas.clear();
    matrizAdjacencia.clear();
    
arquivo >> numeroVertices;
int origem;
int destino;

while (arquivo >> origem >> destino) {
    arestas.push_back({origem, destino});
}

numeroArestas = static_cast<int>(arestas.size());

arquivo.close();
}

void Grafo::criarMatrizAdjacencia() {
    matrizAdjacencia.assign(
        numeroVertices,
        vector<int>(numeroVertices, 0)
    );

     for (const auto& aresta : arestas) {
        int origem = aresta.first;
        int destino = aresta.second;

        // O arquivo usa vertices de 1 ate numeroVertices.
        // Os indices do vetor comecam em zero.
        if (origem < 1 || origem > numeroVertices ||
            destino < 1 || destino > numeroVertices) {
            cout << "Erro: aresta com vertice invalido." << endl;
            matrizAdjacencia.clear();
            return;
        }
        matrizAdjacencia[origem - 1][destino - 1] = 1;
        matrizAdjacencia[destino - 1][origem - 1] = 1;
    }
}

void Grafo::imprimirMatrizAdjacencia() const {
    if (matrizAdjacencia.empty()) {
        cout << "Matriz ainda nao foi criada." << endl;
        return;
    }

    cout << "\nMatriz de adjacencia:\n";

    for (const auto& linha : matrizAdjacencia) {
        for (int valor : linha) {
            cout << valor << " ";
        }

        cout << endl;
    }
}


void Grafo::criarListaAdjacencia() {
    listaAdjacencia.assign(numeroVertices, vector<int>());

    for (const auto& aresta : arestas) {
        int origem = aresta.first;
        int destino = aresta.second;

        if (origem < 1 || origem > numeroVertices ||
            destino < 1 || destino > numeroVertices) {
            cout << "Erro: aresta com vertice invalido." << endl;
            listaAdjacencia.clear();
            return;
        }

        listaAdjacencia[origem - 1].push_back(destino);
        listaAdjacencia[destino - 1].push_back(origem);
    }
}

void Grafo::imprimirListaAdjacencia() const {
    if (numeroVertices > 0 && listaAdjacencia.empty()) {
        cout << "Lista ainda nao foi criada." << endl;
        return;
    }

    cout << "\nLista de adjacencia:\n";

    for (int i = 0; i < numeroVertices; i++) {
        cout << "Vertice " << i + 1 << ":";

        for (int vizinho : listaAdjacencia[i]) {
            cout << " " << vizinho;
        }

        cout << endl;
    }
}

int Grafo::getNumeroVertices() const {
    return numeroVertices;

}

int Grafo::getNumeroArestas() const {
    return numeroArestas;
}


void Grafo::gerarEstatisticas(const string& nomeArquivoSaida) {
    ofstream arquivoSaida(nomeArquivoSaida);

    if (!arquivoSaida.is_open()) {
        cout << "Erro ao criar o arquivo de estatisticas." << endl;
        return;
    }

    if (numeroVertices == 0) {
        arquivoSaida << "O grafo nao possui vertices." << endl;
        arquivoSaida.close();
        return;
    }

    vector<int> graus(numeroVertices, 0);

    for (const auto& aresta : arestas) {
        int origem = aresta.first;
        int destino = aresta.second;

        if (origem < 1 || origem > numeroVertices ||
            destino < 1 || destino > numeroVertices) {
            cout << "Erro: aresta com vertice invalido." << endl;
            arquivoSaida.close();
            return;
        }

        graus[origem - 1]++;
        graus[destino - 1]++;
    }

    int grauMinimo = graus[0];
    int grauMaximo = graus[0];
    int somaGraus = 0;

    for (int grau : graus) {
        if (grau < grauMinimo) {
            grauMinimo = grau;
        }

        if (grau > grauMaximo) {
            grauMaximo = grau;
        }

        somaGraus += grau;
    }

    double grauMedio =
        static_cast<double>(somaGraus) / numeroVertices;

    arquivoSaida << "Numero de vertices: "
                 << numeroVertices << endl;

    arquivoSaida << "Numero de arestas: "
                 << numeroArestas << endl;

    arquivoSaida << "Grau minimo: "
                 << grauMinimo << endl;

    arquivoSaida << "Grau maximo: "
                 << grauMaximo << endl;

    arquivoSaida << "Grau medio: "
                 << grauMedio << endl;

    arquivoSaida.close();

    cout << "\nEstatisticas salvas em: "
         << nomeArquivoSaida << endl;
}
