#ifndef OBJ_HPP
#define OBJ_HPP

#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

// === Structures ===

/**
 * @brief Une structure représentant les coordonnées d'un point du format obj
 */
struct v{
    // La coordonnée en x du point 
    float x;
    // La coordonnée en y du point
    float y;
    // La coordonnée en z du point
    float z;
};

/**
 * @brief Une structure représentant une face du format obj
 */
struct f{
    // L'indice du premier sommet de la face
    int v1;
    // L'indice du deuxième sommet de la face
    int v2;
    // L'indice du troisième sommet de la face
    int v3;
};


// === Fonctions ===

/**
 * Fonction qui lit un fichier .obj et qui remplit les vecteurs de sommets, faces et demi-arête passés en paramètre
 *
 * @param filename Nom du fichier .obj à lire
 * @param vertices Vecteur de sommets à remplir (voir la structure v dans obj.hpp)
 * @param faces Vecteur de faces à remplir (voir la structure f dans obj.hpp)
 * @return void
 */
void readObjFile(const char *filename, vector<v> &vertices, vector<f> &faces);

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
