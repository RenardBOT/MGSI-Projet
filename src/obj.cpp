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
            vertex.x = 0.1f * vertex.x;
            vertex.y = 0.1f * vertex.y;
            vertex.z = 0.1f * vertex.z;
            vertices.push_back(vertex);
        }
        // Si le premier mot est "f", ajout d'une nouvelle face au tableau
        else if (word == "f") {
            face face;
            iss >> face.v1 >> face.v2 >> face.v3;
            face.v1--;
            face.v2--;
            face.v3--;
            faces.push_back(face);
        }
    }
    // On ferme le fichier
    file.close();
}
