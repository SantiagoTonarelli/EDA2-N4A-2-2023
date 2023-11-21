int colorear(Grafo g, int C) {
    // Asignación dinámica de memoria para los arreglos
    int* colores = new int[C + 1];
    bool* disponible = new int[C + 1];

    for (int i = 1; i <= C; ++i) {
        // Inicializar todos los colores como disponibles
        for (int j = 1; j <= C; ++j) {
            disponible[j] = true;
        }

        // Revisar los colores de los vecinos y marcar colores no disponibles
        for (int j = 0; j < g.vecino(i).cantidadDeVecinos(); ++j) {
            int vecino = g.vecino(i).getVecino(j);
            if (colores[vecino] != 0) {
                disponible[colores[vecino]] = false;
            }
        }

        // Encontrar el primer color disponible
        int cr;
        for (cr = 1; cr <= C && !disponible[cr]; ++cr);

        colores[i] = cr; // Asignar el color al cupcake
    }

    // Encontrar el número máximo de colores utilizados
    int maxColor = 0;
    for (int i = 1; i <= C; ++i) {
        if (colores[i] > maxColor) {
            maxColor = colores[i];
        }
    }

    return maxColor;
}