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

int compararElementosPorRatio(Elemento* elementoA, Elemento* elementoB){
    double dif = elementoB->ratio - elementoA->ratio;
    if(dif == 0.0){
        return 0;
    } else if(dif > 0.0){
        return 1;
    } else {
        return -1;
    }
}

void problemaMochila(Elemento** elementos, int cantElementos, int capacidad){
    Lista<Elemento*> * listaElementos = new Lista<Elemento*>();
    for (int i = 0; i < cantElementos; i++)
    {
        listaElementos->insertarOrd(elementos[i], compararElementosPorRatio);
    }
    double valor = 0.0;
    for (IteradorLista<Elemento*>* it = listaElementos->obtenerIterador(); it->hayElemento() && capacidad > 0; it->avanzar())
    {
        Elemento* elem = it->obtenerElemento();
        while(capacidad >= elem->peso){
            valor += elem->valor;
            cout << "Peso: " << elem->peso << " - Valor: " << elem->valor << " - Ratio: " << elem->ratio << endl;
            capacidad -= elem->peso;
        }
    }
    cout << "Valor de la Mochila: " << valor << endl;
    cout << "Capacidad remanente: " << capacidad << endl;
    delete listaElementos;
}


int main() {
    int cantElementos = 4; // Cantidad de elementos
    Elemento** elementos = new Elemento*[cantElementos];

    // Definir elementos con sus pesos, valores y cantidad
    elementos[0] = new Elemento(10, 60, 2);
    elementos[1] = new Elemento(20, 100, 1);
    elementos[2] = new Elemento(30, 120);
    elementos[3] = new Elemento(5, 30, 3);

    int capacidad = 50; // Capacidad de la mochila

    problemaMochila(elementos, cantElementos, capacidad);

    // Liberar la memoria
    for (int i = 0; i < cantElementos; delete elementos[i++]);
    delete[] elementos;

    return 0;
}