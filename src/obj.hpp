#ifndef OBJ_HPP
#define OBJ_HPP

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "gl_structs.hpp"
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
 * @param zoom Facteur de zoom à appliquer aux sommets
 * @return void
 */
void readObjFile(const char *filename, vector<vertex> &vertices, vector<face> &faces, float zoom);

#endif /* OBJ_HPP */