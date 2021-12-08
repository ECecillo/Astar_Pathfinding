#include "module/graph.h"
#include "module/altitude.h"

using namespace std;

Graph::Graph()
{
    Lignes = 0;
    Colonnes = 0;
    grille_sommet = NULL; // Met la pointeur de la grille à NULL.
}
Graph::Graph(int &L, int &C) : Lignes(L), Colonnes(C)
{
    grille_sommet = new Noeud[Lignes * Colonnes]; // On créer un tableau sur le TAS de dimension (nb Lignes * nb Colonnes).
    Altitude h = 0;
    // Lors de l'initialisation de la hauteur pour chaque case de la grille, on mettra dans la donnée membre du noeud l'indice de parcours de ligne et de colonne respectivement i et j.
    for (int i = 0; i < Lignes; i++)
    {
        for (int j = 0; j < Colonnes; j++)
        {
            // Pour plus de lisibilité.
            Noeud noeud_courant = grille_sommet[i * Colonnes + j];
            
            noeud_courant.set_hauteur(h);
            pair<int, int> poistion_noeud_grille(i, j);
            noeud_courant.set_pos(poistion_noeud_grille);
        }
    }
}
Graph::~Graph()
{
    Lignes = 0;
    Colonnes = 0;
    delete[] grille_sommet;
    grille_sommet = NULL;
}

Altitude Graph::Distance_voisin_noeud(Noeud &origine, Noeud &voisin)
{ // On suppose que orignie et voisin sont à côté.
    // Rappel de la formule :
    // sqrt(1 + sqr(altitude_point_depart - altitude_point_arrive));
    Altitude hauteur_origine = origine.get_hauteur();
    Altitude hauteur_voisin = voisin.get_hauteur();
    // Ici il faut que l'on calcule la position du voisin par rapport à Origine.
    Altitude difference = hauteur_origine - hauteur_voisin;

    Altitude carre_difference = difference * difference;

    Altitude base_difference = Altitude(1) + carre_difference;

    return floorSqrt(base_difference); // On retourne la distance euclidienne entre O et F.
}

int Graph::indice_Noeud(const int &i, const int &j) const
{
    return i * Colonnes + j;
}
int Graph::indice_Noeud_depuis_ligne(const int &i) const
{
    // j = 0 car peut importe sa valeur ce qui nous intérèsse c'est la ligne associé.
    return i * Colonnes + 0;
}
int Graph::indice_Noeud_depuis_colonne(const int &j) const
{
    return 0 * Colonnes + j;
}

Altitude Graph::Altitude_Noeud(const int &indice_Noeud) const
{
    return grille_sommet[indice_Noeud].get_hauteur();
}
int Graph::indice_Noeud_voisin(Noeud &ref, string voisin) const
{
    const int indice_i_ref = ref.get_pos_i();
    const int indice_j_ref = ref.get_pos_j();
    int indice_globale_voisin = -1;
    if (voisin == "Nord")
    {
        // On vérifie les cas pour limiter les segfault.
        if (indice_i_ref - 1 < 0)
        {
            cout << "Pas de voisin Nord" << endl;
        }
        else
            indice_globale_voisin = (indice_i_ref - 1) * Colonnes + indice_j_ref;
    }
    else if (voisin == "Sud")
    {
        if (indice_i_ref + 1 > Lignes)
        {
            cout << "Pas de voisin Sud" << endl;
        }
        else
            indice_globale_voisin = (indice_i_ref + 1) * Colonnes + indice_j_ref;
    }
    else if (voisin == "Est")
    {
        if (indice_j_ref + 1 > Colonnes)
        {
            cout << "Pas de voisin Est" << endl;
        }
        else
            indice_globale_voisin = indice_i_ref * Colonnes + (indice_j_ref + 1);
    }
    else if (voisin == "Ouest")
    {
        if (indice_j_ref - 1 < 0)
            cout << "Pas de voisin Ouest" << endl;
        else
            indice_globale_voisin = indice_i_ref * Colonnes + (indice_j_ref - 1);
    }
    return indice_globale_voisin;
}

Altitude Graph::floorSqrt(Altitude &x)
{
    // Base cases
    if (x == 0 || x == 1)
        return x;

    // Do Binary Search for floor(sqrt(x))
    Altitude start = 1, end = x / 2, ans;
    while (start <= end)
    {
        Altitude mid = (start + end) / 2;

        // If x is a perfect square
        Altitude sqr = mid * mid;
        if (sqr == x)
            return mid;

        if (sqr <= x)
        {
            start = mid + Altitude(1);
            ans = mid;
        }
        else // If mid*mid is greater than x
            end = mid - 1;
    }
    return ans;
}

// Pour accéder à la première ligne du tableau 1D on fait :
// *Graph[C * i + j]
/*
 ___ 0__ 1__ 2__ 3__ 4____
 0 | . | . | . | . | . |
 1 | . | . | . | . | . |
 2 | . | . | . | . | . |
 3 | . | . | . | . | . |
 4 | . | . | . | . | . |
 


tab = []

 (0,0) ---- (0,1) ------ (0,2) ---- (0,3)
   |          |            |          |
 (1,0) ---- (1,1) ------ (1,2) ---- (1,3)
   |          |            |          |
 (2,0) ---- (2,1) ------ (2,2) ---- (1,3)
   |          |            |          |
 (3,0) ---- (3,1) ------ (3,2) ---- (3,3)
 
Chaque Point correspond à un sommet (Noeud).

 La représentation graphique que l'on peut donner ici c'est une grille 2D où L = 5 et C = 5.

 Si on décide de mettre dans un fichier : 

 15 24 La ligne est 1 ici sera pour la hauteur(L) la largeur(C)
 
 Pour chaque ligne on donne les valeurs qui vont aller dans les cases de la grille ci-dessus.
  
 Exemple : 
 12 34 5 10 5

 On aura pour la première ligne de la grille : 

 ___ 0__ 1__  2__  3__ 4____
 0 | 12 | 34 | 5 | 10 | 5 |
.....






 */