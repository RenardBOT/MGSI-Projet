#ifndef GL_STRUCTS_HPP
#define GL_STRUCTS_HPP

#include <GL/gl.h>

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

// === Structures ===

/**
 * @brief Une structure un sommet par ses trois coordonnées
 */
typedef struct {
    // La coordonnée en x du point
    GLfloat x;
    // La coordonnée en y du point
    GLfloat y;
    // La coordonnée en z du point
    GLfloat z;
} vertex;

/**
 * @brief Une structure représentant une face par trois indices de sommets
 */
typedef struct {
    // L'indice du premier sommet de la face
    GLint v1;
    // L'indice du deuxième sommet de la face
    GLint v2;
    // L'indice du troisième sommet de la face
    GLint v3;
} face;

/**
 * @brief Fonction qui récupère le sommet d'une face à un indice donné
 *
 * @param index la valeur à récupérer entre 0 et 2
 * @param f la face qui contient les sommets
 * @return int l'indice du sommet
 */
int getVertex(int index, face *face);

/**
 * Fonction qui affiche un tableau de sommets
 *
 * @param vertices Tableau de sommets à afficher
 */
void printVertices(vector<vertex> &vertices);

/**
 * Fonction qui affiche un tableau de faces
 *
 * @param faces Tableau de faces à afficher
 */
void printFaces(vector<face> &faces);

#endif /* GL_STRUCTS_HPP */