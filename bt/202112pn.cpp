struct Pos {
    int x, y;
};

const int movX[] = {2, 1, -1, -2, -2, -1, 1, 2}; // Movimientos del caballo en X
const int movY[] = {1, 2, 2, 1, -1, -2, -2, -1}; // Movimientos del caballo en Y

bool esValido(Pos p, int N, char** tablero) {
    return p.x >= 0 && p.x < N && p.y >= 0 && p.y < N && tablero[p.x][p.y] != 'B';
}

bool comerPeonNegro(Pos p, char** tablero) {
    if (tablero[p.x][p.y] == 'N') {
        tablero[p.x][p.y] = 'V'; // Comer el peón negro
        return true;
    }
    return false;
}

void backtracking(Pos actual, int N, char** tablero, int Y, int* minMovimientos, Lista<Pos>* mejorCamino, Lista<Pos>* caminoActual, int peonesComidos) {
    if (peonesComidos == Y) {
        if (caminoActual->cantidadElementos() < *minMovimientos) {
            *minMovimientos = caminoActual->cantidadElementos();
            delete mejorCamino;
            mejorCamino = caminoActual->clon();
        }
        return;
    }

    for (int i = 0; i < 8; ++i) {
        Pos nuevaPos = {actual.x + movX[i], actual.y + movY[i]};
        if (esValido(nuevaPos, N, tablero)) {
            bool comioPeon = comerPeonNegro(nuevaPos, tablero);
            caminoActual->insertarFin(nuevaPos);
            backtracking(nuevaPos, N, tablero, Y, minMovimientos, mejorCamino, caminoActual, peonesComidos + comioPeon);
            if (comioPeon) {
                tablero[nuevaPos.x][nuevaPos.y] = 'N'; // Restaurar el peón negro
            }
            caminoActual->borrarFin();
        }
    }
}

Lista<Pos>* comerPeones(int N, char** tablero, int Y, Pos posCaballo) {
    int minMovimientos = INT_MAX;
    Lista<Pos>* mejorCamino = new Lista<Pos>();
    Lista<Pos>* caminoActual = new Lista<Pos>();

    backtracking(posCaballo, N, tablero, Y, &minMovimientos, mejorCamino, caminoActual, 0);

    delete caminoActual;
    if (minMovimientos == INT_MAX) {
        delete mejorCamino;
        return nullptr;
    }
    return mejorCamino;
}

