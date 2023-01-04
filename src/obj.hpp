#ifndef OBJ_HPP
#define OBJ_HPP

#include <GL/gl.h>

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "glstructs.hpp"

using namespace std;

// === Fonctions ===

/**
 * Fonction qui lit un fichier .obj et qui remplit les vecteurs de sommets,
 * faces et demi-arête passés en paramètre
 *
 * @param filename Nom du fichier .obj à lire
 * @param vertices Vecteur de sommets à remplir (voir la structure v dans
 * obj.hpp)
 * @param faces Vecteur de faces à remplir (voir la structure f dans obj.hpp)
 * @return void
 */
void readObjFile(const char *filename, vector<v> &vertices, vector<f> &faces);

/**
 * @brief Fonction qui récupère le sommet d'une face à un indice donné
 *
 * @param index la valeur à récupérer entre 0 et 2
 * @param f la face qui contient les sommets
 * @return int l'indice du sommet
 */
int getVertex(int index, f *face);

/**
 * Fonction qui affiche un tableau de sommets
 *
 * @param vertices Tableau de sommets à afficher
 */
void printV(vector<v> &vertices);

/**
 * Fonction qui affiche un tableau de faces
 *
 * @param faces Tableau de faces à afficher
 */
void printF(vector<f> &faces);

#endif /* OBJ_HPP */