#include "module/read_write_file.h"

RW_File::RW_File()
{
    Nb_Lignes_graph = 0;
    Nb_Colonnes_graph = 0;
    nom_fichier = "";
}
RW_File::RW_File(int &L, int &C, string &f) : 
Nb_Lignes_graph(L), Nb_Colonnes_graph(C), nom_fichier(f)
{}

RW_File::RW_File(string &file) : nom_fichier(file)
{}