#include "module/graph.h"

Graph::Graph()
{
    Lignes = 0;
    Colonnes = 0;
    grille_sommet = NULL; // Met la pointeur de la grille à NULL.
}
Graph::Graph(int &L, int &C) : Lignes(L), Colonnes(C) 
{
    grille_sommet = new Noeud[Lignes*Colonnes]; // On créer un tableau sur le TAS de dimension (nb Lignes * nb Colonnes).
    for(int i = 0; i < Lignes*Colonnes; i++)
    {
        grille_sommet[i].set_hauteur() = 0;
    }
}
// Pour accéder à la première ligne du tableau 1D on fait :
// *Graph[C * i + j]
/*
 ___ 0__1__2__3__4____
 0 |  |  |  |  |  |
 1 |  |  |  |  |  |
 2 |  |  |  |  |  |
 3 |  |  |  |  |  |
 4 |  |  |  |  |  |
 
 La représentation graphique que l'on peut donner ici c'est une grille 2D où L = 5 et C = 5.

 Si on décide de mettre dans un fichier : 

 15 24 La ligne est 1 ici sera pour la hauteur(L) la largeur(C)
 
 Pour chaque ligne on donne les valeurs qui vont aller dans les cases de la grille ci-dessus.
  
 Exemple : 
 12 34 5 10 5

 On aura pour la première ligne de la grille : 

 ___ 0__ 1__  2__  3__ 4____
 0 | 0 | 12 | 34 | 5 | 10 |



 */