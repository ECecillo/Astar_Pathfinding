#include "module/noeud.h"

Noeud::Noeud()
{
    h = 0;
    couleur = 'b';
}
Noeud::~Noeud()
{
    h = 0;
    couleur = '\0';
}
Noeud::Noeud(Altitude &h_def) : h(h_def)
{
}

Altitude Noeud::get_hauteur()
{
    return this->h;
}
void Noeud::set_hauteur(Altitude new_h)
{
    this->h = new_h;
}
char Noeud::get_couleur()
{
    return this->couleur;
}
void Noeud::set_couleur(char &c)
{
    this->couleur = c;
}
void Noeud::set_pos(pair<int, int> &nouvelle_pos)
{
    this->pos.first = nouvelle_pos.first;
    this->pos.second = nouvelle_pos.second;
}
int Noeud::get_pos_i()
{
    return this->pos.first;
}
int Noeud::get_pos_j()
{
    return this->pos.second;
}
void Noeud::affiche_noeud()
{
    if (couleur == 'b')
    {
        cout << "\033[1;" << 7 << "m"
             << "[" << h << ", (" << pos.first << ", " << pos.second << ")]"
             << "\033[0m";
        /* cout << "\033[1;" << 1 << "m"
             << "=="
             << "\033[0m"; */
    }
    else if (couleur == 'g')
    {
        cout << "\033[1;" << 100 << "m"
             << "[" << h << ", (" << pos.first << ", " << pos.second << ")]"
             << "\033[0m";
        /* cout << "\033[1;" << 1 << "m"
             << "=="
             << "\033[0m"; */
    }
    else if (couleur == 'n')
    {
        cout << "\033[1;" << 3 << "m"
             << "[" << h << ", (" << pos.first << ", " << pos.second << ")]"
             << "\033[0m";
        /* cout << "\033[1;" << 1 << "m"
             << "=="
             << "\033[0m"; */
    }
}
bool Noeud::operator==(Noeud &n) const
{
    return (h == n.get_hauteur() &&
    pos.first == n.pos.first &&
    pos.second == n.pos.second);
}