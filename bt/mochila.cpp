#include <iostream>
#include <fstream>
#include "../Lista/lista.cpp"
using namespace std;

#define INF 99999

class Elemento {
    public:
        int peso;
        double valor;
        double ratio;
        int cantidad;

        Elemento(int peso, double valor): peso(peso), valor(valor), ratio(valor/peso), cantidad(INF){}
        Elemento(int peso, double valor, int cantidad): peso(peso), valor(valor), ratio(valor/peso), cantidad(cantidad){}
};

void mochilaBT(Elemento** &elementos, int cantElementos, int capacidad, int pos, int valorActual, int* &solActual, int& valorOptimo, int*& solOptima){
    if(capacidad == 0 || pos == cantElementos){
        if(valorActual > valorOptimo){
            valorOptimo = valorActual;
            for (int i = 0; i < cantElementos; solOptima[i] = solActual[i], i++);
        }
    } else {
        mochilaBT(elementos, cantElementos, capacidad, pos+1, valorActual, solActual, valorOptimo, solOptima);
        if(capacidad >= elementos[pos]->peso){
            solActual[pos]++;
            mochilaBT(elementos, cantElementos, capacidad-elementos[pos]->peso, pos, valorActual+elementos[pos]->valor, solActual, valorOptimo, solOptima);
            solActual[pos]--;
        }
    }
}

int main() {
    // Definir la cantidad de elementos y la capacidad de la mochila
    int cantElementos = 4, capacidad = 10;

    // Crear e inicializar elementos
    Elemento** elementos = new Elemento*[cantElementos];
    elementos[0] = new Elemento(2, 100); // Peso 2, Valor 100
    elementos[1] = new Elemento(3, 120); // Peso 3, Valor 120
    elementos[2] = new Elemento(1, 60);  // Peso 1, Valor 60
    elementos[3] = new Elemento(4, 240); // Peso 4, Valor 240

    // Inicializar soluciones y valor óptimo
    int* solOptima = new int[cantElementos], *solActual = new int[cantElementos];
    int valorOptimo = -1;
    for (int i = 0; i < cantElementos; solActual[i++] = 0);

    // Ejecutar el algoritmo de backtracking
    mochilaBT(elementos, cantElementos, capacidad, 0, 0, solActual, valorOptimo, solOptima);

    // Mostrar los resultados
    if(valorOptimo != 0){
        for (int i = 0; i < cantElementos; i++) {
            if(solOptima[i] != 0) {
                cout << "Peso: " << elementos[i]->peso << " - Valor: " << elementos[i]->valor << " - Cantidad: " << solOptima[i] << endl; 
            }
        }
    }
    cout << "Valor optimo: " << valorOptimo << endl;    

    // Liberar memoria
    for (int i = 0; i < cantElementos; delete elementos[i++]);    
    delete[] elementos;
    delete[] solOptima;
    delete[] solActual;

    return 0;
}
