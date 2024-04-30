#include <stdio.h>
#include <time.h>
#include <math.h>


#define INT_MAX 100000
#define TRUE    1
#define FALSE   0
#define V 8
#define E 11

typedef int bool;

typedef struct
{
	int u;
	int v;

} Edge;

typedef struct
{
	int title;
	bool visited;

} Vertex;

void printArray(int *array, int *paths) {
    printf("Vertex\tShortest Path\tPath\n");
    for (int i = 0; i < V; i++) {
        printf("%d\t%d\t\t", i, array[i]);
        int j = i;
        while (j != -1) {
            printf("%d", j);
            j = paths[j];
            if (j != -1) {
                printf(" <- ");
            }
        }
        printf("\n");
    }
}

void DijkstraOMP(Vertex *vertices, Edge *edges, int *weights, Vertex *root) {
    double start, end;

    root->visited = TRUE;

    int len[V];
    int paths[V];

    len[(int)root->title] = 0;
    paths[(int)root->title] = -1;

    int i, j;

    for (i = 0; i < V; i++) {
        if (vertices[i].title != root->title) {
            len[(int)vertices[i].title] = findEdge(*root, vertices[i], edges, weights);
            paths[(int)vertices[i].title] = root->title;
        } else {
            vertices[i].visited = TRUE;
        }
    }

    for (j = 0; j < V; j++) {
        Vertex u;
        int h = minPath(vertices, len);
        u = vertices[h];

        #pragma omp parallel for schedule(runtime) private(i)
        for (i = 0; i < V; i++) {
            if (vertices[i].visited == FALSE) {
                int c = findEdge(u, vertices[i], edges, weights);
                if (len[u.title] + c < len[vertices[i].title]) {
                    len[vertices[i].title] = len[u.title] + c;
                    paths[vertices[i].title] = u.title;
                }
            }
        }
    }
    // end = omp_get_wtime();
    printArray(len, paths);
    // printf("Running time: %f ms\n", (end - start)*1000);
}



//Finds the edge that connects Vertex u with Vertex v
int findEdge(Vertex u, Vertex v, Edge *edges, int *weights)
{

	int i;
	for(i = 0; i < E; i++)
	{

		if(edges[i].u == u.title && edges[i].v == v.title)
		{
			return weights[i];
		}
	}

	return INT_MAX;

}

//Returns the minimum between two integers
int minimum(int A, int B)
{
	if( A > B)
	{
		return B;
	}

	else{
		return A;
	}
}

//Visits the vertices and looks for the lowest weight from the vertex
int minWeight(int *len, Vertex *vertices)
{
	int i;
	int minimum = INT_MAX;
	for(i = 0; i < V; i++)
	{
		if(vertices[i].visited == TRUE)
		{
			continue;
		}

		else if(vertices[i].visited == FALSE && len[i] < minimum)
		{
			minimum = len[i];

		}

	}
	return minimum;
}

//Localizes the vertex with the lowest weight path
int minPath(Vertex *vertices, int *len)
{
	int i;
	int min = minWeight(len, vertices);

	for(i = 0; i < V; i++)
	{
		if(vertices[i].visited == FALSE && len[vertices[i].title] == min)
		{
			vertices[i].visited = TRUE;
			return i;

		}
	}
}

int main(void)
{

	Vertex vertices[V];
	// Edge edges[E];
	// int weights[E];


	//----------------------------------Graph Base Test-------------------------------------//

	Edge edges[E] ={{0, 4}, {0, 6}, {0,2}, {4,6}, {4,7}, {0, 7}, {7, 3}, {3, 1}, {2,5}, {2, 1}, {5,3}};
	int weights[E] = {10, 90, 30, 20, 20, 50, 10, 20, 10, 10, 10};

	int i = 0;
	for(i = 0; i < V; i++)
	{
		Vertex a = { .title =i , .visited=FALSE};
		vertices[i] = a;
	}


	Vertex root = {0, FALSE};

	printf("OpenMP Results for Small Graph of 8 Vertices:\n");
	DijkstraOMP(vertices, edges, weights, &root);

    printf("\n\n");
}