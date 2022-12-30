#ifndef OBJ_HPP
#define OBJ_HPP

#include <vector>

#include "mesh_structs.hpp"

using namespace std;

/**
 * Fonction qui lit un fichier .obj et qui remplit les vecteurs de sommets, faces et demi-arête passés en paramètre
 *
 * @param filename Nom du fichier .obj à lire
 * @param vertices Vecteur de sommets à remplir
 * @param faces Vecteur de faces à remplir
 * @param halfedges Vecteur de demi-arêtes à remplir
 * @return void
 */
void readObjFile(const char *filename, vector<vertex> &vertices, vector<face> &faces, vector<halfedge> &halfedges);

#endif /* OBJ_HPP */
