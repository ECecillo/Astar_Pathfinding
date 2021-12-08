#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include "noeud.h"
#include "altitude.h"
#include <fstream>
#include <cassert>
#include <queue>
#include <vector>

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
    // Calcule la racine carré en O(log n)
    // cf(https://www.geeksforgeeks.org/square-root-of-an-integer/)
    Altitude floorSqrt(Altitude &x);

    // Fonction qui renvoie la distance Euclidienne entre le sommet Origine et le voisin voisin.
    // Return : Altitude qui est le type de la hauteur.
    Altitude Distance_voisin_noeud(Noeud &origine, Noeud &voisin);

    // Retourne l'indice globale d'un Noeud avec des coordo passés en paramètre.
    int indice_Noeud(const int & i, const int& j) const;

    // Renvoie le Noeud (indice globale) qui correspond aux coordo (i,0).
    int indice_Noeud_depuis_ligne(const int &i) const;

    // Renvoie le Noeud qui correspond aux coordo (j,0).
    int indice_Noeud_depuis_colonne(const int& j) const;

    // Retourne l'altitude d'un Noeud dont on a passé l'indice globale en paramètre.
    Altitude Altitude_Noeud(const int& n) const;

    // Prend en paramètre l'indice du noeud de ref et une chaine de cara pour savoir quelle voisin retourner (Nord, Sud, Est, Ouest).
    int indice_Noeud_voisin(Noeud& ref, string voisin) const;
    
    // Procédure qui prend un noeud n en paramètre et qui va mettre les Noeuds voisin à N dans un/e ....
    void ajoute_noeud_voisin(Noeud& n);

    // Algorithme A* pour explications cf le README.
    // depart : Le noeud de depart de l'algo.
    // arrive : Le noeud auxquels on veut aller.
    void retrouve_chemin(Noeud& depart, Noeud& arrive, vector<int>& plus_courte_distance);

    void met_tous_les_noeuds_blanc();

    // Affiche la valeur du sommet aux coordonnées (x,y).
    void affiche_graph();
private:
    Noeud *grille_sommet;
    int Lignes;
    int Colonnes;
};

#endif