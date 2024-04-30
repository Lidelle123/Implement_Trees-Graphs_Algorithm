#include <limits.h>
#include <stdbool.h>
#include <stdio.h>

int sommetMin(int cle[], bool ensembleACM[],int V) {
    int min = INT_MAX, indiceMin;

    for (int v = 0; v < V; v++)
        if (ensembleACM[v] == false && cle[v] < min)
            min = cle[v], indiceMin = v;

    return indiceMin;
}

void imprimerACM(int parent[], int **graphe, int V) {
    printf("Voici les aretes contenues dans l'ACM\n");
    printf("Arêtes \tPoids\n");
    for (int i = 1; i < V; i++)
        printf("(%d , %d) \t%d \n", parent[i], i, graphe[i][parent[i]]);
}

void ACMdePrim(int **graphe,int V) {
    int parent[V];
    int cle[V];
    bool ensembleACM[V];

    for (int i = 0; i < V; i++)
        cle[i] = INT_MAX, ensembleACM[i] = false;

    cle[0] = 0;

    parent[0] = -1;

    for (int count = 0; count < V - 1; count++) {
        int u = sommetMin(cle, ensembleACM,  V);

        ensembleACM[u] = true;

        for (int v = 0; v < V; v++)
            if (graphe[u][v] && ensembleACM[v] == false && graphe[u][v] < cle[v])
                parent[v] = u, cle[v] = graphe[u][v];
    }

    imprimerACM(parent, graphe,V);
}


