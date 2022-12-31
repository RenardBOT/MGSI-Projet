#ifndef HALFEDGE_HPP
#define HALFEDGE_HPP

#include <iostream>
#include <vector>

#include "obj.hpp"

using namespace std;

// === Structures ===

struct vertex;
struct face;
struct halfedge;

/**
 * @brief Une structure représentant les coordonnées d'un sommet du modèle
 * half-edge
 */
struct vertex {
    int id;
    // La coordonnée en x du point
    float x;
    // La coordonnée en y du point
    float y;
    // La coordonnée en z du point
    float z;
};

/**
 * @brief Une structure représentant une face du modèle half-edge
 */
struct face {
    // L'indice d'une demi-arête de la face
    int id;
    halfedge *half_edge;
};

/**
 * @brief Une structure représentant une demi-arête du modèle half-edge
 */
struct halfedge {
    int id;
    // Indice de l'origine du halfedge
    vertex *origin;
    // Indice du halfedge suivant
    halfedge *next;
    // Indice du halfedge précédent
    halfedge *prev;
    // Indice de la demi-arête opposée
    halfedge *twin;
    // Indice de la face dont la demi-arête fait partie
    face *incident_face;
};

// === Fonctions ===

/**
 * Fonction qui prend en entrée un tableau de v et un tableau de faces et qui
 * remplit les vecteurs de sommets, faces et demi-arêtes passés en paramètre
 *
 */
void buildHalfEdge(vector<v> &verticesIn, vector<f> &facesIn,
                   vector<vertex *> &verticesOut, vector<face *> &facesOut,
                   vector<halfedge *> &halfedgesOut);

int getVertexId(vertex *v);
int getFaceId(face *f);
int getHalfedgeId(halfedge *he);
void printVertices(vector<vertex *> &vertices);
void printFaces(vector<face *> &faces);
void printHalfedges(vector<halfedge *> &halfedges);

#endif /* HALFEDGE_HPP */