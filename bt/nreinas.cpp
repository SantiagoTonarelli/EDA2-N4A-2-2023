#include <iostream>
using namespace std;

// Función para imprimir la solución
void printSolution(int **board, int N)
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cout << " " << board[i][j] << " ";
        }
        cout << endl;
    }
}

// Función para verificar si la posición es segura para colocar una reina
bool isSafe(int **board, int row, int col, int N)
{
    int i, j;

    // Revisar esta fila a la izquierda
    for (i = 0; i < col; i++)
        if (board[row][i])
            return false;

    // Revisar la diagonal superior a la izquierda
    for (i = row, j = col; i >= 0 && j >= 0; i--, j--)
        if (board[i][j])
            return false;

    // Revisar la diagonal inferior a la izquierda
    for (i = row, j = col; j >= 0 && i < N; i++, j--)
        if (board[i][j])
            return false;

    return true;
}

// Función principal de backtracking para resolver el problema de N reinas
bool solveNQUtil(int **board, int col, int N)
{
    // Si todas las reinas están colocadas, entonces regresar verdadero
    if (col >= N)
        return true;

    // Considerar esta columna e intentar colocar esta reina en todas las filas una por una
    for (int i = 0; i < N; i++)
    {
        // Revisar si la reina puede ser colocada en board[i][col]
        if (isSafe(board, i, col, N))
        {
            // Colocar esta reina en board[i][col]
            board[i][col] = 1;

            // Recursión para colocar el resto de las reinas
            if (solveNQUtil(board, col + 1, N))
                return true;

            // Si colocar la reina en board[i][col] no conduce a una solución,
            // entonces remover la reina de board[i][col]
            board[i][col] = 0; // Backtrack
        }
    }

    // Si la reina no puede ser colocada en ninguna fila en esta columna col, entonces regresar falso
    return false;
}

// Función para resolver el problema de N reinas usando backtracking.
bool solveNQ(int N)
{
    int **board = new int *[N];
    for (int i = 0; i < N; i++)
    {
        board[i] = new int[N];
        for (int j = 0; j < N; j++)
        {
            board[i][j] = 0;
        }
    }

    if (!solveNQUtil(board, 0, N))
    {
        cout << "La solución no existe" << endl;
        return false;
    }

    printSolution(board, N);
    return true;
}

// Función main para probar el código de arriba
int main()
{
    int N; // Número de reinas
    cout << "Ingrese el número de reinas: ";
    cin >> N;
    if (!solveNQ(N))
    {
        return 1;
    }
    return 0;
}
