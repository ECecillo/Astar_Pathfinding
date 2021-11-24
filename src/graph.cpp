#include "module/graph.h"

Graph::Graph()
{
    Lignes = 0;
    Colonnes = 0;
    Graph = NULL;
}
Graph::Graph(int &L, int &C) : Lignes(L), Colonnes(C) 
{
    *Graph = new [L*C]; // On créer un tableau sur le TAS de dimension (nb Lignes * nb Colonnes).
}
// Pour accéder à la première ligne du tableau 1D on fait :
// *Graph[C * i + j]