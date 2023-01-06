#include <cstdlib>
#include <iostream>
#include <vector>

#include "a_star.hpp"
#include "display.hpp"
#include "halfedge.hpp"
#include "obj.hpp"

int main(int argc, char **argv) {
    // VerticesIn et facesIn sont des vecteurs de structures vertex et fface définies
    // dans gl_structs. Ils contiendront les sommets et faces comme lues dans le fichier obj.
    vector<vertex> verticesIn;
    vector<face> facesIn;

    // initialise un tableau de vertex qui représente un chemin de points. La trajectoire à afficher sur le maillage.
    vector<vertex> path = {
        {1.0, 4.0, 0.0},
        {3.0, 4.0, 0.0},
        {4.0, 2.0, 0.0},
        {3.0, 0.0, 0.0}};

    // verticesOut, facesOut et halfedgesOut sont des vecteurs de pointeurs vers
    // les structures vertex, face et halfedge définies dans halfedge.hpp. Ils
    // contiendront les sommets, faces et demi-arêtes du maillage half-edge.
    vector<he_vertex *> verticesOut;
    vector<he_face *> facesOut;
    vector<he_halfedge *> halfedgesOut;

    // On lit le fichier .obj et on remplit les vecteurs verticesIn et facesIn
    readObjFile("meshes/vache.obj", verticesIn, facesIn);

    // On remplit les 3 vecteurs du maillage half-edge à partir des vecteurs
    // verticesIn et facesIn
    buildHalfEdge(verticesIn, facesIn, verticesOut, facesOut, halfedgesOut);

    // Section d'affichage pour debug
    /*
    printVertices(verticesIn);
    cout << "*************" << endl;
    printFaces(facesIn);
    cout << "*************" << endl;
    printVertices(verticesOut);
    cout << "*************" << endl;
    printFaces(facesOut);
    cout << "*************" << endl;
    printHalfedges(halfedgesOut);
    */

    bindExternalArrays(verticesIn, facesIn, path);
    initDisplay();

    // Libération de la mémoire
    freeHalfEdge(verticesOut, facesOut, halfedgesOut);

    // Sortie du programme
    return 0;
}