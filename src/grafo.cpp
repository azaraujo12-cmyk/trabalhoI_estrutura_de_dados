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
    
arquivo >> numeroVertices;
int origem;
int destino;

while (arquivo >> origem >> destino) {
    arestas.push_back({origem, destino});
}

numeroArestas = arestas.size();

arquivo.close();
}

int Grafo::getNumeroVertices() const {
    return numeroVertices;

}

int Grafo::getNumeroArestas() const {
    return numeroArestas;
}