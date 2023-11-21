#include <iostream>
#include <iomanip>
using namespace std;

const int N = 8; // Tamaño del tablero de ajedrez
const int movX[N] = {2, 1, -1, -2, -2, -1, 1, 2}; // Movimientos posibles en X para el caballo
const int movY[N] = {1, 2, 2, 1, -1, -2, -2, -1}; // Movimientos posibles en Y para el caballo

// Función para imprimir el tablero
void printBoard(int** board) {
    for (int x = 0; x < N; x++) {
        for (int y = 0; y < N; y++)
            cout << setw(2) << board[x][y] << " ";
        cout << endl;
    }
    cout << endl;
}

// Función para verificar si el movimiento es válido
bool isSafe(int x, int y, int** board) {
    return (x >= 0 && x < N && y >= 0 && y < N && board[x][y] == -1);
}

// Función recursiva de backtracking para el recorrido del caballo
bool solveKTUtil(int x, int y, int movei, int** board, int endX, int endY) {
    if (x == endX && y == endY) {
        return true; // Se ha llegado a la posición final, terminar
    }

    // Probar todos los movimientos posibles del caballo desde la posición actual
    for (int k = 0; k < N; k++) {
        int next_x = x + movX[k];
        int next_y = y + movY[k];
        if (isSafe(next_x, next_y, board)) {
            board[next_x][next_y] = movei;
            if (solveKTUtil(next_x, next_y, movei + 1, board, endX, endY))
                return true;
            else
                board[next_x][next_y] = -1; // Backtracking
        }
    }

    return false;
}

// Función para resolver el problema del recorrido del caballo con una posición final específica
bool solveKT(int startX, int startY, int endX, int endY) {
    int** board = new int*[N];
    for (int x = 0; x < N; x++) {
        board[x] = new int[N];
        for (int y = 0; y < N; y++)
            board[x][y] = -1; // Inicializar el tablero a -1
    }

    board[startX][startY] = 0; // Empezar desde la primera posición

    // Si se logra resolver el problema, imprimir el tablero con el recorrido
    if (solveKTUtil(startX, startY, 1, board, endX, endY)) {
        printBoard(board);
        return true;
    } else {
        cout << "La solución no existe";
        return false;
    }
}

int main() {
    int startX = 0; // Posición inicial X del caballo
    int startY = 0; // Posición inicial Y del caballo
    int endX = 7; // Posición final X deseada
    int endY = 7; // Posición final Y deseada

    if (!solveKT(startX, startY, endX, endY)) {
        return 1;
    }
    return 0;
}
