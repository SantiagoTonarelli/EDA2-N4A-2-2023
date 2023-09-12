#include <iostream>
#include <fstream>
#include "../Lista/lista.cpp"
#define INF 99999
using namespace std;

void mostrar(int *&vec, int desde, int hasta)
{
    cout << "[";
    for (size_t i = desde; i < hasta; i++)
    {
        cout << vec[i] << ", ";
    }
    cout << vec[hasta] << "]" << endl;
}

template <typename T>
void mostrarArray(T *array, int tope)
{
    cout << "[";
    for (int i = 0; i < tope - 1; i++)
    {
        cout << array[i] << ", ";
    }
    cout << array[tope - 1] << "]" << endl;
}

class Arista
{
public:
    int costo, origen, destino;
    bool existe;
    Arista(int costo, int origen, int destino) : costo(costo), origen(origen), destino(destino), existe(true) {}
    Arista(int costo) : costo(costo), existe(true) {}
    Arista() : costo(0), existe(false) {}
};

template <class T>
class Grafo
{
private:
    int cantVertices;
    int tope;
    bool esDirigido;
    T **vertices;
    Arista ***matAdy;
    Lista<int> *huecos;

    int posVertice(T origen)
    {
        for (int i = 0; i < this->tope; i++)
        {
            if (this->vertices[i] && *this->vertices[i] == origen)
            {
                return i;
            }
        }
        return -1;
    }

    void ubicarVertices(T origen, int &posOrigen, T destino, int &posDestino)
    {
        for (int i = 0; i < this->tope && (posOrigen == -1 || posDestino == -1); i++)
        {
            if (this->vertices[i] && *this->vertices[i] == origen)
            {
                posOrigen = i;
            }
            if (this->vertices[i] && *this->vertices[i] == destino)
            {
                posDestino = i;
            }
        }
    }

    int buscarElemSinIncidencias(int *cantInicidencias)
    {
        for (int i = 0; i < this->tope; i++)
        {
            if (cantInicidencias[i] == 0)
            {
                return i;
            }
        }
        return -1;
    }

    int caminoMasCortoNoPonderado(T origen, T destino)
    {
        int posOrigen = -1, posDestino = -1;
        this->ubicarVertices(origen, posOrigen, destino, posDestino);
        int *dist = new int[this->tope];
        int *ant = new int[this->tope];
        for (int i = 0; i < this->tope; dist[i] = INF, ant[i] = -1, i++)
            ;
        dist[posOrigen] = 0;
        int cantMarcados = 1;
        for (int i = 0; i < this->tope && cantMarcados < this->tope; i++)
        {
            for (int x = 0; x < this->tope; x++)
            {
                if (dist[x] == i)
                {
                    for (int y = 0; y < this->tope; y++)
                    {
                        if (dist[y] == INF && this->matAdy[x][y]->existe)
                        {
                            dist[y] = i + 1;
                            ant[y] = x;
                        }
                    }
                }
            }
        }
        mostrar(dist, 0, this->tope - 1);
        mostrar(ant, 0, this->tope - 1);
        Lista<T> *camino = new Lista<T>();
        camino->insertarPpio(destino);
        int aux = posDestino;
        while (ant[aux] != -1)
        {
            aux = ant[aux];
            camino->insertarPpio(*this->vertices[aux]);
        }
        camino->mostrar();
        return dist[posDestino];
    }
    
    void dfsRec(int pos, bool *&vis)
    {
        cout << *(this->vertices[pos]) << endl;
        vis[pos] = true;
        for (int i = 0; i < this->tope; i++)
        {
            if (this->matAdy[pos][i]->existe && !vis[i])
            {
                dfsRec(i, vis);
            }
        }
    }

public:
    Grafo(int tope, bool esDirigido)
    {
        this->tope = tope;
        this->esDirigido = esDirigido;
        this->cantVertices = 0;

        this->vertices = new T *[tope];
        for (int i = 0; i < tope; vertices[i++] = NULL)
            ;

        this->matAdy = new Arista **[tope];
        for (int i = 0; i < tope; i++)
        {
            this->matAdy[i] = new Arista *[tope];
        }

        if (esDirigido)
        {
            for (int i = 0; i < tope; i++)
            {
                for (int j = 0; j < tope; j++)
                {
                    this->matAdy[i][j] = new Arista();
                }
            }
        }
        else
        {
            for (int i = 0; i < tope; i++)
            {
                for (int j = i + 1; j < tope; j++)
                {
                    this->matAdy[i][j] = this->matAdy[j][i] = new Arista();
                }
                this->matAdy[i][i] = new Arista();
            }
        }

        this->huecos = new Lista<int>();
        for (int i = 0; i < tope; i++)
        {
            this->huecos->insertarFin(i);
        }
    }

    void agregarVertice(T vertice)
    {
        int hueco = this->huecos->obtenerPpio();
        this->huecos->borrar(hueco);
        this->vertices[hueco] = new T(vertice);
        this->cantVertices++;
    }

