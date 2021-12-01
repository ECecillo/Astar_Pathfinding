#ifndef NOEUD_H
#define NOEUD_H

#include "altitude.h"

class Noeud
{
public:
    // Constructeur Destructeur.
    Noeud();
    Noeud(Altitude &);
    ~Noeud();

    void set_hauteur(Altitude&);
    Altitude get_hauteur();


    //

private:
    Altitude h; // L'altitude du sommet.
};

#endif