#include <stdio.h>
#include <limits.h>
#include <stdbool.h>


void afficherChemin(int predecesseurs[], int j) {
    
    if (predecesseurs[j] == -1)
        return;

    afficherChemin(predecesseurs, predecesseurs[j]);
    printf("-> %d ", j);
}

int trouverSommetMin(int distance[], bool ensembleSPT[], int V) {
    int min = INT_MAX, min_index;

    for (int v = 0; v < V; v++) {
        if (ensembleSPT[v] == false && distance[v] < min) {
            min = distance[v];
            min_index = v;
        }
    }

    return min_index;
}

void afficherSolution(int distance[], int predecesseurs[], int source, int V) {
    printf("Sommet \t Distance depuis la source \t Chemin\n");
    for (int i = 0; i < V; i++) {
        printf("%d \t %d \t\t\t\t\t\t", i, distance[i]);
        afficherChemin(predecesseurs, i);
        printf("\n");
    }
}

void dijkstra(int **graphe, int source, int destination, int V ) {
    int distance[V];
    bool ensembleSPT[V];
    int predecesseurs[V];

    for (int i = 0; i < V; i++) {
        distance[i] = INT_MAX;
        ensembleSPT[i] = false;
        predecesseurs[i] = -1;
    }

    distance[source] = 0;

    for (int count = 0; count < V - 1; count++) {
        int u = trouverSommetMin(distance, ensembleSPT, V);

        ensembleSPT[u] = true;

        for (int v = 0; v < V; v++) {
            if (!ensembleSPT[v] && graphe[u][v] && distance[u] != INT_MAX && distance[u] + graphe[u][v] < distance[v]) {
                distance[v] = distance[u] + graphe[u][v];
                predecesseurs[v] = u;
            }
        }
    }

    afficherSolution(distance, predecesseurs, source, V);

    printf("\nDistance minimale de %d à %d : %d\n", source, destination, distance[destination]);
}


