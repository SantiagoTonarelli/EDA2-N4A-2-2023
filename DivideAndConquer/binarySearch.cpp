#include <iostream>

using namespace std;

// Función para buscar un elemento en un arreglo ordenado
int binarySearch(int* arr, int start, int end, int target) {
    if (start > end) {
        return -1; // Elemento no encontrado
    }

    int middle = (start + end) / 2;

    if (arr[middle] == target) {
        return middle; // Elemento encontrado en la posición middle
    } else if (arr[middle] < target) {
        // Si el elemento está en la mitad derecha, buscar en la mitad derecha
        return binarySearch(arr, middle + 1, end, target);
    } else {
        // Si el elemento está en la mitad izquierda, buscar en la mitad izquierda
        return binarySearch(arr, start, middle - 1, target);
    }
}

int main() {
    int arr[] = {1, 3, 5, 7, 9, 11, 13, 15, 17};
    int n = sizeof(arr) / sizeof(arr[0]);
    int target = 7;

    int index = binarySearch(arr, 0, n - 1, target);

    if (index != -1) {
        cout << "El elemento " << target << " se encuentra en la posición " << index << endl;
    } else {
        cout << "El elemento " << target << " no se encuentra en el arreglo." << endl;
    }

    return 0;
}