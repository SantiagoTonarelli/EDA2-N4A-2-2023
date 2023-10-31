#include <iostream>

long long tribonacci(int n)
{
    if (n == 0)
        return 0;
    if (n == 1)
        return 1;
    if (n == 2)
        return 1;

    return tribonacci(n - 1) + tribonacci(n - 2) + tribonacci(n - 3);
}

int main()
{
    int n;

    std::cout << "Ingrese el valor de n: ";
    std::cin >> n;

    std::cout << "El " << n << "-ésimo número de Tribonacci es: " << tribonacci(n) << std::endl;

    return 0;
}
