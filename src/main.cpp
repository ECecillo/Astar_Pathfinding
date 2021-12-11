#include "module/graph.h"
#include "module/indexed_priority_queue.h"

int main(void)
{
    string data_path = "./data/"; // Si on veut modifier le chemin vers le fichier.
    string file_name = "graph_init.txt";
    cout << data_path + file_name << endl;
    Graph test(data_path + file_name);
    cout << "Graph succes" << endl;
    test.affiche_graph();
    //Graph g=(10,10);
    //g(10,10);
    return 0;
}