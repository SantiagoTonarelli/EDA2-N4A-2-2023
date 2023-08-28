#include <iostream>
#include <fstream>

using namespace std;

// método burbuja
void sort(int *v, int n) 
{
    for (int i = 0; i < n; i++) 
    {
        for (int j = i + 1; j < n; j++) 
        {
            if (v[j] < v[i]) 
            {
                int aux = v[i];
                v[i] = v[j];
                v[j] = aux;
            }
        }
    }
}

int main () 
{
    // IMPORTANTE! BORRAR O COMENTAR LAS SIGUIENTES LINEAS  EN TODOS LOS EJERCICIOS DEL OBLIGATORIO. NO PUEDEN ESTAR EN NINGUNA ENTREGA!
    ifstream myFile("Practico-1-0\\Pruebas\\casos\\1000.in.txt");
    cin.rdbuf(myFile.rdbuf());
    // Si desean tirar la salida a un archivo, usen las siguientes líneas (si no, sáquenlas):
    ofstream myFile2("Practico-1-0\\Pruebas\\casos\\1000.out.txt");
    cout.rdbuf(myFile2.rdbuf());

    int n;
    cin >> n;

    int *vec = new int[n];

    for (int i = 0; i < n; i++) 
    {
        cin >> vec[i];
    }

    sort(vec, n);

    for (int i = 0; i < n; i++) 
    {
        cout << vec[i] << " ";
    }

    return 0;
}