#include "noeud.h"

Noeud::Noeud()
{
    h = 0;
}
Noeud::~Noeud()
{
    h = 0;
}
Noeud::Noeud(Altitude& h_def) : h(h_def)
{}
Altitude Noeud::get_hauteur()
{
    return this->h;
}
void Noeud::set_hauteur(Altitude& new_h)
{
    this->h = new_h;
}
