********************************************************************************************
# Projet de LIFAP6 : Graphe d’un terrain, recherche de chemins entre deux points
****************************************************************************************

# Remarques Avant de Commencer
--- 

Avant de lire ce Readme et de compiler ce programme, il est à noter que ce dernier a été testé sur un seul **graph[10 * 10]** et que le résultat obtenu semble plus ou moins valable.
\
\
Cependant par manque de temps, il est fort probable que cette algorithme soit aussi glouton que Dijsktra.  
\
Dans `module/` se trouve un fichier `indexed_priority_queue.h` qui devait à l'origine faire office de File de priorité mais due au manque de temps cette structure de donnée n'a pas pu être utilisé à cause d'un bug lié au TAS Binaire utilisé par la File.

# Membres

|  Nom|Prénom  |Numéros étudiant  |
|--|--|--|
| **CECILLON**  |Enzo  |11805901  |
| **MIKLOVANA** | Rica |p1413172 |


# Commandes Utiles
---
### Pour compiler 

`make`
## Netttoyer le répertoire

`make clean`
\
**ou pour supprimer les dossiers bin, data et object** 
\
`make mrproper`


# Explications Algorithme A*
---

### Sources

[Rappel sur l'algorithme](https://fr.wikipedia.org/wiki/Algorithme_A*)

[Explication de l'algorithme en vidéo](https://www.youtube.com/watch?v=pSqmAO-m7Lk&t=456s)

[Article de Vincent Nivolier sur Dijsktra et A*](https://perso.liris.cnrs.fr/vincent.nivoliers/lifap6/Supports/Cours/graph_traversal.html)

[Autre Ressource utilisé lors de l'écriture du code](https://khayyam.developpez.com/articles/algo/astar/)
## Exemple d'abre Rouge et Noir
---
![Image Parcours Astar](https://media.geeksforgeeks.org/wp-content/uploads/a_-search-algorithm-1.png)

---

## Code source du Graph
---
[Arbre_RN.cpp](https://forge.univ-lyon1.fr/p1805901/tp8_graph_dijsktra/-/blob/main/src/graph.cpp)
