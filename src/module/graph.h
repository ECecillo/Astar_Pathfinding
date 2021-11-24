#ifndef GRAPH_H
#define GRAPH_H

#include "altitude.h"

class Graph {
    public:
        // L : Le nombre de ligne.
        // C : le nombre de Colonne pour le tableau.
        Class(int& L, int& C);
        Class();
        ~Class();


        void affiche_valeur_graph();
    private:
        Altitude *grille_graph;
        int Lignes;
        int Colonnes;

};

#endif