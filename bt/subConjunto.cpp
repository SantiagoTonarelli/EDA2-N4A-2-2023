#include <iostream>

using namespace std;

// Función para imprimir el subconjunto
void printSubset(int subset[], int size)
{
    for (int i = 0; i < size; i++)
    {
        cout << subset[i] << " ";
    }
    cout << endl;
}

// Función de backtracking para encontrar los subconjuntos
void subsetSum(int arr[], int n, int subset[], int subsetSize, int total, int index, int sum)
{
    if (total == sum)
    {
        printSubset(subset, subsetSize);
        if (index < n)
        {
            subsetSum(arr, n, subset, subsetSize - 1, total - arr[index], index + 1, sum);
        }
    }
    else if (index < n && total <= sum)
    {

        for (int i = index; i < n; i++)
        {
            subset[subsetSize] = arr[i];
            subsetSum(arr, n, subset, subsetSize + 1, total + arr[i], i + 1, sum);
        }
    }
}

// Función para iniciar el proceso de backtracking
void findSubsets(int arr[], int n, int sum)
{
    int *subset = new int[n];
    subsetSum(arr, n, subset, 0, 0, 0, sum);
    delete[] subset;
}

int main()
{
    int arr[] = {1, 2, 3, 4, 5}; // Cambia esto por tu conjunto de números
    int sum = 6;                 // Cambia esto por tu suma objetivo
    int n = sizeof(arr) / sizeof(arr[0]);
    findSubsets(arr, n, sum);

    return 0;
}
