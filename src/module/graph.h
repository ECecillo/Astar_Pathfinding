#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include "noeud.h"
#include "altitude.h"
#include <fstream>
#include <cassert>
#include <queue>
#include <vector>
#include "math.h"
#include "indexed_priority_queue.h"
#include <unistd.h>
#include <functional>

// Structure de donnée que l'on passera comme argument de la file de priorité pour classer cette dernière selon les éléments présents dans des listes.
struct Comparateur_paire
{
    bool operator()(const pair<int,int>&p1, const pair<int,int>& p2)
    { return p1.second > p2.second; }
};

class Graph
{
public:
    Graph();
    // NomFichier : Le nom du fichier qui va remplir le graph.
    Graph(string nomFichier);
    ~Graph();

    // ======= Procédures et Fonctions du module Graph.
    
    // Procédure qui va lire un fichier en définissant les données membres de la classe.
    void lecture_fichier_graph(string nomFichier); 
    
    // Fonction qui renvoie la distance Euclidienne entre le sommet Origine et le sommet voisin en fonction de son dénivelé.
    // Retourne la distance.
    int Distance_voisin_noeud_3D(Noeud &origine, Noeud &voisin);


    // Fonction qui renvoie la distance Euclidienne entre le sommet Origine et le sommet voisin selon leur position.
    // Return : Altitude qui est le type de la hauteur.
    int Distance_voisin_noeud_2D(Noeud &origine, Noeud &voisin);

    // Retourne l'indice globale d'un Noeud avec des coordo passés en paramètre.
    int indice_Noeud(Noeud& n) const;

    // Renvoie le Noeud (indice globale) qui correspond aux coordo (i,0).
    int indice_Noeud_depuis_ligne(Noeud& n) const;

    // Renvoie le Noeud qui correspond aux coordo (j,0).
    int indice_Noeud_depuis_colonne(Noeud& n) const;

    // Retourne l'altitude d'un Noeud dont on a passé l'indice globale en paramètre.
    Altitude Altitude_Noeud(Noeud& n) const;

    // Prend en paramètre l'indice du noeud de ref et une chaine de cara pour savoir quelle voisin retourner (Nord, Sud, Est, Ouest).
    int indice_Noeud_voisin(Noeud& ref, int& voisin) const;    

    // Algorithme A*.
    // depart : Noeud de depart.
    // fin : Noeud où on veut arriver.
    // Chemin : Tableau d'indice (entier) qui va nous dire quelle est le chemin opti trouvé par l'algo. 
    void Astar(Noeud& depart, Noeud& arrive, vector<int>&Chemin, int& choix_heuristique);

    // Cette procédure va gérer les cas pour les voisins du noeud courant que l'on défilé dans la boucle tant que de A*
    // fin : Noeud vers lequel va notre algo.
    // PQ : Priority queue.
    // verifie : Tableau de bool qui va nous dire si on a déjà vérifié le noeud (comme set couleur en noir ne mettait pas vraiment les noeuds en noir on a remplacé par un tab bool).
    // choix_heuristique : Choix du calcul de la distance eucli en prennant en compte la hauteur du sommet ou pas.
    void ajoute_noeud_voisin(Noeud& n, Noeud& fin, priority_queue< pair<int, int>, vector <pair<int,int>>, Comparateur_paire> &PQ, bool verifie[], int& choix_heuristique);

    // Modifie la couleur de tous les noeuds dans la grille et les mets en blanc.
    // Utile si on fais d'autre calcul après un première algo A*
    void met_tous_les_noeuds_blanc();

    // Affiche la valeur du sommet aux coordonnées (x,y).
    void affiche_graph() const;

    // Affiche le chemin depuis le noeud de départ jusqu'au noeud Courant.
    void affiche_chemin_noeud( Noeud& depart,  Noeud& courant) const;

    // Affiche une file de priorité passé en paramètre.
    void affiche_file_priorite(priority_queue< pair<int, int>, vector <pair<int,int>>, Comparateur_paire>&) const;

    // Procédure pour effectuer les tests.
    void test_regression(int choix_Heuristique);

private:
    // Tableau de Noeud qui sera notre grille.
    Noeud *grille_sommet;
    // Nombres de lignes de la grille.
    int Lignes;
    // Nombres de Colonnes de notre grille.
    int Colonnes;
};

#endif