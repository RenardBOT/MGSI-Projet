#include "obj.hpp"

void readObjFile(const char *filename, vector<vertex> &vertices,
                 vector<face> &faces) {
    // Ouverture du fichier
    ifstream file(filename);
    // Si le fichier n'a pas pu être ouvert quitter avec un message d'erreur
    if (!file) {
        cout << "Impossible d'ouvrir le fichier " << filename << endl;
        exit(1);
    }
    // Lecture du fichier ligne par ligne
    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        string word;
        iss >> word;
        // Si le premier mot est "v", ajout d'un nouveau sommet au tableau
        if (word == "v") {
            vertex vertex;
            iss >> vertex.x >> vertex.y >> vertex.z;
            vertices.push_back(vertex);
        }
        // Si le premier mot est "f", ajout d'une nouvelle face au tableau
        else if (word == "f") {
            face face;
            iss >> face.v1 >> face.v2 >> face.v3;
            faces.push_back(face);
        }
    }
    // On ferme le fichier
    file.close();
}

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

void printV(vector<vertex> &vertices) {
    // Pour chaque sommet du vecteur on affiche les coordonnées du sommet
    for (size_t i = 0; i < vertices.size(); i++) {
        cout << "v " << vertices[i].x << " " << vertices[i].y << " "
             << vertices[i].z << endl;
    }
}

void printF(vector<face> &faces) {
    // Pour chaque face du vecteur on affiche les indices des sommets de la face
    for (size_t i = 0; i < faces.size(); i++) {
        cout << "f " << faces[i].v1 << " " << faces[i].v2 << " " << faces[i].v3
             << endl;
    }
}