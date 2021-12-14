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
## Exemple de l'application d'un graph avec l'algo A*
---
![Image Parcours Astar](https://media.geeksforgeeks.org/wp-content/uploads/a_-search-algorithm-1.png)

---

# Représentation de la grille

Pour accéder à la première ligne du tableau 1D on fait :
**Graph[C * i + j]**
\
**C** : Nombres de Colonnes de la grille.\
**i** : Numéro de la ligne\
**j** : Numéro de la colonne.

\
<pre>
 (0,0) ---- (0,1) ------ (0,2) ---- (0,3)
   |          |            |          |
 (1,0) ---- (1,1) ------ (1,2) ---- (1,3)
   |          |            |          |
 (2,0) ---- (2,1) ------ (2,2) ---- (1,3)
   |          |            |          |
 (3,0) ---- (3,1) ------ (3,2) ---- (3,3)
</pre>

 Si on décide de mettre dans un fichier :

 15 24 La ligne est 1 ici sera pour la hauteur(L) la largeur(C)

 Pour chaque ligne on donne les valeurs qui vont aller dans les cases de la grille ci-dessus.

 Exemple :
 12 34 5 10 5 15

 On aura pour la première ligne de la grille :

<pre>
(0,0) ---- (0,1) ---- (0,2) ---- (0,3) ---- (0,3) ---- (0,3) ---- (0,3)
  0         12         34          5          10         5         15
</pre>

## Code source du Graph
---
[Arbre_RN.cpp](https://forge.univ-lyon1.fr/p1805901/tp8_graph_dijsktra/-/blob/main/src/graph.cpp)
