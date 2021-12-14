#ifndef NOEUD_H
#define NOEUD_H

#include <utility>
#include "altitude.h"


class Noeud
{
public:
    // Données membres.
    int indice_parent; // Indice du parent dans la grille que l'on utilisera pour les aglos de PCD.
    int distance;      // Distance entre 2 noeud.
    int cout;          // Somme la distance entre 2 Noeuds et la distance entre depart et le noeud parent.
    int cout_total;    // Le cout Total de l'opétation = Heuristique (distance this ---> Fin) + cout.

    // Constructeur Destructeur.
    Noeud();
    Noeud(Altitude &);
    ~Noeud();

    bool operator==(Noeud &) const;
    void set_hauteur(Altitude);
    Altitude get_hauteur();

    void set_couleur(char);
    char get_couleur();

    // Va définir les coordo du Noeud par rapport à la grille du graph.
    void set_pos(pair<int, int> &nouvelle_pos);
    int get_pos_i();
    int get_pos_j();

    // Affiche le Noeud avec ces infos (hauteur, coord )
    void affiche_noeud();

private:
    char couleur;
    // Indice de position du Noeud dans la grille.
    pair<int, int> pos;
    Altitude h; // L'altitude du sommet.
};

#endif