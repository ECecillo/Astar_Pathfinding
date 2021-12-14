#include "module/noeud.h"

using namespace std;


Noeud::Noeud()
{
    h = 0;
    couleur = 'b';
    indice_parent = 0;
    pos.first = 0;
    pos.second = 0;
    distance = 0;
    cout = 0;
    cout_total = 0;
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
void Noeud::set_couleur(char c)
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
        std::cout << "\033[1;" << 7 << "m" << "[" << h << ", (" << pos.first << ", " << pos.second << ")]" << "\033[0m";
        /* cout << "\033[1;" << 1 << "m"
             << "=="
             << "\033[0m"; */
    }
    else if (couleur == 'g')
    {
        std::cout << "\033[1;" << 31 << "m"
             << "[" << h << ", (" << pos.first << ", " << pos.second << ")]"
             << "\033[0m";
        /* cout << "\033[1;" << 1 << "m"
             << "=="
             << "\033[0m"; */
    }
    else if (couleur == 'n')
    {
        std::cout << "\033[1;" << 3 << "m"
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