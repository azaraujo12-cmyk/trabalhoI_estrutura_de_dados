#include <iostream>
#include "grafo.hpp"

using namespace std;

int main() {

    Grafo grafo;
    int opcao;
    int verticeInicial;
 // Le o grafo que esta salvo no arquivo.
    grafo.lerArquivo("dados/grafo.txt");

    cout << "Numero de vertices:"
    << grafo.getNumeroVertices() << endl;
    cout << "Numero de aresta:"
    << grafo.getNumeroArestas() << endl;
// Permite escolher como o grafo sera representado.
     cout << "\nEscolha a representacao do grafo:\n";
    cout << "1 - Matriz de adjacencia\n";
    cout << "2 - Lista de adjacencia\n";
    cout << "Opcao: ";
    cin >> opcao;
// Cria e imprime a representacao escolhida.
    if (opcao == 1) {
        grafo.criarMatrizAdjacencia();
        cout << "Matriz de adjacencia criada com sucesso." << endl;
       // grafo.imprimirMatrizAdjacencia();
    }
    else if (opcao == 2) {
        grafo.criarListaAdjacencia();
        cout << "Lista de adjacencia criada com sucesso." << endl;
    }
    else {
        cout << "Opcao invalida." << endl;
        return 1;
    }

    cin.ignore();
cout << "\nGrafo carregado. Consulte a memoria no Gerenciador de Tarefas.";
cout << "\nPressione ENTER para continuar...";
cin.get();

cout << "\nIniciando teste de tempo da BFS..." << endl;

double tempoLista = grafo.testarTempoBFS(2, 100);
cout << "Tempo medio da BFS usando lista: "
     << tempoLista << " ms" << endl;

double tempoMatriz = grafo.testarTempoBFS(1, 100);
cout << "Tempo medio da BFS usando matriz: "
     << tempoMatriz << " ms" << endl;

 // Calcula as estatisticas e salva em um arquivo.
    grafo.gerarEstatisticas("dados/estatisticas.txt");

    cout << "\nDigite o vertice inicial da BFS: ";
    cin >> verticeInicial;
 // Executa a busca em largura e salva os resultados.
    grafo.buscaLargura(
        verticeInicial,
        "dados/resultado_bfs.txt",
        opcao
    );

  // Declara as variaveis para calcular a distancia.   
int origem;
int destino;
 // Solicita os dois vertices para calcular a distancia.
cout << "\nDigite o vertice de origem: ";
cin >> origem;

cout << "Digite o vertice de destino: ";
cin >> destino;
// Calcula a menor distancia entre os vertices. 
int distancia = grafo.calcularDistancia(
    origem, destino, opcao
);
 // Mostra a distancia ou informa que nao existe caminho.
if (distancia >= 0) {
    cout << "Distancia entre os vertices: "
         << distancia << endl;
} else {
    cout << "Nao foi encontrado um caminho entre os vertices."
         << endl;
}

    return 0;
}