#include <cstdlib>
#include <iostream>
#include <vector>

#include "display.hpp"
#include "halfedge.hpp"
#include "obj.hpp"

int main(int argc, char **argv) {
    // VerticesIn et facesIn sont des vecteurs de structures v et f définies
    // dans obj.hpp Ils contiendront les sommets et faces du fichier .obj
    vector<vertex> verticesIn;
    vector<face> facesIn;

    // verticesOut, facesOut et halfedgesOut sont des vecteurs de pointeurs vers
    // les structures vertex, face et halfedge définies dans halfedge.hpp. Ils
    // contiendront les sommets, faces et demi-arêtes du maillage half-edge.
    vector<he_vertex *> verticesOut;
    vector<he_face *> facesOut;
    vector<he_halfedge *> halfedgesOut;

    // On lit le fichier .obj et on remplit les vecteurs verticesIn et facesIn
    readObjFile("meshes/hexagone.obj", verticesIn, facesIn);

    // On remplit les 3 vecteurs du maillage half-edge à partir des vecteurs
    // verticesIn et facesIn
    buildHalfEdge(verticesIn, facesIn, verticesOut, facesOut, halfedgesOut);

    // On affiche pour débug
    printVertices(verticesOut);
    cout << "*************" << endl;
    printFaces(facesOut);
    cout << "*************" << endl;
    printHalfedges(halfedgesOut);

    // exit(EXIT_SUCCESS);

    initDisplay(argc, argv);

    // Libération de la mémoire
    freeHalfEdge(verticesOut, facesOut, halfedgesOut);
}