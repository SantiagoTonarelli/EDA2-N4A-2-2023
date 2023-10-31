#include <iostream>
using namespace std;

long long fibonacci(int n) {
    if(n <= 1) {
        return n;
    }

    long long* fib = new long long[n+1];
    fib[0] = 0;
    fib[1] = 1;

    for(int i = 2; i <= n; i++) {
        fib[i] = fib[i-1] + fib[i-2];
    }

    long long result = fib[n];
    delete[] fib; // Liberar memoria
    return result;
}

int main() {
    int n;
    cout << "Ingrese un número para calcular Fibonacci: ";
    cin >> n;

    cout << "Fibonacci(" << n << ") = " << fibonacci(n) << endl;
    return 0;
}