    void borrarVertice(T vertice)
    {
        int pos = buscarPos(vertice);
        delete this->vertices[pos];
        if (this->esDirigido)
        {
            for (int k = 0; k < tope; k++)
            {
                this->matAdy[pos][k]->existe = false;
                this->matAdy[k][pos]->existe = false;
            }
        }
        else
        {
            for (int k = 0; k < tope; k++)
            {
                this->matAdy[pos][k]->existe = false;
            }
        }

        this->huecos->insertarPpio(pos);
        this->cantVertices--;
    }

    bool existeArista(T origen, T destino)
    {
        int posOrigen = -1, posDestino = -1;
        this->ubicarVertices(origen, posOrigen, destino, posDestino);
        return this->matAdy[posOrigen][posDestino]->existe;
    }

    // Pre: !existeArista(origen)
    void agregarArista(T origen, T destino, int costo)
    {
        int posOrigen = -1, posDestino = -1;
        this->ubicarVertices(origen, posOrigen, destino, posDestino);
        this->matAdy[posOrigen][posDestino]->existe = true;
        this->matAdy[posOrigen][posDestino]->costo = costo;
    }

    Lista<T> *ordenTopologico()
    {
        Lista<T> *ot = new Lista<T>();
        // Inicializo cant incidencias
        int *cantIncidencias = new int[this->tope];
        for (int i = 0; i < this->tope; cantIncidencias[i++] = 0)
            ;
        // Recorro matriz marcando incidencias en el vector cantIncidencias
        for (int i = 0; i < this->tope; i++)
        {
            for (int j = 0; j < this->tope; j++)
            {
                if (this->matAdy[i][j]->existe)
                {
                    cantIncidencias[j]++;
                }
            }
        }
        for (int k = 0; k < this->tope; k++)
        {
            int posSinIndicencias = buscarElemSinIncidencias(cantIncidencias);
            if (posSinIndicencias == -1)
            {
                delete ot;
                return new Lista<T>();
            }
            else
            {
                ot->insertarFin(*this->vertices[posSinIndicencias]);
                cantIncidencias[posSinIndicencias] = -1;
                for (int j = 0; j < this->tope; j++)
                {
                    if (this->matAdy[posSinIndicencias][j]->existe)
                    {
                        cantIncidencias[j]--;
                    }
                }
            }
        }
        delete[] cantIncidencias;
        return ot;
    }

    void dfs(T origen)
    {
        int posOrigen = posVertice(origen);
        bool *vis = new bool[this->tope];
        for (int i = 0; i < this->tope; vis[i++] = false)
            ;
        dfsRec(posOrigen, vis);
    }

    void bfs(T origen)
    {
        int posOrigen = posVertice(origen);
        bool *vis = new bool[this->tope];
        for (int i = 0; i < this->tope; vis[i++] = false)
            ;
        Lista<int> *cola = new Lista<int>();
        cola->insertarFin(posOrigen);
        vis[posOrigen] = true;
        while (!cola->esVacia())
        {
            int pos = cola->obtenerPpio();
            cola->borrar(cola->obtenerPpio());
            cout << *(this->vertices[pos]) << endl;
            for (int i = 0; i < this->tope; i++)
            {
                if (this->matAdy[pos][i]->existe && !vis[i])
                {
                    cola->insertarFin(i);
                    vis[i] = true;
                }
            }
        }
    }
};

int main(){
    // // IMPORTANTE! BORRAR O COMENTAR LAS SIGUIENTES LINEAS  EN TODOS LOS EJERCICIOS DEL OBLIGATORIO. NO PUEDEN ESTAR EN NINGUNA ENTREGA!
    // ifstream myFile("Grafo/in.txt");
    // cin.rdbuf(myFile.rdbuf());
    // // Si desean tirar la salida a un archivo, usen las siguientes líneas (si no, sáquenlas):
    // ofstream myFile2("Grafo/out.txt");
    // cout.rdbuf(myFile2.rdbuf());
    // Crear un grafo con 5 vértices
    Grafo<int> *g = new Grafo<int>(5, false);

    // Agregar vértices al grafo
    for (int i = 1; i <= 5; i++)
    {
        g->agregarVertice(i);
    }

    // Agregar aristas entre los vértices
    g->agregarArista(1, 2, 1); // Arista entre el vértice 1 y 2 con un costo de 1
    g->agregarArista(1, 3, 1); // Arista entre el vértice 1 y 3 con un costo de 1
    g->agregarArista(2, 4, 1); // Arista entre el vértice 2 y 4 con un costo de 1
    g->agregarArista(3, 5, 1); // Arista entre el vértice 3 y 5 con un costo de 1
    g->agregarArista(4, 5, 1); // Arista entre el vértice 4 y 5 con un costo de 1

    // Llamar a las funciones dfs y bfs
    cout << "DFS desde el vertice 1:" << endl;
    g->dfs(1);

    cout << "\nBFS desde el vertice 1:" << endl;
    g->bfs(1);

    // Liberar memoria
    delete g;

    return 0;
}