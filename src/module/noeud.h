#ifndef NOEUD_H
#define NOEUD_H

#include <utility>
#include "altitude.h"

class Noeud
{
public:
    // Constructeur Destructeur.
    Noeud();
    Noeud(Altitude &);
    ~Noeud();

    bool operator==(Noeud&) const;
    void set_hauteur(Altitude);
    Altitude get_hauteur();

    void set_couleur(char&);
    char get_couleur();

    // Va définir les coordo du Noeud par rapport à la grille du graph.
    void set_pos(pair<int,int>& nouvelle_pos);
    int get_pos_i();
    int get_pos_j();

    // Affiche le Noeud avec ces infos (hauteur, coord )
    void affiche_noeud();


private:
    char couleur;
    // Indice de position du Noeud dans la grille.
    pair<int, int> pos;
    pair<int, int> parent;
    Altitude h; // L'altitude du sommet.
};

#endif