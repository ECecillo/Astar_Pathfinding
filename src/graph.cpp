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
            // cout << "Pas de voisin Nord" << endl;
        }
        else
            indice_globale_voisin = (indice_i_ref - 1) * Colonnes + indice_j_ref;
    }
    else if (voisin == 1)
    {
        if (indice_i_ref + 1 > Lignes)
        {
            // cout << "Pas de voisin Sud" << endl;
        }
        else
            indice_globale_voisin = (indice_i_ref + 1) * Colonnes + indice_j_ref;
    }
    else if (voisin == 2)
    {
        if (indice_j_ref + 1 > Colonnes)
        {
            // cout << "Pas de voisin Est" << endl;
        }
        else
            indice_globale_voisin = indice_i_ref * Colonnes + (indice_j_ref + 1);
    }
    else if (voisin == 3)
    {
        if (indice_j_ref - 1 < 0)
        {
            // cout << "Pas de voisin Ouest" << endl;
        }
        else
            indice_globale_voisin = indice_i_ref * Colonnes + (indice_j_ref - 1);
    }
    return indice_globale_voisin;
}

void Graph::affiche_graph()const
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
void Graph::Astar(Noeud &depart, Noeud &arrive, vector<int> &Chemin, int& choix_heuristique)
{
    // Met tous les noeuds en blanc.
    met_tous_les_noeuds_blanc();
    bool verifie[Lignes * Colonnes];
    for (auto &i : verifie)
    {
        i = false;
    }
    // (Noeud, Distance).
    pair<int, int> pair_Noeud_distance(indice_Noeud(depart), 0);

    // File de priorité.
    // Sa clé est l'indice gloable d'un noeud.
    // Sa valeur est sa distance + tab_distance depuis origine.
    priority_queue<pair<int, int>, vector<pair<int, int>>, Comparateur_paire> PQ;

    // (depart, 0)
    // pair_indice_distance = make_pair(indice_Noeud(depart), 0);
    // On ajoute la distance dans le tableau du noeud.

    // On défini le parent du noeud de depart à 0 car c'est son indice dans la grille.
    depart.indice_parent = 0;
    ;
    // On défini sa distance à 0 car c'est le départ.
    depart.distance = 0;
    depart.cout_total = 0;
    depart.cout = 0;
    // On pousse dans la file (depart, 0).
    PQ.push(pair_Noeud_distance);
    // On commence le parcours en largeur.
    while (!PQ.empty())
    {
        // On stock la pair (indice_Noeud, dist) que l'on étudie.
        pair_Noeud_distance = PQ.top();
        // Defile
        PQ.pop();

        Noeud &Noeud_courant = grille_sommet[pair_Noeud_distance.first];

        if (indice_Noeud(arrive) == indice_Noeud(Noeud_courant))
        {
            Noeud temp = Noeud_courant; // On va parcourir tous les ancêtres du Noeud courant.
            Chemin.push_back(indice_Noeud(temp));
            while (temp.indice_parent != 0)
            {
                Chemin.push_back(temp.indice_parent);
                temp = grille_sommet[temp.indice_parent]; // On récupère le Noeud qui est à l'indice Parent.
            }
            cout << "========= Fin de l'algo ===============" << endl;
            return;
        }
        // Si le noeud que l'on regarde a déjà évalué mais que sa valeur actuel est inférieur à celle dans le tableau alors on doit le traiter car c'est potentiellment un meilleur chemin.

        // On a fini de traiter le Noeud Courant et on ne reviendra plus dessus.

        // On va parcourir un tab de voisin via la procédure ajoute_noeud_voisin qui va nous le générer !!
        ajoute_noeud_voisin(Noeud_courant, arrive, PQ, verifie, choix_heuristique);
        verifie[pair_Noeud_distance.first] = true;

        // On va afficher le chemin depart au noeud avec sa distance et le chemin depart -> pred.
        affiche_chemin_noeud(depart, Noeud_courant);        
         //affiche_file_priorite(PQ);
         //affiche_graph();
         //sleep(1);
    }
}
void Graph::affiche_chemin_noeud(Noeud& depart, Noeud& courant) const
{
    cout << "[  " << indice_Noeud(depart) << " ->  " << indice_Noeud(courant) << " ]  : " << courant.cout << " | ";

        if (indice_Noeud(depart) != indice_Noeud(courant))
        {
            // Pour récup les indice parent sans les overwrite par inadvertance.
            int indice_pred = courant.indice_parent;

            vector<int> liste_pred = {indice_Noeud(courant)};
            while (indice_pred != indice_Noeud(depart))
            {
                liste_pred.emplace(liste_pred.begin(), indice_pred);
                indice_pred = grille_sommet[indice_pred].indice_parent;
            }
            cout << indice_Noeud(depart);
            for (auto &indice_de_noeud : liste_pred)
            {
                cout << " -> " << indice_de_noeud;
            }
            cout << endl;
        }
        else
        {
            cout << indice_Noeud(depart);
            cout << endl;
        }
}

