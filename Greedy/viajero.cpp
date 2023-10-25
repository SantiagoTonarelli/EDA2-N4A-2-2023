#include <iostream>
#include <algorithm>
#include "../Lista/lista.cpp"

using namespace std;

class Destino {
public:
    double costo;
    double satisfaccion;
    double ratio;

    Destino(double costo, double satisfaccion): costo(costo), satisfaccion(satisfaccion), ratio(satisfaccion/costo){}
};

int compararDestinosPorRatio(Destino* destinoA, Destino* destinoB){
    double dif = destinoB->ratio - destinoA->ratio;
    if(dif == 0.0){
        return 0;
    } else if(dif > 0.0){
        return 1;
    } else {
        return -1;
    }
}

void viaje(Destino** destinos, int cantDestinos, double presupuesto){
    Lista<Destino*> * listaDestinos = new Lista<Destino*>();
    for (int i = 0; i < cantDestinos; i++)
    {
        listaDestinos->insertarOrd(destinos[i], compararDestinosPorRatio);
    }
    double satisfaccionTotal = 0.0;
    for (IteradorLista<Destino*>* it = listaDestinos->obtenerIterador(); it->hayElemento() && presupuesto > 0; it->avanzar())
    {
        Destino* destino = it->obtenerElemento();
        if(presupuesto >= destino->costo){
            satisfaccionTotal += destino->satisfaccion;
            cout << "Destino con costo: " << destino->costo << " y satisfaccion: " << destino->satisfaccion << endl;
            presupuesto -= destino->costo;
        }
    }
    cout << "Satisfaccion total: " << satisfaccionTotal << endl;
    cout << "Presupuesto remanente: " << presupuesto << endl;
    delete listaDestinos;
}

int main() {
    int cantDestinos = 4;
    Destino** destinos = new Destino*[cantDestinos];

    destinos[0] = new Destino(300, 90);  // Por ejemplo, Paris
    destinos[1] = new Destino(500, 150); // Por ejemplo, Nueva York
    destinos[2] = new Destino(200, 50);  // Por ejemplo, Bangkok
    destinos[3] = new Destino(400, 110); // Por ejemplo, Sydney

    double presupuesto = 700;

    viaje(destinos, cantDestinos, presupuesto);

    // Liberar memoria
    for (int i = 0; i < cantDestinos; delete destinos[i++]);
    delete[] destinos;

    return 0;
}