#include "module/graph.h"
#include "module/altitude.h"
#include "module/indexed_priority_queue.h"

using namespace std;

Graph::Graph()
{
    Lignes = 0;
    Colonnes = 0;
    grille_sommet = NULL; // Met la pointeur de la grille à NULL.
}
Graph::Graph(string nomFichier)
{
    // On créer un tableau sur le TAS de dimension (nb Lignes * nb Colonnes).
    lecture_fichier_graph(nomFichier);
    // Lors de l'initialisation de la hauteur pour chaque case de la grille, on mettra dans la donnée membre du noeud l'indice de parcours de ligne et de colonne respectivement i et j.
    cout << grille_sommet[0].get_hauteur() << endl;
}
Graph::~Graph()
{
    Lignes = 0;
    Colonnes = 0;
    delete[] grille_sommet;
    grille_sommet = NULL;
}

void Graph::lecture_fichier_graph(string nomFichier)
{
    // Varible locale pour définir la hauteur pour chaque noeud.
    int hauteur_noeud;
    // Debut lecture fichier.
    ifstream fichier(nomFichier.c_str());
    if (fichier.is_open())
    {
        // On initialise la taille du graph.
        fichier >> Colonnes;
        fichier >> Lignes;
        grille_sommet = new Noeud[Lignes * Colonnes];
        for (int i = 0; i < Lignes; i++)
        {
            for (int j = 0; j < Colonnes; j++)
            {
                if (!fichier.eof())
                {
                    // Noeud sur lequel on est.
                    Noeud &noeud_courant = grille_sommet[i * Colonnes + j];
                    // Pair permettant de retrouver à partir d'un noeud sa position dans la grille.
                    pair<int, int> poistion_noeud_grille(i, j);
                    // Application dans données membres du noeud courant.
                    noeud_courant.set_pos(poistion_noeud_grille);
                    // On fix la hauteur du noeud.
                    fichier >> hauteur_noeud;
                    noeud_courant.set_hauteur(Altitude(hauteur_noeud));
                }
                else
                {
                    cout << "Erreur dans l'acquisition du fichier" << endl;
                }
            }
        }
        fichier.close();
    }
    else
    {
        cout << "Erreur dans l'ouverture du fichier" << endl;
    }
}

int Graph::Distance_voisin_noeud_3D(Noeud &origine, Noeud &voisin)
{ // On suppose que orignie et voisin sont à côté.
    // Rappel de la formule :
    // sqrt(1 + sqr(altitude_point_depart - altitude_point_arrive));
    Altitude hauteur_origine = origine.get_hauteur();
    Altitude hauteur_voisin = voisin.get_hauteur();
    // Ici il faut que l'on calcule la position du voisin par rapport à Origine.
    Altitude difference_hauteur = hauteur_origine - hauteur_voisin;

    int difference_position_x = origine.get_pos_i() - voisin.get_pos_i();
    int difference_position_y = origine.get_pos_j() - voisin.get_pos_j();

    Altitude carre_difference_hauteur = difference_hauteur * difference_hauteur;

    // On fait (position_des_x)²
    int carre_difference_position_x = difference_position_x * difference_position_x;

    int carre_difference_position_y = difference_position_y * difference_position_y;

    int base_difference = carre_difference_hauteur + (carre_difference_position_x + carre_difference_position_y);

    //
    return sqrt(base_difference);
}
int Graph::Distance_voisin_noeud_2D(Noeud &origine, Noeud &voisin)
{ // On suppose que orignie et voisin sont à côté.
    // Rappel de la formule :
    // sqrt(1 + sqr(altitude_point_depart - altitude_point_arrive));

    int difference_position_x = origine.get_pos_i() - voisin.get_pos_i();
    int difference_position_y = origine.get_pos_j() - voisin.get_pos_j();

    // On fait (position_des_x)²
    int carre_difference_position_x = difference_position_x * difference_position_x;

    // (y1 - y2)²
    int carre_difference_position_y = difference_position_y * difference_position_y;

    return sqrt((carre_difference_position_x + carre_difference_position_y));
}

