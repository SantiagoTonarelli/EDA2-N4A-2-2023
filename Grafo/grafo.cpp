#include <iostream>
#include <fstream>
#include <string>
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

int fComp(Arista* a, Arista* b){
    return a->costo - b->costo;
}

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

    int posNoVisDeMenorCosto(int *dist, bool *vis)
    {
        int posMin = -1, min = INF;
        for (int i = 0; i < tope; i++)
        {
            if (!vis[i] && dist[i] < min)
            {
                posMin = i;
                min = dist[i];
            }
        }
        return posMin;
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
        int *cantIncidencias = new int[this->tope]();
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
                cout << "El grafo tiene ciclos" << endl;
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

    // Dijkstra es conocido por su trabajo en el diseño y análisis de algoritmos,
    // y es especialmente conocido por su algoritmo de camino más corto, que lleva su
    // nombre y es ampliamente utilizado en la búsqueda de rutas óptimas en mapas y redes.
    // También fue un pionero en el desarrollo de la programación estructurada, y es conocido
    // por haber acuñado el término "insecto" para describir un error de programación.
    void dijkstra(T origen)
    {
        int posOrigen = posVertice(origen);
        bool *vis = new bool[tope];
        int *dist = new int[tope];
        int *ant = new int[tope];

        for (int i = 0; i < tope; i++)
        {
            vis[i] = false;
            dist[i] = INF;
            ant[i] = -1;
        }

        dist[posOrigen] = 0;

        for (int i = 0; i < cantVertices; i++)
        {
            int proximoVertice = posNoVisDeMenorCosto(dist, vis);

            if (proximoVertice == -1)
            {
                break;
            }
            for (int j = 0; j < tope; j++)
            {
                if (!vis[j] && matAdy[proximoVertice][j]->existe)
                {
                    int nuevaDistancia = dist[proximoVertice] + matAdy[proximoVertice][j]->costo;
                    if (dist[j] > nuevaDistancia)
                    {
                        dist[j] = nuevaDistancia;
                        ant[j] = proximoVertice;
                    }
                }
            }
            vis[proximoVertice] = true;
        }
        cout << "Distancias" << endl;
        mostrarArray(dist, tope);
        cout << "Anteriores" << endl;
        mostrarArray(ant, tope);
        cout << "Visitados" << endl;
        mostrarArray(vis, tope);
    }

    void prim(){
        int* dist = new int[tope];
        bool* vis = new bool[tope];
        int* ant = new int[tope];
        for (int i = 0; i < tope; dist[i]=INF, vis[i]=false, ant[i]=-1, i++);
        dist[0]=0;

        for (int k = 0; k < cantVertices; k++)
        {
            int proxVertice = posNoVisDeMenorCosto(dist, vis);
            vis[proxVertice] = true;
            if(ant[proxVertice] != -1){
                cout << *vertices[ant[proxVertice]] << " --- " << *vertices[proxVertice] << endl;
            }
            for (int i = 0; i < tope; i++)
            {
                if(!vis[i] && matAdy[proxVertice][i]->existe && dist[i] > matAdy[proxVertice][i]->costo){
                    dist[i] = matAdy[proxVertice][i]->costo;
                    ant[i] = proxVertice;
                }
            }
        }
    }

    void kruskal(){
        // Se crea una lista dinámica listaAristas para almacenar todas las aristas del grafo.
        Lista<Arista* > * listaAristas = new Lista<Arista *>();
        for (int i = 0; i < tope; i++)
        {
            for (int j = 0; j < tope; j++)
            {
                if(matAdy[i][j]->existe)
                {
                    listaAristas->insertarOrd(new Arista(matAdy[i][j]->costo, i, j), fComp);
                }
            }
        }

        // Se crea un arreglo dinámico de listas para representar
        // las componentes conexas del grafo. Cada componente conexa 
        // es inicialmente un vértice individual.
        Lista<int>** compConexas = new Lista<int>*[tope];
        for (int i = 0; i < tope; i++)
        {
            compConexas[i] = new Lista<int>();
            compConexas[i]->insertarPpio(i);
        }

        int cantAristas = 0;

        // Mientras no se hayan añadido todas las aristas 
        // necesarias y aún haya aristas por procesar, se sigue el proceso.
        while(cantAristas < cantVertices-1 && !listaAristas->esVacia()){
            Arista* arista = listaAristas->obtenerPpio();
            listaAristas->borrar(arista);

            int posOrigen = -1, posDestino = -1;
            for (int i = 0; i < tope; i++)
            {
                if(compConexas[i]->pertenece(arista->origen)){
                    posOrigen = i;
                }
                if(compConexas[i]->pertenece(arista->destino)){
                    posDestino = i;
                }
            }

            // Genera ciclo? Si genera, me voy
            if(posOrigen == posDestino){
                delete arista;
                continue;
            }

            cout << *vertices[arista->origen] << " --- " << *vertices[arista->destino] << endl;
            // UNION DE COMPONENTES CONEXAS: Si la arista actual conecta dos componentes conexas 
            // diferentes, se unen en una sola componente conexa.
            for (IteradorLista<int> * it = compConexas[posDestino]->obtenerIterador(); it->hayElemento(); it->avanzar())
            {
                int posVertice = it->obtenerElemento();
                compConexas[posOrigen]->insertarFin(posVertice);
            }
            compConexas[posDestino]->vaciar();
            delete arista;
        }
        for (int i = 0; i < tope; delete compConexas[i++]);
        delete [] compConexas;

        delete listaAristas;        
    }
};

