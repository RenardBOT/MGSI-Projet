#include "gl_structs.hpp"

int getVertex(int index, face *face) {
    // On retourne l'indice du sommet correspondant à l'index passé en paramètre
    switch (index) {
        case 0:
            return face->v1;
        case 1:
            return face->v2;
        case 2:
            return face->v3;
        default:
            return -1;
    }
}

void printVertices(vector<vertex> &vertices) {
    // Pour chaque sommet du vecteur on affiche les coordonnées du sommet
    for (size_t i = 0; i < vertices.size(); i++) {
        cout << "v " << vertices[i].x << " " << vertices[i].y << " "
             << vertices[i].z << endl;
    }
}

void printFaces(vector<face> &faces) {
    // Pour chaque face du vecteur on affiche les indices des sommets de la face
    for (size_t i = 0; i < faces.size(); i++) {
        cout << "f " << faces[i].v1 << " " << faces[i].v2 << " " << faces[i].v3
             << endl;
    }
}