int Graph::indice_Noeud(Noeud &n) const
{
    assert(n.get_pos_i() >= 0 && n.get_pos_i() < Lignes && n.get_pos_j() >= 0 && n.get_pos_j() < Colonnes && "Echec, merci de spécifier des valeurs dans les bornes de la grille.\n");
    return n.get_pos_i() * Colonnes + n.get_pos_j();
}
int Graph::indice_Noeud_depuis_ligne(Noeud &n) const
{
    // j = 0 car peut importe sa valeur ce qui nous intérèsse c'est la ligne associé.
    return n.get_pos_i() * Colonnes + 0;
}
int Graph::indice_Noeud_depuis_colonne(Noeud &n) const
{
    return 0 * Colonnes + n.get_pos_j();
}

Altitude Graph::Altitude_Noeud(Noeud &n) const
{
    return n.get_hauteur();
}
int Graph::indice_Noeud_voisin(Noeud &ref, int &voisin) const
{ // 0 : Nord, 1: Sud, 2: Est, 3: Ouest.
    const int indice_i_ref = ref.get_pos_i();
    const int indice_j_ref = ref.get_pos_j();

    int indice_globale_voisin = -1;
    if (voisin == 0)
    {
        // On vérifie les cas pour limiter les segfault.
        if (indice_i_ref - 1 < 0)
        {
            cout << "Pas de voisin Nord" << endl;
        }
        else
            indice_globale_voisin = (indice_i_ref - 1) * Colonnes + indice_j_ref;
    }
    else if (voisin == 1)
    {
        if (indice_i_ref + 1 > Lignes)
        {
            cout << "Pas de voisin Sud" << endl;
        }
        else
            indice_globale_voisin = (indice_i_ref + 1) * Colonnes + indice_j_ref;
    }
    else if (voisin == 2)
    {
        if (indice_j_ref + 1 > Colonnes)
        {
            cout << "Pas de voisin Est" << endl;
        }
        else
            indice_globale_voisin = indice_i_ref * Colonnes + (indice_j_ref + 1);
    }
    else if (voisin == 3)
    {
        if (indice_j_ref - 1 < 0)
            cout << "Pas de voisin Ouest" << endl;
        else
            indice_globale_voisin = indice_i_ref * Colonnes + (indice_j_ref - 1);
    }
    return indice_globale_voisin;
}

void Graph::affiche_graph()
{
    for (int i = 0; i < Lignes; i++)
    {
        for (int j = 0; j < Colonnes; j++)
        {
            Noeud Noeud_courant = grille_sommet[i * Colonnes + j];
            Noeud_courant.affiche_noeud();
            if (j < Colonnes - 1)
                cout << "\033[1;" << 1 << "m"
                     << "=="
                     << "\033[0m";
        }
        cout << endl;
        cout << endl;
        // TODO : On peut faire un affiche pour || qui lie les noeuds au dessus.
    }
}
void Graph::met_tous_les_noeuds_blanc()
{
    char couleur_blanc = 'b';
    for (int i = 0; i < Lignes * Colonnes; i++)
        grille_sommet[i].set_couleur(couleur_blanc);
}
void Graph::Astar(Noeud &depart, Noeud &arrive)
{
    // Met tous les noeuds en blanc.
    met_tous_les_noeuds_blanc();

    // Tableau dans lequelle on va mettre toutes les distances pour chaque noeud par rapport au noeud de depart.
    int tab_distance[Lignes * Colonnes] = {-1};

    // (Noeud, Distance).
    pair<int, int> pair_Noeud_distance;

    // File de priorité indexé.
    // Sa clé est le Noeud identifié par sa position.
    // Sa valeur est la distance que l'on met dans le tableau de dist.
    indexed_priority_queue<int, int> q;

    // (depart, 0)
    //pair_indice_distance = make_pair(indice_Noeud(depart), 0);

    // On défini le parent du noeud de depart à lui même pour ne pas avoir d'erreur lorsque l'on va faire le chemin vers l'origine depuis la fin.
    depart.indice_parent = indice_Noeud(depart);
    ;
    // On défini sa distance à 0 car c'est le départ.
    depart.distance = 0;

    // On pousse dans la file (depart, 0).
    q.push(indice_Noeud(depart), 0);
    // On commence le parcours en largeur.
    while (!q.empty())
    {
        // On stock la pair (Noeud, dist) que l'on étudie.
        pair_Noeud_distance = q.top();
        // Defile
        q.pop();

        Noeud Noeud_courant = grille_sommet[pair_Noeud_distance.first];

        if (arrive == Noeud_courant)
        {
            cout << "========= Fin de l'algo ===============" << endl;
            return;
        }

        // On ajoute la distance dans le tableau du noeud.
        tab_distance[indice_Noeud(Noeud_courant)] = pair_Noeud_distance.second;

        // Comme on est en train de le traiter on passe le noeud en gris.
        Noeud_courant.set_couleur('g');

        // On va parcourir un tab de voisin via la procédure ajoute_noeud_voisin qui va nous le générer !!
        ajoute_noeud_voisin(Noeud_courant, arrive, q, tab_distance);
        cout << "La taille de la pile après check des voisins : " << q.size() << endl;
        q.display();
        // On a terminé de traiter les voisin du noeud n donc on ne reviendra pas sur ce noeud mais sur ces voisins.
        Noeud_courant.set_couleur('n');
    }
}