int main()
{
    // // IMPORTANTE! BORRAR O COMENTAR LAS SIGUIENTES LINEAS  EN TODOS LOS EJERCICIOS DEL OBLIGATORIO. NO PUEDEN ESTAR EN NINGUNA ENTREGA!
    // ifstream myFile("Grafo/in.txt");
    // cin.rdbuf(myFile.rdbuf());
    // // Si desean tirar la salida a un archivo, usen las siguientes líneas (si no, sáquenlas):
    // ofstream myFile2("Grafo/out.txt");
    // cout.rdbuf(myFile2.rdbuf());
    // Crear un grafo con 5 vértices

    // PRUEBA BFS Y DFS
    // Grafo<int> *g = new Grafo<int>(5, false);

    // // Agregar vértices al grafo
    // for (int i = 1; i <= 5; i++)
    // {
    //     g->agregarVertice(i);
    // }

    // // Agregar aristas entre los vértices
    // g->agregarArista(1, 2, 1); // Arista entre el vértice 1 y 2 con un costo de 1
    // g->agregarArista(1, 3, 1); // Arista entre el vértice 1 y 3 con un costo de 1
    // g->agregarArista(2, 4, 1); // Arista entre el vértice 2 y 4 con un costo de 1
    // g->agregarArista(3, 5, 1); // Arista entre el vértice 3 y 5 con un costo de 1
    // g->agregarArista(4, 5, 1); // Arista entre el vértice 4 y 5 con un costo de 1

    // // Llamar a las funciones dfs y bfs
    // cout << "DFS desde el vertice 1:" << endl;
    // g->dfs(1);

    // cout << "\nBFS desde el vertice 1:" << endl;
    // g->bfs(1);

    // // Liberar memoria
    // delete g;

    // // Crear un grafo dirigido con un tope de 5 vértices
    // Grafo<string> grafo(5, true);

    // // Agregar vértices
    // grafo.agregarVertice("A");
    // grafo.agregarVertice("B");
    // grafo.agregarVertice("C");
    // grafo.agregarVertice("D");
    // grafo.agregarVertice("E");

    // // Agregar aristas
    // // A -> B
    // grafo.agregarArista("A", "B", 1);
    // // A -> C
    // grafo.agregarArista("A", "C", 1);
    // // B -> D
    // grafo.agregarArista("B", "D", 1);
    // // C -> D
    // grafo.agregarArista("C", "D", 1);
    // // D -> E
    // grafo.agregarArista("D", "E", 1);

    // // Obtener y mostrar el orden topológico
    // Lista<string> *ordenTop = grafo.ordenTopologico();
    // cout << "Orden Topologico: ";
    // ordenTop->mostrar();

    // // Liberar memoria
    // delete ordenTop;

    // // Crear un grafo dirigido con un tope de 5 vértices
    // Grafo<string> grafoD(5, true);

    // // Agregar vértices
    // grafoD.agregarVertice("A");
    // grafoD.agregarVertice("B");
    // grafoD.agregarVertice("C");
    // grafoD.agregarVertice("D");
    // grafoD.agregarVertice("E");

    // // Agregar aristas con sus respectivos costos
    // // A -> B (costo 4)
    // grafoD.agregarArista("A", "B", 4);
    // // A -> C (costo 2)
    // grafoD.agregarArista("A", "C", 2);
    // // B -> C (costo 5)
    // grafoD.agregarArista("B", "C", 5);
    // // B -> D (costo 10)
    // grafoD.agregarArista("B", "D", 10);
    // // C -> D (costo 3)
    // grafoD.agregarArista("C", "D", 3);
    // // D -> E (costo 1)
    // grafoD.agregarArista("D", "E", 1);
    // // E -> A (costo 8)
    // grafoD.agregarArista("E", "A", 8);

    // // Ejecutar el algoritmo de Dijkstra desde el vértice "A"
    // cout << "Resultados del algoritmo de Dijkstra desde el vertice A:" << endl;
    // grafoD.dijkstra("A");

    // Crear un grafo no dirigido con un tope de 5 vértices
    Grafo<string> grafo(5, false);

    // Agregar vértices
    grafo.agregarVertice("A");
    grafo.agregarVertice("B");
    grafo.agregarVertice("C");
    grafo.agregarVertice("D");
    grafo.agregarVertice("E");

    // Agregar aristas con sus respectivos costos
    // A - B (costo 4)
    grafo.agregarArista("A", "B", 4);
    // A - C (costo 2)
    grafo.agregarArista("A", "C", 2);
    // B - C (costo 5)
    grafo.agregarArista("B", "C", 5);
    // B - D (costo 10)
    grafo.agregarArista("B", "D", 10);
    // C - D (costo 3)
    grafo.agregarArista("C", "D", 3);
    // D - E (costo 7)
    grafo.agregarArista("D", "E", 7);
    // E - A (costo 1)
    grafo.agregarArista("E", "A", 1);

    // Ejecutar el algoritmo de Prim
    cout << "Resultado del algoritmo de Prim:" << endl;
    grafo.prim();

    // Ejecutar el algoritmo de Kruskal
    cout << "\nResultado del algoritmo de Kruskal:" << endl;
    grafo.kruskal();

    return 0;
}