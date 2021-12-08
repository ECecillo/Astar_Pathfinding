#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include "noeud.h"
#include "altitude.h"
#include <fstream>
#include <cassert>

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

    int indice_Noeud(const int & i, const int& j) const;

    // Renvoie le Noeud (indice globale) qui correspond aux coordo (i,0).
    int indice_Noeud_depuis_ligne(const int &i) const;

    // Renvoie le Noeud qui correspond aux coordo (j,0).
    int indice_Noeud_depuis_colonne(const int& j) const;

    Altitude Altitude_Noeud(const int& n) const;

    // Prend en paramètre l'indice du noeud de ref et une chaine de cara pour savoir quelle voisin retourner (Nord, Sud, Est, Ouest).
    int indice_Noeud_voisin(Noeud& ref, string voisin) const;

    // Affiche la valeur du sommet aux coordonnées (x,y).
    void affiche_graph();
private:
    Noeud *grille_sommet;
    int Lignes;
    int Colonnes;
};

#endif