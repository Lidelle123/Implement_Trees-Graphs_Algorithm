#include <stdlib.h>
#include <stdio.h>

#define NOIR 0
#define ROUGE 1
#define FEUILLE NULL

typedef struct noeud
{
  struct noeud *gauche;
  struct noeud *droit;
  struct noeud *parent;
  int couleur;
  int clé;
} Noeud;

struct noeud *parent(struct noeud *n)
{
  return n->parent;
}

struct noeud *grandparent(struct noeud *n)
{
  struct noeud *p = parent(n);
  if (p == NULL)
    return NULL;
  return parent(p);
}

struct noeud *frere(struct noeud *n)
{
  struct noeud *p = parent(n);
  if (p == NULL)
    return NULL;
  if (n == p->gauche)
    return p->droit;
  else
    return p->gauche;
}

struct noeud *oncle(struct noeud *enfant)
{
  struct noeud *p = parent(enfant);
  struct noeud *g = grandparent(enfant);
  if (g == NULL)
    return NULL;
  return frere(p);
}

void rotationGauche(struct noeud *x)
{
  struct noeud *y = x->droit;
  x->droit = y->gauche;
  if (y->gauche != FEUILLE)
    y->gauche->parent = x;

  y->parent = x->parent;
  if (x->parent == NULL)
    y->parent = NULL;
  else if (x == x->parent->gauche)
    x->parent->gauche = y;
  else
    x->parent->droit = y;


  y->gauche = x;
  x->parent = y;
}

void rotationDroite(struct noeud *x)
{
  struct noeud *y = x->gauche;
  x->gauche = y->droit;
  if (y->droit != FEUILLE)
    y->droit->parent = x;

  y->parent = x->parent;
  if (x->parent == NULL)
    y->parent = NULL;

  else if (x == x->parent->droit)
    x->parent->droit = y;
  else
    x->parent->gauche = y;

  y->droit = x;
  x->parent = y;


}

void insertion_recursif(struct noeud *racine, struct noeud *n)
{
  if (racine != NULL && n->clé < racine->clé)
  {
    if (racine->gauche != FEUILLE)
    {
      insertion_recursif(racine->gauche, n);
      return;
    }
    else
      racine->gauche = n;
  }
  else if (racine != NULL)
  {
    if (racine->droit != FEUILLE)
    {
      insertion_recursif(racine->droit, n);
      return;
    }
    else
      racine->droit = n;
  }

  // Insertion du nouveau noeud n
  n->parent = racine;
  n->gauche = FEUILLE; // NIL
  n->droit = FEUILLE;  // NIL
  n->couleur = ROUGE;
}

void insertion_cas1(struct noeud *n);
void insertion_cas2(struct noeud *n);
void insertion_cas3(struct noeud *n);
void insertion_cas4(struct noeud *n);


void insertionCorrection(struct noeud *n)
{
  if (parent(n) == NULL)
    insertion_cas1(n);
  else if (parent(n)->couleur == NOIR)
    insertion_cas2(n);
  else if (oncle(n) != NULL && oncle(n)->couleur == ROUGE)
    insertion_cas3(n);
  else
    insertion_cas4(n);
}

void insertion_cas1(struct noeud *n)
{
  if (parent(n) == NULL)
    n->couleur = NOIR;
}

void insertion_cas2(struct noeud *n)
{
  return;
}

void insertion_cas3(struct noeud *n)
{
  parent(n)->couleur = NOIR;
  oncle(n)->couleur = NOIR;

  struct noeud *g = grandparent(n);
  g->couleur = ROUGE;
  insertionCorrection(g);
}

void insertion_cas4(struct noeud *n)
{
  struct noeud *p = parent(n);
  struct noeud *g = grandparent(n);

  if (n == p->gauche)
    rotationDroite(g);
  else
    rotationGauche(g);

  p->couleur = NOIR;
  g->couleur = ROUGE;
}


struct noeud *insertion(struct noeud *racine, struct noeud *n)
{
  insertion_recursif(racine, n);

  insertionCorrection(n);

  racine = n;

  while (parent(racine) != NULL)
    racine = parent(racine);

  return racine;
}





/*
* Fonction supplementaire
*/
// Renvoie la racine de l'arbre
struct noeud* racine(struct noeud* x)
{
  if (x->parent == NULL)
    return x;
  else
    racine(x->parent);
};

// Renvoie le noeud partant de la racine s'il existe
struct noeud* recherche(struct noeud* r, int cle)
{
  
  if(r == NULL)
  return NULL;
  printf("noeud objet de recherche\n");
  printf("%d, %d\n", r->clé, r->couleur);
  if (r->clé == cle)
    return r;
  else if (r->clé < cle)
    recherche(r->droit, cle);
  else if (r->clé > cle)
    recherche(r->gauche, cle);
  else
    return NULL;
};

