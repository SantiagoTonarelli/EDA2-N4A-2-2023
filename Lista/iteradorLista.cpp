#include "nodoLista.cpp"

template <class T>
class IteradorLista {
    private:
        NodoLista<T> *actual, *ppio;

    public:
        IteradorLista(NodoLista<T>* ppio){
            this->actual = this->ppio = ppio;
        }

        bool hayElemento() {
            return actual != NULL;
        }

        T obtenerElemento() {
            return actual->dato;
        }

        void avanzar(){
            actual = actual->sig;
        }

        void reiniciar(){
            actual = ppio;
        }
};