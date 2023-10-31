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

    // Imprimir la matriz resultante
    cout << "Matriz de Programación Dinámica resultante:" << endl;
    for (int i = 0; i <= cantElementos; i++)
    {
        for (int j = 0; j <= capacidad; j++)
        {
            cout << matDP[i][j] << "\t";
        }
        cout << endl;
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
    // Predefinir la cantidad de elementos y la capacidad de la mochila.
    int cantElementos = 5;
    int capacidad = 10;

    // Crear un arreglo de punteros a Elemento con valores predefinidos.
    Elemento *elementos[] = {
        new Elemento(2, 3),
        new Elemento(3, 4),
        new Elemento(4, 5),
        new Elemento(5, 8),
        new Elemento(9, 10)
    };

    // Calcula la solución usando programación dinámica.
    int **matDP = mochilaDP(elementos, cantElementos, capacidad);

    // Obtener la combinación óptima de elementos para la mochila.
    Lista<Elemento *> *seleccionados = new Lista<Elemento *>;
    obtenerCombinacionOptima(matDP, elementos, cantElementos, capacidad, seleccionados);

    // Imprimir la combinación óptima de elementos.
    cout << "Combinación óptima de elementos para la mochila de capacidad " << capacidad << ":" << endl;
    
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
    for (int i = 0; i <= cantElementos; i++)
    {
        delete[] matDP[i];
    }
    delete[] matDP;
    delete seleccionados;

    return 0;
}