void Graph::ajoute_noeud_voisin(Noeud &n, Noeud &fin, indexed_priority_queue<int, int> &q, int tab_distance[])
{
    // On insère dans notre vecteur tous les voisins de n (Nord, Sud, Est, Ouest)
    for (int i = 0; i < 4; i++)
    { // On va de 0 à 3 car on va devoir insérer au maximum 4 Noeuds voisin de n.
        // On stock le noeud voisin sur lequel on est en train de travailler.
        int indice_voisin = indice_Noeud_voisin(n, i);
        Noeud Noeud_voisin = grille_sommet[indice_voisin];

        if (!(Noeud_voisin.get_couleur() == 'n') && !(indice_voisin == -1))
        { // Si on a pas traité le voisin.
            // Calcul du cout : distance n --> voisin
            Noeud_voisin.distance = Distance_voisin_noeud_3D(n, Noeud_voisin);

            // Ici on va ajouter la distance que l'on stock dans notre tableau de parcours depuis le noeud de départ de l'algo avec la distance que l'on vient de calculer depuis n et voisin.
            //int poid_n_voisin = tab_distance[indice_Noeud(n)] + Noeud_voisin.distance;

            // Ici on peut mettre l'option pour faire distance 2D ou 3D.
            // Calcul de l'heuristique par vol d'oiseau (distance eucli).
            Noeud_voisin.heuristique = Distance_voisin_noeud_3D(Noeud_voisin, fin) + Noeud_voisin.distance;

            // On calcule le cout approximatif pour le noeud.
            //Noeud_voisin.cout_noeud_voisin = poid_n_voisin + Noeud_voisin.heuristique;

            Noeud_voisin.cout_noeud_voisin = tab_distance[indice_Noeud(n)] + Noeud_voisin.distance;
            cout << "Noeud : " << indice_voisin << " Avec la Couleur " << Noeud_voisin.get_couleur() << endl;

            // On sauvegarde l'indice du parent pour refaire le trajet.
            Noeud_voisin.indice_parent = indice_Noeud(n);

            // Si la Distance entre n --> voisin est NULL ou que la distance entre voisin et

            //cout << "Hauteur du Noeud " << indice_voisin << " : " << Noeud_voisin.get_hauteur() << endl;
            //sleep(1);
            // On va regarder si le voisin est déjà présent dans notre file de priorité indexé.
            int distance_dans_file_voisin = q.getValueIndex(indice_voisin);
            cout << distance_dans_file_voisin << endl;
            if (distance_dans_file_voisin == -1)
            { // Si le voisin n'est pas dans la file.
                // On pousse le voisin sur la file.
                q.push(indice_voisin, Noeud_voisin.cout_noeud_voisin);
            }
            else
            {
                // Si la distance dans la file indexé est supérieur à celle que l'on vient de calculer alors on remplace l'ancienne valeur pour éviter de duppliquer les noeuds.
                if (distance_dans_file_voisin > Noeud_voisin.cout_noeud_voisin)
                {
                    // On met à jour la distance dans le file avec la nouvelle distance plus optimisé.
                    q.changeAtKey(indice_voisin, Noeud_voisin.cout_noeud_voisin);

                    tab_distance[indice_voisin] = Noeud_voisin.cout_noeud_voisin;
                }
            }
        }
    }
}
void Graph::test_regression()
{
    affiche_graph();
    Noeud depart = grille_sommet[0];
    Noeud fin = grille_sommet[(Lignes * Colonnes) - 1];

    Astar(depart, fin);

    affiche_graph();
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