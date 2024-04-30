#include <stdio.h>
#include <stdlib.h>


int comparateur(const void* p1, const void* p2)
{
	const int(*x)[3] = p1;
	const int(*y)[3] = p2;

	return (*x)[2] - (*y)[2];
}


void initialiserEnsemble(int parent[], int rang[], int n)
{
	for (int i = 0; i < n; i++) {
		parent[i] = i;
		rang[i] = 0;
	}
}


int trouverParent(int parent[], int composant)
{
	if (parent[composant] == composant)
		return composant;

	return parent[composant]
		= trouverParent(parent, parent[composant]);
}


void unionEnsemble(int u, int v, int parent[], int rang[], int n)
{
	
	u = trouverParent(parent, u);
	v = trouverParent(parent, v);

	if (rang[u] < rang[v]) {
		parent[u] = v;
	}
	else if (rang[u] > rang[v]) {
		parent[v] = u;
	}
	else {
		parent[v] = u;
		rang[u]++;
	}
}


void algorithmeKruskal(int n, int aretes[n][3])
{
	
	qsort(aretes, n, sizeof(aretes[0]), comparateur);

	int parent[n];
	int rang[n];

	
	initialiserEnsemble(parent, rang, n);

	
	int coutMinimum = 0;

	printf(
		"Voici les arêtes dans l'ACM construit\n");
	for (int i = 0; i < n; i++) {
		int v1 = trouverParent(parent, aretes[i][0]);
		int v2 = trouverParent(parent, aretes[i][1]);
		int poids = aretes[i][2];

		
		if (v1 != v2) {
			unionEnsemble(v1, v2, parent, rang, n);
			coutMinimum += poids;
			printf(" Arête (%d, %d) de poids %d\n", aretes[i][0],
				aretes[i][1], poids);
		}
	}

	printf("Cout Minimum de l'Arbre Couvrant : %d\n", coutMinimum);
}

// Programme principal
/*int main()
{
	int aretes[5][3] = { { 1, 2, 4 },
					{ 2, 4, 3 },
					{ 4, 3, 1 },
					{ 2, 3, 1 },
					{ 1, 3, 6 } };

	algorithmeKruskal(5, aretes);

	return 0;
}*/
