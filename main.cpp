#include <iostream>
#include "grafo.hpp"

using namespace std;

int main() {

    Grafo grafo;

    grafo.lerArquivo("dados/grafo.txt");

    cout << "Programa iniciado!" << endl;

    return 0;
