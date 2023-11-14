#include <iostream>
#include <fstream>
#include "../Lista/lista.cpp" // Asegúrate de que el path es correcto
using namespace std;

#define INF 99999

class Elemento
{
public:
    int peso;
    double valor;
    double ratio;
    int cantidad;

    Elemento(int peso, double valor) : peso(peso), valor(valor), ratio(valor / peso), cantidad(INF) {}
    Elemento(int peso, double valor, int cantidad) : peso(peso), valor(valor), ratio(valor / peso), cantidad(cantidad) {}
};

void mochilaBT(Elemento **&elementos, int cantElementos, int capacidad, int pos, int valorActual, int *solActual, Lista<int *> *&solucionesOptimas, int &valorOptimo)
{
    if (capacidad == 0 || pos == cantElementos)
    {
        if (valorActual > valorOptimo)
        {
            valorOptimo = valorActual;
            solucionesOptimas->vaciar();
            int *nuevaSolucion = new int[cantElementos];
            copy(solActual, solActual + cantElementos, nuevaSolucion);
            solucionesOptimas->insertarFin(nuevaSolucion);
        }
        else if (valorActual == valorOptimo)
        {
            int *nuevaSolucion = new int[cantElementos];
            copy(solActual, solActual + cantElementos, nuevaSolucion);
            solucionesOptimas->insertarFin(nuevaSolucion);
        }
    }
    else
    {
        mochilaBT(elementos, cantElementos, capacidad, pos + 1, valorActual, solActual, solucionesOptimas, valorOptimo);
        if (capacidad >= elementos[pos]->peso)
        {
            solActual[pos]++;
            mochilaBT(elementos, cantElementos, capacidad - elementos[pos]->peso, pos, valorActual + elementos[pos]->valor, solActual, solucionesOptimas, valorOptimo);
            solActual[pos]--;
        }
    }
}

int main()
{
    int cantElementos = 4, capacidad = 10;
    Elemento **elementos = new Elemento *[cantElementos];
    elementos[0] = new Elemento(2, 100);
    elementos[1] = new Elemento(3, 120);
    elementos[2] = new Elemento(1, 60);
    elementos[3] = new Elemento(4, 240);

    int *solOptima = new int[cantElementos], *solActual = new int[cantElementos];
    int valorOptimo = -1;
    for (int i = 0; i < cantElementos; solActual[i++] = 0)
        ;

    Lista<int *> *solucionesOptimas = new Lista<int *>();
    mochilaBT(elementos, cantElementos, capacidad, 0, 0, solActual, solucionesOptimas, valorOptimo);
    
    for (IteradorLista<int *> *it = solucionesOptimas->obtenerIterador(); it->hayElemento(); it->avanzar())
    {
        int *sol = it->obtenerElemento();
        for (int i = 0; i < cantElementos; i++)
        {
            cout << "Elemento " << i << ": Cantidad = " << sol[i] << endl;
        }
        cout << "----" << endl;
        delete[] sol;
    }

    cout << "Valor optimo: " << valorOptimo << endl;

    for (int i = 0; i < cantElementos; delete elementos[i++])
        ;
    delete[] elementos;
    delete[] solOptima;
    delete[] solActual;

    return 0;
}
