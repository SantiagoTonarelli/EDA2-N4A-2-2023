#include <iostream>

// Función auxiliar para obtener el máximo entre dos enteros
int max(int a, int b)
{
    return (a > b) ? a : b;
}

// Función para resolver el problema de la mochila con limitaciones de peso y volumen
int knapsack(int max_weight, int max_liters, int weights[], int liters[], int values[], int n)
{
    // Uso de punteros en C++ para crear una matriz tridimensional dinámica
    int ***dp = new int **[n + 1];
    for (int i = 0; i <= n; i++)
    {
        dp[i] = new int *[max_weight + 1];
        for (int w = 0; w <= max_weight; w++)
        {
            dp[i][w] = new int[max_liters + 1]();
        }
    }

    // Construir la tabla dp utilizando programación dinámica
    for (int i = 1; i <= n; i++)
    {
        for (int w = 1; w <= max_weight; w++)
        {
            for (int l = 1; l <= max_liters; l++)
            {
                if (weights[i - 1] <= w && liters[i - 1] <= l)
                {
                    dp[i][w][l] = max(values[i - 1] + dp[i - 1][w - weights[i - 1]][l - liters[i - 1]], dp[i - 1][w][l]);
                }
                else
                {
                    dp[i][w][l] = dp[i - 1][w][l];
                }
            }
        }
    }

    // Almacenar el resultado antes de liberar la memoria
    int result = dp[n][max_weight][max_liters];

    // Liberar la memoria asignada dinámicamente
    for (int i = 0; i <= n; i++)
    {
        for (int w = 0; w <= max_weight; w++)
        {
            delete[] dp[i][w];
        }
        delete[] dp[i];
    }
    delete[] dp;

    return result;
}

int main()
{
    // Datos de ejemplo para el problema de la mochila
    int weights[] = {1, 4, 3};
    int liters[] = {1, 2, 3};
    int values[] = {150, 300, 200};
    int max_weight = 5;
    int max_liters = 3;
    int n = sizeof(values) / sizeof(values[0]);

    // Llamada a la función knapsack y presentación del resultado
    std::cout << "El valor máximo alcanzable con las restricciones de peso y volumen es "
              << knapsack(max_weight, max_liters, weights, liters, values, n) << std::endl;

    return 0;
}
