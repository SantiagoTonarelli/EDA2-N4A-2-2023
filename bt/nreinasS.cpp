#include <iostream>
using namespace std;

void printSolution(int** board, int N) {
    static int solutionCount = 0;
    cout << "Solución #" << ++solutionCount << ":\n";
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << " " << board[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

bool isSafe(int** board, int row, int col, int N) {
    for (int i = 0; i < col; i++)
        if (board[row][i])
            return false;

    for (int i = row, j = col; i >= 0 && j >= 0; i--, j--)
        if (board[i][j])
            return false;

    for (int i = row, j = col; j >= 0 && i < N; i++, j--)
        if (board[i][j])
            return false;

    return true;
}

void solveNQUtil(int** board, int col, int N) {
    if (col == N) {
        printSolution(board, N);
        return;
    }

    for (int i = 0; i < N; i++) {
        if (isSafe(board, i, col, N)) {
            board[i][col] = 1;
            solveNQUtil(board, col + 1, N);
            board[i][col] = 0; // Backtrack
        }
    }
}

void solveNQ(int N) {
    int** board = new int*[N];
    for (int i = 0; i < N; i++) {
        board[i] = new int[N]();
    }

    solveNQUtil(board, 0, N);

    // Limpieza de la memoria asignada al tablero
    for (int i = 0; i < N; i++) {
        delete[] board[i];
    }
    delete[] board;
}

int main() {
    int N;
    cout << "Ingrese el número de reinas: ";
    cin >> N;
    solveNQ(N);
    return 0;
}