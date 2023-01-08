#ifndef DISPLAY_HPP
#define DISPLAY_HPP

#include <GL/glew.h>

#include <SDL/SDL.h>

#include <cstdlib>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <vector>

#include "gl_structs.hpp"
#include "halfedge.hpp"
#include "obj.hpp"
#include "shader.hpp"

/* -------------------------------------------------------------------------- */
/*                         Constantes de préprocesseur                        */
/* -------------------------------------------------------------------------- */

// Hauteur de la fenêtre
#define HEIGHT 900
// Largeur de la fenêtre
#define WIDTH 1200

/* -------------------------------------------------------------------------- */
/*                                  Méthodes                                  */
/* -------------------------------------------------------------------------- */

/* ------------- Initialisation des shaders, buffers et matrices ------------ */

/**
 * @brief Association d'un id à chaque shader et qui les compile
 */
void genShaders(void);

/**
 * @brief Génération des matrices MVP (Model, View, Projection) pour le rendu de la scène
 */
void genMatrices(void);

/**
 * @brief Génération des VAO, VBO et IBO servant à afficher le maillage et la trajectoire
 */
void genBuffers(void);

/**
 * @brief Remplissage des VAO, VBO et IBO avec les données du maillage
 */
void fillMeshBuffers(void);

/**
 * @brief Remplissage des VAO, VBO et IBO avec les données de la trajectoire
 */
void fillPathBuffers(void);
/**
 * @brief Remplissage des VAO, VBO et IBO avec les données du maillage de la sphère
 */
void fillMeshSphereBuffers(void);

/**
 * @brief Fonction qui remplit VAO, VBO et IBO avec les données du maillage et de la trajectoire
 * @param mesh_vertices Tableau de coordonnées des sommets du maillage (cf structure vertex dans gl_structs.hpp)
 * @param mesh_faces Tableau d'indices des sommets des faces triangulaires du maillage (cf structure face dans gl_structs.hpp)
 * @param path_vertices Tableau de coordonnées des points de la trajectoire (cf structure vertex dans gl_structs.hpp)
 * @param mesh_vertices Tableau de coordonnées des sommets du maillage de la sphère (cf structure vertex dans gl_structs.hpp)
 * @param mesh_faces Tableau d'indices des sommets des faces triangulaires du maillage de la sphère (cf structure face dans gl_structs.hpp)
 */
void bindExternalArrays(const vector<vertex> &mesh_vertices, const vector<face> &mesh_faces, const vector<vertex> &path_vertices, const vector<vertex> &sphere_vertices_in, const vector<face> &sphere_faces_in);

/* ------------------- Affichage de l'interface graphique ------------------- */

/**
 * @brief Initialisation de l'interface graphique et lecture de la boucle principale.
 */
int initDisplay(void);

/**
 * @brief Affichage la scène à l'écran à chaque itération de la boucle principale.
 */
void display(void);

/**
 * @brief Fonction qui gère les évènements clavier
 * @param event Évènement clavier
 */
void keyboard(SDL_Event event);

#endif /* DISPLAY_HPP */
