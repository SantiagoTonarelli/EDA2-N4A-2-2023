int lucas(int n, int a, int b) {
    int * tab = new int[n+1]();
    tab[0] = a;
    tab[1] = b;
    for (int i = 2; i <= n; i++)
    {
        tab[i] = tab[i-1] + tab[i-2];
    }
    return tab[n];
}

int F = 8;
int C = 8;

bool tengoQuePodar(candidata, mejorSolucion) {
    return mejorSolucion != NULL && candidata.length() > mejorSolucion.length();
}

bool esSolucion(fAc, cAc,  fD,  cD) {
    return fAc==fD && cAc == cD;
}

bool esMejorSolucion(candidata, mejorSolucion) {
    return mejorSolucion == NULL || candidata.length() < mejorSolucion.length()
}

bool movimientoEsValido(int nuevaF, int nuevaC, bool**muros){
    return !muros[nuevaF][nuevaC];
}

bool yaPase(int nuevaF,int nuevaC, List<Paso> *candidata){
    return candidata->existe(Paso(nuevaF, nuevaC));
}

void aplicoMovimiento(int nuevaF,int nuevaC, List<Paso> *candidata)  {
    candidata->agregar(Paso(nuevaF, nuevaC)); // agrega al final profe! 
}

void deshagoMovimiento(List<Paso> *candidata)  {
    candidata->eliminarFinal();
}


void caminoBT(int fAc,int cAc, int fD, int cD, bool** muros, List<Paso>* candidata, List<Paso>*& mejorSolucion){
    if(tengoQuePodar(candidata, mejorSolucion)) {
        if(esSolucion(fAc, cAc,  fD,  cD)) {
            if(esMejorSolucion(candidata, mejorSolucion)){
                mejorSolucion = candidata.clone();
            }
        } else {
            // recorrer todos mis movimientos
            int df[] = [-1, -1, -1,  0,  ...]
            int dc[] = [-1, 0,   1, -1, ...]
            for (int i = 0; i < 8; i++)
            {
                int nuevaF = fAc + df[i];
                int nuevaC = cAc + dc[i];
                if(movimientoEsValido(nuevaF,nuevaC,muros) && !yaPase(nuevaF,nuevaC, candidata)) {
                    aplicoMovimiento(nuevaF,nuevaC, candidata)
                    caminoBT(nuevaF, nuevaC, fD, cD, muros, candidata, mejorSolucion);
                    deshagoMovimiento(candidata)
                }
            }
        }
    }
}

List<Paso>* camino(int fO,int cO, int fD, int cD, bool** muros) {
    List<Paso> candidata = new List<paso>();
    List<Paso> mejorCandidata = NULL
    caminoBT(fO, cO,  fD,  cD, muros, candidata, mejorCandidata)
    return mejorCandidata;
}