//Supprime une cle dans l'arbre
/*
* NB: La suppression marque a -1 la cle du noeud supprime
*/
void suppressionCorrection(struct noeud* racine, struct noeud* x) {
  // printf("Correction");
  // affiche(racine);
  struct noeud* frere = NULL;
  while (x != racine && x->couleur == NOIR) {
    if (x == x->parent->gauche) {
      frere = x->parent->droit;
      if (frere->couleur == ROUGE) {
        frere->couleur = NOIR;
        x->parent->couleur = ROUGE;
        rotationGauche(x->parent);
        frere = x->parent->droit;
      }
      if (frere->gauche == FEUILLE || frere->gauche->couleur == NOIR && frere->droit == FEUILLE || frere->droit->couleur == NOIR) {
        frere->couleur = ROUGE;
        x = x->parent;
      } else {
        if (frere->droit->couleur == NOIR) {
          frere->gauche->couleur = NOIR;
          frere->couleur = ROUGE;
          rotationDroite(frere);
          frere = x->parent->droit;
        }
        frere->couleur = x->parent->couleur;
        x->parent->couleur = NOIR;
        frere->droit->couleur = NOIR;
        rotationGauche(x->parent);
        x = racine;
      }
    } else {
      // Cas symétrique pour la droite
      frere = x->parent->gauche;
      if (frere->couleur == ROUGE) {
        frere->couleur = NOIR;
        x->parent->couleur = ROUGE;
        rotationDroite(x->parent);
        frere = x->parent->gauche;
      }
      if (frere->droit == FEUILLE || frere->droit->couleur == NOIR && frere->gauche == FEUILLE || frere->gauche->couleur == NOIR) {
        frere->couleur = ROUGE;
        x = x->parent;
      } else {
        if (frere->gauche->couleur == NOIR) {
          frere->droit->couleur = NOIR;
          frere->couleur = ROUGE;
          rotationGauche(frere);
          frere = x->parent->gauche;
        }
        frere->couleur = x->parent->couleur;
        x->parent->couleur = NOIR;
        frere->gauche->couleur = NOIR;
        rotationDroite(x->parent);
        x = racine;
      }
    }
  }
  x->couleur = NOIR;
}

void suppression(struct noeud* racine, int cle) {
  // printf("Suppression");
  struct noeud* z = racine;
  while (z != NULL) {
    if (z->clé == cle)
      break;
    if (z->clé < cle)
      z = z->droit;
    else
      z = z->gauche;
  }

  if (z == NULL) {
    printf("La clé %d n'existe pas dans l'arbre.\n", cle);
    return;
  }

  struct noeud* y = z;
  int y_original_color = y->couleur;
  struct noeud* x;

  if (z->gauche == NULL) {
    x = z->droit;
    suppressionCorrection(racine, z);
    z->clé = -1;
  } else if (z->droit == NULL) {
    x = z->gauche;
    suppressionCorrection(racine, z);
    z->clé = -1;
  } else {
    y = z->droit;
    while (y->gauche != NULL)
      y = y->gauche;
      y_original_color = y->couleur;
      x = y->droit;
    if (y->parent == z)
      x->parent = y;
    else {
      suppressionCorrection(racine, y);
      y->droit = z->droit;
      y->droit->parent = y;
    }
    suppressionCorrection(racine, z);
    y->gauche = z->gauche;
    y->gauche->parent = y;
    y->couleur = z->couleur;
    z->clé = -1;
  }

  if (y_original_color == NOIR)
    suppressionCorrection(racine, x);

}




char* couleur(struct noeud* n){
  if (n->couleur == 0)
    return "NOIR";
  else
    return "ROUGE";
}

void parcoursInfixe(struct noeud *racine, int n)
{
  if (racine == NULL)
  {
    return ;
  }
  parcoursInfixe(racine->gauche, n+1);
  printf("Niveau %d : %d.%s ", n, racine->clé, couleur(racine));
  parcoursInfixe(racine->droit, n+1);
}

struct noeud* afficheArbre(struct noeud* n)
{
  if (n->parent == NULL)
  {
    
    parcoursInfixe(n, 1);
    return n;}
   
  else
    afficheArbre(n->parent);
}

void afficheNoeud(struct noeud* x) {
  printf("Cle: %d,\n", x->clé);
  printf("Couleur: %d,\n", x->couleur);
  if (x->parent == NULL)
  {
    printf("Parent: null\n");
  } else {
    printf("Parent: %d,\n", x->parent->clé);
  }
  if (x->droit == FEUILLE)
  {
    printf("Fils Droit: (null)\n");
  } else {
    printf("Fils Droit: %d,\n", x->droit->clé);
  }
  if (x->gauche == FEUILLE)
  {
    printf("Fils Gauche: (null)\n");
  } else {
    printf("Fils Gauche: %d,\n", x->gauche->clé);
  }
}

struct noeud* creerNoeud(int valeur) {
    struct noeud* nouveau = (struct noeud*)malloc(sizeof(struct noeud));
    nouveau->clé = valeur;
    nouveau->gauche = FEUILLE;
    nouveau->droit = FEUILLE;
    nouveau->parent = NULL;
    nouveau->couleur = ROUGE;
    
    return nouveau;
}


