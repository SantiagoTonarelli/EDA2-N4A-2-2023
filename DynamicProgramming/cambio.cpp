#include <iostream>
#include <fstream>
#define INF 99999
using namespace std;

void obtenerCombinacionOptima(int **matDP, int *monedas, int cantMonedas, int cambio, int *&cantidadMonedas)
{
    int i = cantMonedas - 1;
    int j = cambio;

    for (int index = 0; index < cantMonedas; ++index)
    {
        cantidadMonedas[index] = 0;
    }

    while (j > 0)
    {
        if (i == 0 || matDP[i][j] != matDP[i - 1][j])
        {
            cantidadMonedas[i]++;
            j -= monedas[i];
        }
        else
        {
            i--;
        }
    }
}

int **cambioDP(int *&monedas, int cantMonedas, int cambio)
{

    // Creación Matriz
    int **matDP = new int *[cantMonedas];
    for (int i = 0; i < cantMonedas; i++)
    {
        matDP[i] = new int[cambio + 1];
    }

    // Primer columna
    for (int i = 0; i < cantMonedas; matDP[i++][0] = 0)
        ;
    // Primer fila
    for (int j = 1; j <= cambio; j++)
    {
        if (j % monedas[0] == 0)
        {
            matDP[0][j] = j / monedas[0];
        }
        else
        {
            matDP[0][j] = INF;
        }
    }

    // Core
    for (int i = 1; i < cantMonedas; i++)
    {
        for (int j = 1; j <= cambio; j++)
        {
            matDP[i][j] = j < monedas[i] ? matDP[i - 1][j] : min(matDP[i - 1][j], matDP[i][j - monedas[i]] + 1);
        }
    }

    // Opcional: Muestra
    cout << "\t";
    for (int j = 0; j <= cambio; j++)
    {
        cout << j << "\t";
    }
    cout << endl;

    for (int i = 0; i < cantMonedas; i++)
    {
        cout << monedas[i] << "\t";
        for (int j = 0; j <= cambio; j++)
        {
            cout << matDP[i][j] << "\t";
        }
        cout << endl;
    }

    return matDP;
}

int main()
{
    int cantMonedas;
    int cambio;

    // Sample input for testing
    cout << "Ingrese la cantidad de monedas disponibles: ";
    cin >> cantMonedas;

    int *monedas = new int[cantMonedas];
    int *cantidadMonedas = new int[cantMonedas];

    cout << "Ingrese los valores de las monedas:" << endl;
    for (int i = 0; i < cantMonedas; i++)
    {
        cin >> monedas[i];
    }

    cout << "Ingrese el valor de cambio deseado: ";
    cin >> cambio;

    int **matDP = cambioDP(monedas, cantMonedas, cambio);

    obtenerCombinacionOptima(matDP, monedas, cantMonedas, cambio, cantidadMonedas);

    cout << "Combinación óptima de monedas para el cambio:" << endl;
    for (int i = 0; i < cantMonedas; i++)
    {
        if (cantidadMonedas[i] > 0)
        {
            cout << "Moneda " << monedas[i] << ": " << cantidadMonedas[i] << " veces" << endl;
        }
    }

    delete[] monedas;
    delete[] cantidadMonedas;

    return 0;
}