void Graph::ajoute_noeud_voisin(Noeud &n, Noeud &fin, priority_queue<pair<int, int>, vector<pair<int, int>>, Comparateur_paire> &q, bool verifie[], int& choix_heuristique)
{
    // On insère dans notre vecteur tous les voisins de n (Nord, Sud, Est, Ouest)
    // On pourrait optimisé ici en modifiant la boucle par quelque chose qui traite que les noeuds qui sont valides pour notre algo.
    for (int i = 0; i < 4; i++)
    { // On va de 0 à 3 car on va devoir insérer au maximum 4 Noeuds voisin de n.
        // On stock le noeud voisin sur lequel on est en train de travailler.
        int indice_voisin = indice_Noeud_voisin(n, i);

        Noeud &Noeud_voisin = grille_sommet[indice_voisin];
        if (!(indice_voisin == -1))
        {
            if (!(verifie[indice_voisin]))
            { // Si on a pas traité le voisin <=> Noeud_voisin.couleur == 'n' ?

                // On va stocker les calculs liés au Noeud Voisin avant de les mettre dans ses données membres ce qui pourraient faussés les futures calculs.
                int tab_calcul_Noeud[3] = {
                    Distance_voisin_noeud_3D(n, Noeud_voisin),                          // Distance (n,v) + distance du dernier noeud.
                    tab_calcul_Noeud[0] + n.cout,                                       // Distance depart au voisin actuel = distance (n-->Noeud_voisin) + distance N(distance depuis origine).
                    Distance_voisin_noeud_2D(Noeud_voisin, fin) + tab_calcul_Noeud[1]}; // Cout totale = Heuristique + Cout.

                //cout << "Calcule du Noeud " << indice_voisin << " : Distance(" << tab_calcul_Noeud[0] << ") + depart_noeud(" << n.cout << ") où noeud = " << indice_Noeud(n) << endl;
                cout << "g(h) = " << tab_calcul_Noeud[1] << " et f(h) = " << tab_calcul_Noeud[2] << endl;
                // Si la Distance entre n --> voisin est NULL ou que la distance entre voisin et
                if (Noeud_voisin.get_couleur() == 'g')
                { 
                    // Si le voisin que l'on regarde est dans la file alors on doit voir si le cout que l'on vient de calculer est meilleur ou moins bon que celui qui est dans la file.

                    //cout << "Je suis le noeud " << indice_Noeud(Noeud_voisin) << " gris je regarde si le Noeud dans la File est meilleur ou pas" << endl;

                    if (tab_calcul_Noeud[1] < Noeud_voisin.cout && Noeud_voisin.cout != 0)
                    { // Si le cout que l'on vient de calculer est meilleur que celui qui a déjà été calculé et différent de 0 car c'est la valeur de base que l'on donne dans le constructeur d'un noeud et c'est impossible d'avoir un cout de 0.

                        //cout << "Le noeud dans la file semble meilleur et différent de 0 ces valeurs " << " Cout calculé " << tab_calcul_Noeud[1] << " | " << "Cout dans la file " << Noeud_voisin.cout << endl;

                        Noeud_voisin.distance = tab_calcul_Noeud[0];

                        Noeud_voisin.cout = tab_calcul_Noeud[1];

                        Noeud_voisin.cout_total = tab_calcul_Noeud[2];

                        // On remplace son ancien parent par le nouveau parent plus avantageux.
                        Noeud_voisin.indice_parent = indice_Noeud(n);

                        pair<int, int> nouvelle_pair(indice_voisin, Noeud_voisin.cout_total);

                        q.push(nouvelle_pair);
                    }
                    // Si la valeur dans le tab_distance était plus petite on ne change rien !
                }
                else
                {
                    // On a jamais visité ce Noeud.
                    Noeud_voisin.distance = tab_calcul_Noeud[0];

                    Noeud_voisin.cout = tab_calcul_Noeud[1];

                    Noeud_voisin.cout_total = tab_calcul_Noeud[2];

                    // On le passe dans la file donc il devient gris.
                    Noeud_voisin.set_couleur('g');

                    pair<int, int> nouvelle_pair(indice_voisin, Noeud_voisin.cout_total);
                    // On pousse le nouveau Noeud qui a un meilleur cout.
                    q.push(nouvelle_pair);
                    // On lui met comment parent le noeud qui a permis de trouver ce voisin.
                    Noeud_voisin.indice_parent = indice_Noeud(n);
                }
            }
        }
    }
}

void Graph::affiche_file_priorite(priority_queue<pair<int, int>, vector<pair<int, int>>, Comparateur_paire> &PQ) const
{
    cout << endl;
    priority_queue<pair<int, int>, vector<pair<int, int>>, Comparateur_paire> temp = PQ;
    while (!temp.empty())
    {
        pair<int, int> tmp;
        tmp = temp.top();
        temp.pop();
        cout << "  ( " << tmp.first << ", "
             << tmp.second << " ) " << endl;
    }
    cout << "_______________" << endl;
    cout << "(index, value)" << endl;
    cout << "key-value pairs" << endl;
    cout << endl;
}

void Graph::test_regression(int choix_Heuristique)
{
    affiche_graph();
    Noeud depart = grille_sommet[0];
    Noeud fin = grille_sommet[(Lignes * Colonnes) - 1];
    vector<int> Chemin_Algo;
    Astar(depart, fin, Chemin_Algo, choix_Heuristique);

    affiche_graph();
    cout << "Le chemin finale est :" << endl;
    for (auto &indice_chemin : Chemin_Algo)
    {
        cout << indice_chemin << " ";
    }
    cout << indice_Noeud(depart) << endl;
}   