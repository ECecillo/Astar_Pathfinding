#ifndef READ_H
#define READ_H

#include <string>
#include <iostream>
#include <fstream>

using namespace std;

// Permettra de créer un lire un fichier pour initialiser un graphe.
class RW_File
{
public:
    RW_File();
    // On utilisera les champs L
    RW_File(int &L, int &C, string& f);
    // On utilisera que le champ file pour lire le fichier.
    RW_File(string& file);
    ~RW_File();

private:
    // Nombre de ligne du graph si on le définit dans un nouveau fichier.
    int Nb_Lignes_graph;
    // Nombre de colonne.
    int Nb_Colonnes_graph;
    // Le nom du fichier.
    string nom_fichier;
};

#endif