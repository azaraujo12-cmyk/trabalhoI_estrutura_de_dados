#include "grafo.hpp"
#include <chrono>
#include <fstream>
#include <iostream>
#include <queue>
#include <vector>

Grafo::Grafo(){
    numeroVertices = 0;
    numeroArestas = 0;
}

// lê os vertices e as arestas de um arquivo 
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

 // Le as arestas ate o final do arquivo.
while (arquivo >> origem >> destino) {
    arestas.push_back({origem, destino});
}
// calcula a quantidade total de arestas
numeroArestas = static_cast<int>(arestas.size());

arquivo.close();
}


void Grafo::criarMatrizAdjacencia() {
    // Cria uma matriz quadrada preencida por zeros
    matrizAdjacencia.assign(
        numeroVertices,
        vector<int>(numeroVertices, 0)
    );
      
    // percorre todas as arestas do grafo
     for (const auto& aresta : arestas) {
        int origem = aresta.first;
        int destino = aresta.second;

        // verifica se os vertices estão dentro do limites
        if (origem < 1 || origem > numeroVertices ||
            destino < 1 || destino > numeroVertices) {
            cout << "Erro: aresta com vertice invalido." << endl;
            matrizAdjacencia.clear();
            return;
        }
        // marca a conexão nos dois sentidos,pq o grafo e não direcionado
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

    // Imprime cada linha e cada valor da matriz
for (const auto& linha : matrizAdjacencia) {
        for (int valor : linha) {
            cout << valor << " ";
        }

        cout << endl;
    }
}


void Grafo::criarListaAdjacencia() {
    listaAdjacencia.assign(numeroVertices, vector<int>());

    // percorre todas as arestas 
    for (const auto& aresta : arestas) {
        int origem = aresta.first;
        int destino = aresta.second;

        if (origem < 1 || origem > numeroVertices ||
            destino < 1 || destino > numeroVertices) {
            cout << "Erro: aresta com vertice invalido." << endl;
            listaAdjacencia.clear();
            return;
        }

        // Adiciona os vizinhos em todos os sentidos
        listaAdjacencia[origem - 1].push_back(destino);
        listaAdjacencia[destino - 1].push_back(origem);
    }
}
// Imprimi os vizinhos de cada vertice
void Grafo::imprimirListaAdjacencia() const {
    if (numeroVertices > 0 && listaAdjacencia.empty()) {
        cout << "Lista ainda nao foi criada." << endl;
        return;
    }

    cout << "\nLista de adjacencia:\n";

// percorre todos os vertices 
    for (int i = 0; i < numeroVertices; i++) {
        cout << "Vertice " << i + 1 << ":";

       //Imprime od vizinhos do vertice atual
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

// calcula as estatisticas do grafo e salva em um aquivo 
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

    // Cria um vetor para guarda o grau de vertice
    vector<int> graus(numeroVertices, 0);
// conta as conexoes de cada vertice
    for (const auto& aresta : arestas) {
        int origem = aresta.first;
        int destino = aresta.second;

        if (origem < 1 || origem > numeroVertices ||
            destino < 1 || destino > numeroVertices) {
            cout << "Erro: aresta com vertice invalido." << endl;
            arquivoSaida.close();
            return;
        }
        // Cada aresta aumenta o grau dos dois vertices.
        graus[origem - 1]++;
        graus[destino - 1]++;
    }
       // Inicializa os graus minimo e maximo.
    int grauMinimo = graus[0];
    int grauMaximo = graus[0];
    int somaGraus = 0;
    // Encontra o menor grau, o maior grau e a soma dos graus.
    for (int grau : graus) {
        if (grau < grauMinimo) {
            grauMinimo = grau;
        }

        if (grau > grauMaximo) {
            grauMaximo = grau;
        }

        somaGraus += grau;
    }
     // Calcula o grau medio dividindo a soma pelo numero de vertices.
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

// Executa a busca em largura (BFS) e salva pai e nivel de cada vertice.
void Grafo::buscaLargura(
    int verticeInicial,
    const string& nomeArquivoSaida,
    int representacao
) {
    if (verticeInicial < 1 ||
        verticeInicial > numeroVertices) {
        cout << "Erro: vertice inicial invalido." << endl;
        return;
    }

    if (representacao != 1 && representacao != 2) {
        cout << "Erro: representacao invalida." << endl;
        return;
    }
// Confere se a matriz foi criada quando ela for utilizada.
    if (representacao == 1 && matrizAdjacencia.empty()) {
        cout << "Erro: matriz de adjacencia nao criada." << endl;
        return;
    }

    if (representacao == 2 &&
        numeroVertices > 0 && listaAdjacencia.empty()) {
        cout << "Erro: lista de adjacencia nao criada." << endl;
        return;
    }
    // Guarda o pai, o nivel e o estado de visita de cada vertice.
    vector<int> pai(numeroVertices, -1);
    vector<int> nivel(numeroVertices, -1);
    vector<bool> visitado(numeroVertices, false);
    queue<int> fila;

    int raiz = verticeInicial - 1;
 // A raiz ja foi visitada e fica no nivel zero.
    visitado[raiz] = true;
    pai[raiz] = 0;
    nivel[raiz] = 0;

    fila.push(raiz);
// Continua enquanto houver vertices na fila.
    while (!fila.empty()) {
        int atual = fila.front();
        fila.pop();
    // Percorre os vizinhos usando a matriz.
        if (representacao == 1) {
            for (int i = 0; i < numeroVertices; i++) {
                if (matrizAdjacencia[atual][i] == 1 &&
                    !visitado[i]) {
                    
                    // Marca o vizinho e registra pai e nivel.    
                    visitado[i] = true;
                    pai[i] = atual + 1;
                    nivel[i] = nivel[atual] + 1;
                    fila.push(i);
                }
            }
        }
        // Percorre os vizinhos usando a lista.
        else {
            for (int vizinho : listaAdjacencia[atual]) {
                int indice = vizinho - 1;

                if (!visitado[indice]) {
                    // Marca o vizinho e registra pai e nivel.
                    visitado[indice] = true;
                    pai[indice] = atual + 1;
                    nivel[indice] = nivel[atual] + 1;
                    fila.push(indice);
                }
            }
        }
    }
 // Abre o arquivo para salvar o resultado da BFS.
    ofstream arquivoSaida(nomeArquivoSaida);

    if (!arquivoSaida.is_open()) {
        cout << "Erro ao criar o arquivo da BFS." << endl;
        return;
    }
  // Escreve o vertice inicial e os resultados.
    arquivoSaida << "Busca em largura\n";
    arquivoSaida << "Vertice inicial: " << verticeInicial << "\n";
    arquivoSaida << "Vertice | Pai | Nivel\n";

    // Salva o pai e o nivel de cada vertice.
    for (int i = 0; i < numeroVertices; i++) {
        arquivoSaida << i + 1 << " | "
                     << pai[i] << " | "
                     << nivel[i] << "\n";
    }

    arquivoSaida.close();

    cout << "Resultado da BFS salvo em: "
         << nomeArquivoSaida << endl;
}

// Calcula a menor distancia entre dois vertices usando BFS.
int Grafo::calcularDistancia(
    int origem,
    int destino,
    int representacao
) {
     // Verifica se os vertices informados sao validos.
    if (origem < 1 || origem > numeroVertices ||
        destino < 1 || destino > numeroVertices) {
        cout << "Erro: vertice invalido." << endl;
        return -1;
    }
 // Verifica se a representacao escolhida e valida.
    if (representacao != 1 && representacao != 2) {
        cout << "Erro: representacao invalida." << endl;
        return -1;
    }
 // Verifica se a matriz esta pronta para uso.
    if (representacao == 1 && matrizAdjacencia.empty()) {
        cout << "Erro: matriz de adjacencia nao criada." << endl;
        return -1;
    }

    if (representacao == 2 &&
        numeroVertices > 0 && listaAdjacencia.empty()) {
        cout << "Erro: lista de adjacencia nao criada." << endl;
        return -1;
    }
    // Guarda a distancia de cada vertice a partir da origem.
    // -1 significa que o vertice ainda nao foi alcancado.
    vector<int> distancia(numeroVertices, -1);
    queue<int> fila;
    // Converte os vertices para indices de vetor.
    int inicio = origem - 1;
    int fim = destino - 1;
    // A distancia da origem para ela mesma e zero.
    distancia[inicio] = 0;
    fila.push(inicio);
    // Percorre o grafo usando a BFS.
    while (!fila.empty()) {
        int atual = fila.front();
        fila.pop();
     // Se chegou ao destino, retorna a distancia encontrada.
        if (atual == fim) {
            return distancia[atual];
        }
  // Procura os vizinhos usando a matriz.
        if (representacao == 1) {
            for (int i = 0; i < numeroVertices; i++) {
                if (matrizAdjacencia[atual][i] == 1 &&
                    distancia[i] == -1) {
                    distancia[i] = distancia[atual] + 1;
                    fila.push(i);
                }
            }
        }
        // Procura os vizinhos usando a lista.
        else {
            for (int vizinho : listaAdjacencia[atual]) {
                int indice = vizinho - 1;

                if (distancia[indice] == -1) {
                    distancia[indice] = distancia[atual] + 1;
                    fila.push(indice);
                }
            }
        }
    }

    return -1;
}

// teste 100

double Grafo::testarTempoBFS(int representacao, int repeticoes) {
    if (repeticoes <= 0 || numeroVertices <= 0) {
        return 0.0;
    }

    // Garante que a representacao escolhida exista.
    if (representacao == 1 && matrizAdjacencia.empty()) {
        criarMatrizAdjacencia();
    }

    if (representacao == 2 && listaAdjacencia.empty()) {
        criarListaAdjacencia();
    }

    if (representacao != 1 && representacao != 2) {
        return 0.0;
    }

    using Relogio = chrono::steady_clock;

    auto inicio = Relogio::now();

    for (int i = 0; i < repeticoes; i++) {
        int raiz = i % numeroVertices;

        vector<int> nivel(numeroVertices, -1);
        queue<int> fila;

        nivel[raiz] = 0;
        fila.push(raiz);

        while (!fila.empty()) {
            int atual = fila.front();
            fila.pop();

            if (representacao == 1) {
                for (int v = 0; v < numeroVertices; v++) {
                    if (matrizAdjacencia[atual][v] != 0 &&
                        nivel[v] == -1) {
                        nivel[v] = nivel[atual] + 1;
                        fila.push(v);
                    }
                }
            } else {
                for (int vizinho : listaAdjacencia[atual]) {
                    int v = vizinho - 1;

                    if (nivel[v] == -1) {
                        nivel[v] = nivel[atual] + 1;
                        fila.push(v);
                    }
                }
            }
        }
    }

    auto fim = Relogio::now();

    chrono::duration<double, milli> duracao = fim - inicio;

    return duracao.count() / repeticoes;
}

