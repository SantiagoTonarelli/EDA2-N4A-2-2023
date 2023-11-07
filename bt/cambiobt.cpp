#include <iostream>
using namespace std;

const int COINS[] = {1, 2, 5}; // Tipos de monedas disponibles
const int NUM_COINS = sizeof(COINS) / sizeof(COINS[0]);

// Función para imprimir una solución
void printSolution(int **solutions, int numSolutions) {
    for (int i = 0; i < numSolutions; i++) {
        cout << "Solución " << (i + 1) << ": ";
        int j = 0;
        while (solutions[i][j] != 0) {
            cout << solutions[i][j] << " ";
            j++;
        }
        cout << endl;
    }
}

// Función para encontrar todas las formas de dar cambio
void findChange(int **solutions, int *solution, int numSolutions, int coinIndex, int totalCoins, int target, int &count) {
    if (target == 0) {
        // Encontramos una solución, copiar al arreglo de soluciones
        for (int i = 0; i < totalCoins; i++) {
            solutions[count][i] = solution[i];
        }
        count++;
        return;
    }

    for (int i = coinIndex; i < NUM_COINS; i++) {
        if (COINS[i] <= target) {
            solution[totalCoins] = COINS[i];
            findChange(solutions, solution, numSolutions, i, totalCoins + 1, target - COINS[i], count);
            solution[totalCoins] = 0; // Backtrack
        }
    }
}

int main() {
    int change = 5;         // Cambio para el cual encontrar soluciones
    int numSolutions = 100; // Estimar un número máximo de soluciones
    int count = 0;          // Contador de soluciones encontradas

    // Inicialización de la matriz de soluciones
    int **solutions = new int*[numSolutions];
    for (int i = 0; i < numSolutions; i++) {
        solutions[i] = new int[change]; // Asignar espacio para una solución de longitud 'change'
        fill(solutions[i], solutions[i] + change, 0); // Inicializar con ceros
    }

    // Array para almacenar una solución temporal
    int *solution = new int[change]();
    fill(solution, solution + change, 0); // Inicializar con ceros

    // Encontrar todas las formas de dar cambio
    findChange(solutions, solution, numSolutions, 0, 0, change, count);

    // Imprimir todas las soluciones encontradas
    printSolution(solutions, count);

    // Liberar la memoria dinámica
    for (int i = 0; i < numSolutions; i++) {
        delete[] solutions[i];
    }
    delete[] solutions;
    delete[] solution;

    return 0;
}
