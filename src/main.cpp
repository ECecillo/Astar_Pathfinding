#include "module/graph.h"
#include "module/indexed_priority_queue.h"

int main(void)
{
    string data_path = "./data/"; // Si on veut modifier le chemin vers le fichier.
    string file_name = "graph_init.txt";

    Graph test(data_path + file_name);
    // Les Tests sur le graph se font dans la procédure ci_dessous qui est à la fin du fichier graph.cpp
    test.test_regression();

    //Graph g=(10,10);
    //g(10,10);
    return 0;
}