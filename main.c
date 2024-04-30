#include <stdio.h>
#include <stdlib.h>
#include "Annexe - Dijkstra.c"
#include "Annexe - FibMemo.c"
#include "Annexe - FibTab.c"
#include "Annexe - Kruskal.c"
#include "Annexe - ARN.c"
#include "Annexe - Prim.c"

void afficherMenu()
{
    printf("\nMenu :\n");
    printf("1. Dijkstra - Plus court chemin dans un graphe\n");
    printf("2. Fibonacci (Programmation dynamique)\n");
    printf("3. Kruskal - Arbre couvrant de poids minimum\n");
    printf("4. ARN - Arbre rouge noir\n");
    printf("5. Prime - Arbre couvrant de poids minimum\n");
    printf("0. Quitter\n");
}

int main()
{
    int choix;

    do
    {
        afficherMenu();
        printf("Choisissez un algorithme (0-5) : ");
        scanf("%d", &choix);

        switch (choix)
        {
        case 1:
        {
            int v, numEdges;

            printf("Entrez le nombre de sommets du graphe: ");
            scanf("%d", &v);

            printf("Entrez le nombre d'aretes du graphe: ");
            scanf("%d", &numEdges);

            
            int **graph = (int **)malloc(v * sizeof(int *));
            for (int i = 0; i < v; i++)
            {
                graph[i] = (int *)malloc(v * sizeof(int));
                for (int j = 0; j < v; j++)
                {
                    graph[i][j] =0;
                }
            }

            printf("Entrez les aretes du graphe avec les poids (debut fin poids):\n");
            for (int i = 0; i < numEdges; ++i)
            {
                int start, end, weight;
                printf("Arete %d: ", i + 1);
                scanf("%d %d %d", &start, &end, &weight);
        
                graph[start][end] = weight;
                graph[end][start] = weight;
            }

            
            int source, destination;
            printf("Entrez le sommet source: ");
            scanf("%d", &source);
            printf("Entrez le sommet destination: ");
            scanf("%d", &destination);

            printf("Voici la matrice d'adjacence du graphe construit a partir des arretes que vous avez fournis: \n ");
            for(int i=0;i < v; i++){
                for(int j=0;j < v; j++)
                printf("%d\t",graph[i][j]);

                printf("\n");
            }
            dijkstra(graph, source, destination,v);
            break;
        }
        case 2:
        {
            int n;
            do
            {
                printf("Entrez le terme de la suite de Fibonacci que vous souhaitez calculer : ");
                scanf("%d", &n);
                if (n < 0)
                {
                    printf("Veuillez entrer un nombre positif.\n");
                }
            } while (n < 0);
            printf("LE TERME %d DE LA SUITE DE FIBONACCI EST : %llu\n", n, fibonacciT(n));
            break;
        }
        case 3:
        {
            int numEdges;

            printf("Entrer le nombre d'aretes: ");
            scanf("%d", &numEdges);

            int(*edges)[3] = malloc(numEdges * sizeof(int[3]));

            printf("\nEntrer les aretes (start end weight):\n");
            for (int i = 0; i < numEdges; ++i)
            {
                printf("\nAretes %d: ", i + 1);

                for (int j = 0; j < 3; ++j)
                {
                    scanf("%d", &edges[i][j]);
                }
            }

            algorithmeKruskal(numEdges, edges);

            free(edges);
            break;
        }

        case 4:
        {
            struct noeud *racine = NULL;
            int choix2;
            int cle;
            int cleR;
            int nbre;
            int arbreConstruit = 0;

            do
            {
                // Affichez le menu
                printf("\nMenu :\n");
                printf("1. Insertion\n");
                printf("2. Suppression\n");
                printf("3. Recherche\n");
                //printf("3. Affichage de l'arbre\n");
                printf("4. Rotation à gauche\n");
                printf("5. Rotation à droite\n");
                printf("6. Quitter\n");

                // Demandez à l'utilisateur de faire un choix
                printf("Choix : ");
                scanf("%d", &choix2);

                switch (choix2)
                {
                case 1:
                    printf("Entrez le Nombre de noeuds de votre arbre : ");
                    scanf("%d", &nbre);

                    for (int i = 0; i < nbre; ++i)
                    {
                        printf("Entrez la clé du nœud %d : ", i + 1);
                        scanf("%d", &cle);

                        struct noeud *nouveau = (struct noeud *)malloc(sizeof(struct noeud));
                        nouveau->clé = cle;
                        nouveau->gauche = FEUILLE;
                        nouveau->droit = FEUILLE;
                        nouveau->parent = NULL;
                        nouveau->couleur = ROUGE;

                        racine = insertion(racine, nouveau);
                    }

                    arbreConstruit = 1;


                    printf("Arbre après insertion :\n");
                    racine = afficheArbre(racine);

                    break;
                case 2:
                    if (arbreConstruit)
                    {
                        printf("Entrez la clé à supprimer : ");
                        scanf("%d", &cle);

                        suppression(racine, cle);

                        printf("Arbre après suppression :\n");
                        racine = afficheArbre(racine);
                    }
                    else
                    {
                        printf("Veuillez d'abord construire l'arbre en insérant des valeurs.\n");
                    }

                    break;
                case 3:
                    if (arbreConstruit) {
                        printf("Entrez la clé à rechercher : ");
                        scanf("%d", &cle);

                        struct noeud* resultatRecherche = recherche(racine, cle);

                        if (resultatRecherche != NULL) {
                            printf("La clé %d a été trouvée dans l'arbre.\n", cle);
                            printf("Voici les informations du noeuds en question\n");
                            afficheNoeud(resultatRecherche);
                        } else {
                            printf("La clé %d n'a pas été trouvée dans l'arbre.\n", cle);
                        }
                    } else {
                        printf("Veuillez d'abord construire l'arbre en insérant des valeurs.\n");
                    }
                    break;
                case 4:
                    if (arbreConstruit)
                    {
                        printf("Entrez la clé du nœud sur lequel vous voulez roter : ");
                        scanf("%d", &cleR);

                        struct noeud* resultatRecherche = recherche(racine, cleR);

                        if (resultatRecherche != NULL) {
                            struct noeud* monNoeud = creerNoeud(cleR);
                            //
                             //printf("%d, %d\n", monNoeud->clé, monNoeud->couleur);
                            rotationGauche(resultatRecherche);
                            printf("Affichage de l'arbre apres rotation a gauche sur le noeud de cle %d \n", cleR);
                            racine = afficheArbre(racine);


                        } else {
                            printf("La clé %d n'est pas présente dans l'arbre. Veuillez réessayer.\n", cleR);
                        }
                    }
                        else
                    {
                        printf("Veuillez d'abord construire l'arbre en insérant des valeurs.\n");
                    }
                    
                    break;
                case 5:
                    if (arbreConstruit)
                    {
                        printf("Entrez la clé du nœud sur lequel vous voulez roter : ");
                        scanf("%d", &cleR);

                        struct noeud* resultatRecherche = recherche(racine, cleR);

                        if (resultatRecherche != NULL) {
                            struct noeud* monNoeud = creerNoeud(cleR);
                            rotationDroite(resultatRecherche);
                            printf("Affichage de l'arbre apres rotation a droite sur le noeud de cle %d \n", cleR);
                            racine = afficheArbre(racine);

                        } else {
                            printf("La clé %d n'est pas présente dans l'arbre. Veuillez réessayer.\n", cleR);
                        }
                    }
                        else
                    {
                        printf("Veuillez d'abord construire l'arbre en insérant des valeurs.\n");
                    }
                    
                    break;
                case 6:
                {
                    // Quittez le programme
                    printf("Programme terminé.\n");
                    break;
                    
                }default:
                        printf("Choix invalide. Veuillez réessayer.\n");
                        break;
            }
            } while (choix2 != 6);
            break;
        }
        case 5:{
            int v, numEdges;

            printf("Entrez le nombre de sommets du graphe: ");
            scanf("%d", &v);

            printf("Entrez le nombre d'aretes du graphe: ");
            scanf("%d", &numEdges);

            int **graph = (int **)malloc(v * sizeof(int *));
            for (int i = 0; i < v; i++)
            {
                graph[i] = (int *)malloc(v * sizeof(int));
                for (int j = 0; j < v; j++)
                {
                    graph[i][j] =0;
                }
            }

            printf("Entrez les aretes du graphe avec les poids (debut fin poids):\n");
            for (int i = 0; i < numEdges; ++i)
            {
                int start, end, weight;
                printf("Arete %d: ", i + 1);
                scanf("%d %d %d", &start, &end, &weight);
                graph[start][end] = weight;
                graph[end][start] = weight;
            }

            printf("Voici la matrice d'adjacence du graphe construit a partir des arretes que vous avez fournis: \n ");
            for(int i=0;i < v; i++){
                for(int j=0;j < v; j++)
                printf("%d\t",graph[i][j]);

                printf("\n");
            }
            ACMdePrim(graph,v);
        }
        case 0:
            printf("Au revoir !\n");
            break;
        default:
            printf("Choix invalide. Veuillez entrer un nombre entre 0 et 4.\n");
        }

    } while (choix != 0);

    return 0;
}
