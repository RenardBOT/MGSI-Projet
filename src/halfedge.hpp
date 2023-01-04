#ifndef HALFEDGE_HPP
#define HALFEDGE_HPP

#include <iostream>
#include <vector>

#include "gl_structs.hpp"
#include "obj.hpp"

using namespace std;

// === Structures ===

struct he_vertex;
struct he_face;
struct he_halfedge;

/**
 * @brief Une structure représentant les coordonnées d'un sommet du modèle
 * half-edge
 */
struct he_vertex {
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
struct he_face {
    // L'indice d'une demi-arête de la face
    int id;
    he_halfedge *half_edge;
};

/**
 * @brief Une structure représentant une demi-arête du modèle half-edge
 */
struct he_halfedge {
    int id;
    // Indice de l'origine du halfedge
    he_vertex *origin;
    // Indice du halfedge suivant
    he_halfedge *next;
    // Indice du halfedge précédent
    he_halfedge *prev;
    // Indice de la demi-arête opposée
    he_halfedge *twin;
    // Indice de la face dont la demi-arête fait partie
    he_face *incident_face;
};

// === Fonctions ===

/**
 * Fonction qui prend en entrée un tableau de v et un tableau de faces et qui
 * remplit les vecteurs de sommets, faces et demi-arêtes passés en paramètre
 *
 */
void buildHalfEdge(vector<vertex> &verticesIn, vector<face> &facesIn,
                   vector<he_vertex *> &verticesOut,
                   vector<he_face *> &facesOut,
                   vector<he_halfedge *> &halfedgesOut);

int getVertexId(he_vertex *v);
int getFaceId(he_face *f);
int getHalfedgeId(he_halfedge *he);
void printVertices(vector<he_vertex *> &vertices);
void printFaces(vector<he_face *> &faces);
void printHalfedges(vector<he_halfedge *> &halfedges);

#endif /* HALFEDGE_HPP */