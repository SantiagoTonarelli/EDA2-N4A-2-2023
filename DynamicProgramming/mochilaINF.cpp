#include <iostream>
#include "../Lista/lista.cpp"
using namespace std;

class Elemento
{
public:
    int peso;
    double valor;
    double ratio;

    Elemento(int peso, double valor) : peso(peso), valor(valor), ratio(valor / peso) {}
};

int max(int a, int b)
{
    return a >= b ? a : b;
}

int **mochilaDP(Elemento **elementos, int cantElementos, int capacidad)
{
    int **matDP = new int *[cantElementos + 1];
    for (int i = 0; i <= cantElementos; i++)
    {
        matDP[i] = new int[capacidad + 1];
        fill_n(matDP[i], capacidad + 1, 0);
    }

    for (int i = 1; i <= cantElementos; i++)
    {
        for (int j = 1; j <= capacidad; j++)
        {
            if (j < elementos[i - 1]->peso)
                matDP[i][j] = matDP[i - 1][j];
            else
                matDP[i][j] = max(matDP[i - 1][j], elementos[i - 1]->valor + matDP[i][j - elementos[i - 1]->peso]);
        }
    }

    return matDP;
}

void obtenerCombinacionOptima(int **matDP, Elemento **elementos, int cantElementos, int capacidad, Lista<Elemento *> *seleccionados)
{
    int i = cantElementos, j = capacidad;

    while (i > 0 && j > 0)
    {
        if (i == 0 || matDP[i][j] != matDP[i - 1][j])
        {
            seleccionados->insertarFin(elementos[i - 1]);
            j -= elementos[i - 1]->peso;
        }
        else
            i--;
    }
}

int main()
{
    int cantElementos;
    int capacidad;

    cout << "Ingrese la cantidad de elementos disponibles: ";
    cin >> cantElementos;

    Elemento **elementos = new Elemento *[cantElementos];

    for (int i = 0; i < cantElementos; i++)
    {
        int peso;
        double valor;
        cout << "Ingrese el peso y valor del elemento " << i + 1 << ": ";
        cin >> peso >> valor;
        elementos[i] = new Elemento(peso, valor);
    }

    cout << "Ingrese la capacidad de la mochila: ";
    cin >> capacidad;

    int **matDP = mochilaDP(elementos, cantElementos, capacidad);

    Lista<Elemento *> *seleccionados = new Lista<Elemento *>;
    obtenerCombinacionOptima(matDP, elementos, cantElementos, capacidad, seleccionados);

    cout << "Combinación óptima de elementos para la mochila:" << endl;
    int *contadorElementos = new int[cantElementos]();
    while (!seleccionados->esVacia())
    {
        Elemento *e = seleccionados->obtenerFin();
        for (int i = 0; i < cantElementos; i++)
        {
            if (elementos[i]->peso == e->peso && elementos[i]->valor == e->valor)
            {
                contadorElementos[i]++;
            }
        }
        seleccionados->borrarFin();
    }

    for (int i = 0; i < cantElementos; i++)
    {
        if (contadorElementos[i] > 0)
        {
            cout << "Elemento con peso " << elementos[i]->peso << " y valor " << elementos[i]->valor;
            cout << " se utiliza " << contadorElementos[i] << " veces." << endl;
        }
    }

    // Liberar memoria
    delete[] contadorElementos;

    for (int i = 0; i < cantElementos; i++)
    {
        delete elementos[i];
    }
    delete[] elementos;

    for (int i = 0; i <= cantElementos; i++)
    {
        delete[] matDP[i];
    }
    delete[] matDP;

    delete seleccionados;

    return 0;
}
