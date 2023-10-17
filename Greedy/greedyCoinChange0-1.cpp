#include <iostream>

using namespace std;

void greedyCoinChange(int* denominations, int amount) {
    int change[4] = {0}; // Inicializamos un arreglo de tamaño 4 para las denominaciones 10, 5, 2, 1.

    for (int i = 0; i < 4; i++) {
        if (amount >= denominations[i] && change[i] == 0) {
            amount -= denominations[i];
            change[i]++;
        }
    }

    cout << "Cambio en monedas uruguayas:" << endl;
    cout << "Monedas de 10 pesos: " << change[0] << endl;
    cout << "Monedas de 5 pesos: " << change[1] << endl;
    cout << "Monedas de 2 pesos: " << change[2] << endl;
    cout << "Monedas de 1 peso: " << change[3] << endl;
}

int main() {
    int denominations[] = {10, 5, 2, 1}; // Monedas en pesos uruguayos
    int amount = 23; // Cambio deseado en pesos uruguayos

    greedyCoinChange(denominations, amount);

    return 0;
}