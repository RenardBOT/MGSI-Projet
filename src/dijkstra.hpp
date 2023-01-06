#include <stdbool.h>
#include <iostream>
#include <vector>

#include "halfedge.hpp"

using namespace std;
/**
 * @brief Une structure permettant le déroulement de l'algorithme de Diijkstra
 */
struct dijSommet {
    // Indice du sommet
    int id;
    // Indice du sommet précedent le courant pour former le plus court chemin
    int origin;
    // Poids du plus court chemin au niveau de ce sommet
    double poids;
    // indice qui indique si le sommet a déjà été analysé ou pas
    bool marque;
};

/**
 * @brief Une structure contenant un half edge et son poids (distance d'un vertex à un autre)
*/
struct halfedge_ponderee {
    he_halfedge *half_edge;
    float poids;
};

// === Fonctions ===

/**
 * Fonction qui prend en entrée le tableau half-edge, une origine et une destination
 * et qui calcul le plus cours chemin sur ce tableau,
 * Flag à 1 : calcul pondéré par la distance entre les sommets
 * Flag à 0 : calcul non pondéré par la distance entre les sommets
 * Renvoie un vecteur contenant la suite des sommet constituant le plus cours chemin
 */
vector<int> buildDijkstra(vector<he_halfedge *> HalfEdges, vector<he_vertex *> Sommets, int origine, int destination, int flag);

/**
 * Fonction qui construit le tableau qui contiendra toute les informations
 * Flag à 1 = calcul pondéré par la distance entre les sommets
 * Flag à 0 = calcul non pondéré par la distance entre les sommets
 * concernant le calcul du plus court chemin par Dijkstra
*/
void construire(vector<he_halfedge *>, int origine, int flag);

/**
 * Fonction déterminant quel sommet sera analysé ensuite en fonction du poids et
 * du marquage des sommet dans le tableau de Dijkstra.
 * Renvoie l'id du sommet à analyser, -1 si il n'en existe pas.
*/
int selection();

/**
 * Fonction affichant le tableau dijSommet
*/
void afficheDijSommet();