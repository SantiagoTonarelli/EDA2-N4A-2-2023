#include <iostream>

#define MAX 1000
long long memo[MAX];
/*
Letra del Problema:
El número de Tribonacci es similar a la serie de Fibonacci, 
pero en lugar de sumar los dos últimos números para obtener 
el siguiente, sumas los tres últimos números.

La serie comienza con T(0) = 0, T(1) = 1, T(2) = 1. 
El siguiente número en la serie es T(3) = T(2) + T(1) + T(0) = 2.
*/
long long tribonacci(int n) {
    if (n == 0) return 0;
    if (n == 1) return 1;
    if (n == 2) return 1;

    // Comprobamos si ya hemos calculado este valor antes
    if (memo[n] != -1) return memo[n];

    // Almacenamos el valor en nuestra memoria antes de devolverlo
    memo[n] = tribonacci(n - 1) + tribonacci(n - 2) + tribonacci(n - 3);
    return memo[n];
}

int main() {
    int n;
    for(int i = 0; i < MAX; i++) {
        memo[i] = -1;
    }

    std::cout << "Ingrese el valor de n: ";
    std::cin >> n;

    std::cout << "El " << n << "-ésimo número de Tribonacci es: " << tribonacci(n) << std::endl;
    return 0;
}
