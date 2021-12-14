#include "module/graph.h"

// Pre declaration pour le constructeur.
void menu_programme_principale(string& nomF);

int main(void)
{
    string data_path = "./data/"; // Si on veut modifier le chemin vers le fichier.
    string file_name = data_path + "graph_init.txt";

    // Les Tests sur le graph se font dans la procédure ci_dessous qui est à la fin du fichier graph.cpp
    menu_programme_principale(file_name);
    return 0;
}

void menu_programme_principale(string & nomFichier)
{
    // Menu pour choisir l'arbre que l'on voudra tester (à faire à la fin).
    char choix_utilisateur;
    Graph test(nomFichier);
    bool boucle_programme = true;
    while (boucle_programme)
    {
        cout << "\033[2J\033[1;1H"; // Nettoie le terminale et remet le cursor à sa place de départ.
        cout << "============ MENU PRINCIPALE =================" << endl;
        cout << "Veuillez choisir votre style de Voyage : " << endl;
        cout << " 1 - Montagne ? c'est quoi ? " << endl;
        cout << " 2 - Faut pas trop que ça monte." << endl;
        cin >> choix_utilisateur;
        if (choix_utilisateur == '1')
        {
            // Graph avec la distance Heuristique en 2D.
            test.test_regression(1);
            boucle_programme = false;
        }
        else if (choix_utilisateur == '2')
        {
            //
            test.test_regression(2);
            boucle_programme = false;
        }
        else
        {
            cout << "Votre choix n'est pas valide" << endl;
        }
    }
}
