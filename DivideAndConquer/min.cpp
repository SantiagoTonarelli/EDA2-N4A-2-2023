#include <iostream>

using namespace std;

int findMinDAC(int* arr, int start, int end) {
    if (start == end) {
        // Caso base: Cuando solo queda un elemento, es el mínimo.
        return arr[start];
    }

    int middle = (start + end) / 2;

    // Divide la lista en dos mitades y encuentra el mínimo en cada mitad.
    int minLeft = findMinDAC(arr, start, middle);
    int minRight = findMinDAC(arr, middle + 1, end);

    // Combina los resultados para obtener el mínimo global.
    return min(minLeft, minRight);
}

int main() {
    int arr[] = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5};
    int n = sizeof(arr) / sizeof(arr[0]);

    int minVal = findMinDAC(arr, 0, n - 1);

    cout << "El valor minimo en el arreglo es: " << minVal << endl;

    return 0;
}

