#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include "noeud.h"

class Graph {
    public:
        // L : Le nombre de ligne.
        // C : le nombre de Colonne pour le tableau.
        Graph();
        Graph(int& L, int& C);
        ~Graph();


        void affiche_valeur_graph();
    private:
        Noeud * grille_sommet;
        int Lignes;
        int Colonnes;

};

#endif