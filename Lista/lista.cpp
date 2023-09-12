#include <iostream>
#include <fstream>
#include "nodoLista.cpp"
#include "iteradorLista.cpp"
using namespace std;

template<class T>
class Lista {
    private:
        NodoLista<T> * ppio, * fin;
        int largo;

        bool perteneceRec(T dato, NodoLista<T>* nodo){
            return nodo && (dato == nodo->dato || perteneceRec(dato, nodo->sig));
        }

        void borrarRec(T dato, NodoLista<T> *& nodo){
            if(nodo){
                if(dato == nodo->dato){
                    NodoLista<T> * aBorrar = nodo;
                    nodo = nodo->sig;
                    if(nodo){
                        nodo->ant = aBorrar->ant;
                    } else {
                        this->fin = this->fin->ant;
                        if(!this->fin){
                            this->ppio=NULL;
                        }
                    }
                    delete aBorrar;
                    this->largo--;
                } else {
                    borrarRec(dato, nodo->sig);
                }
            }
        }

        void mostrarRec(NodoLista<T> *nodo){
            if(nodo){
                cout << nodo->dato << endl;
                mostrarRec(nodo->sig);
            }
        }

        void vaciarRec(NodoLista<T>* &nodo){
            if(nodo){
                vaciarRec(nodo->sig);
                delete nodo;
                nodo=NULL;
            }
        }

    public:

        ~Lista(){
            vaciarRec(ppio);
        }

        void vaciar(){
            vaciarRec(ppio);
            largo=0;
            fin=NULL;
        }

        Lista<T>* clon(){
            Lista<T>* ret = new Lista<T>();
            NodoLista<T>* aux = ppio;
            while(aux){
                ret->insertarFin(aux->dato);
                aux = aux->sig;
            }
            return ret;
        }

        int cantidadElementos(){
            return this->largo;
        }

        bool esVacia() {
            return this->largo==0;
        }

        bool pertenece(T dato) {
            return perteneceRec(dato, this->ppio);
        }

        void insertarPpio(T dato){
            this->ppio = new NodoLista<T>(dato, NULL, this->ppio);
            if(!this->fin){
                this->fin = this->ppio;
            }
            else
            {
             }
            this->largo++;
        }

        void insertarFin(T dato){
            this->fin = new NodoLista<T>(dato, this->fin, NULL);
            if(!this->ppio){
                this->ppio = this->fin;
            }
            else
            {
                this->fin->ant->sig = this->fin;
            }
            this->largo++;
        }

        void insertarOrd(T dato, int(*fComp)(T a, T b)){
            if(!ppio || fComp(ppio->dato, dato)  >= 0){
                insertarPpio(dato);
                return;
            }
            if(fComp(dato, fin->dato) >= 0){
                insertarFin(dato);
                return;
            }
            NodoLista<T>* aux = ppio, *nuevo;
            while(fComp(aux->sig->dato, dato) < 0){
                aux = aux->sig;
            }
            nuevo = new NodoLista<T>(dato, aux, aux->sig);
            aux->sig->ant = nuevo;
            aux->sig = nuevo;
            largo++;
        }

        void borrar(T dato){
            borrarRec(dato, this->ppio);
        }

        void borrarFin(){
            this->fin = this->fin->ant;
            if(this->fin){
                delete this->fin->sig;
                this->fin->sig = NULL;
            } else {
                delete this->ppio;
                this->ppio = NULL;
            }
            this->largo--;
        }

        void mostrar(){
            mostrarRec(this->ppio);
        }

        T obtenerPpio(){
            return this->ppio->dato;
        }

        T obtenerFin(){
            return this->fin->dato;
        }

        IteradorLista<T>* obtenerIterador(){
            return new IteradorLista<T>(ppio);
        }
};

int main(){
    // IMPORTANTE! BORRAR O COMENTAR LAS SIGUIENTES LINEAS  EN TODOS LOS EJERCICIOS DEL OBLIGATORIO. NO PUEDEN ESTAR EN NINGUNA ENTREGA!
    ifstream myFile("Lista/in.txt");
    cin.rdbuf(myFile.rdbuf());
    // Si desean tirar la salida a un archivo, usen las siguientes líneas (si no, sáquenlas):
    ofstream myFile2("Lista/out.txt");
    cout.rdbuf(myFile2.rdbuf());
    
    Lista<int>* lista = new Lista<int>();
    int cantNumeros, numero;
    cin >> cantNumeros;
    for (int i = 0; i < cantNumeros; i++)
    {
        cin >> numero;
        lista->insertarFin(numero);
    }

    IteradorLista<int> * it = lista->obtenerIterador();
    while(it->hayElemento()){
        cout << it->obtenerElemento() << endl;
        it->avanzar();
    }
}
