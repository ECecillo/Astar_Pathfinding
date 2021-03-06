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

// Structure de donnée que l'on passera comme argument de la file de priorité pour classer cette dernière.
struct Comparateur_paire
{
    bool operator()(const pair<int,int>&p1, const pair<int,int>& p2)
    { return p1.second > p2.second; }
};

class Graph
{
public:
    // L : Le nombre de ligne.
    // C : le nombre de Colonne pour le tableau.
    Graph();
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

    //
    // fin : Noeud vers lequel va notre algo.
    // tab_distance : le tableau avec toutes les distances depuis le noeud de depart de l'algo.
    void ajoute_noeud_voisin(Noeud& n, Noeud& fin, priority_queue< pair<int, int>, vector <pair<int,int>>, Comparateur_paire> &PQ, bool verifie[]);

    // Algorithme A*.
    // depart : Noeud de depart.
    // fin : Noeud où on veut arriver.
    // Chemin : Tableau d'indice (entier) qui va nous dire quelle est le chemin opti trouvé par l'algo. 
    void Astar(Noeud& depart, Noeud& arrive, vector<int>&Chemin);

    void met_tous_les_noeuds_blanc();

    // Affiche la valeur du sommet aux coordonnées (x,y).
    void affiche_graph();

    void affiche_file_priorite(priority_queue< pair<int, int>, vector <pair<int,int>>, Comparateur_paire>&) const;

    void test_regression();

private:
    Noeud *grille_sommet;
    int Lignes;
    int Colonnes;
};

#endif