#include <cstdlib>
#include <iostream>
#include <vector>

#include "display.hpp"
#include "dijkstra.hpp"
#include "halfedge.hpp"
#include "obj.hpp"

// include get

int main(int argc, char **argv) {
    // ARGUMENTS : Parsing des arguments
    int a = -1, b = -1, d = -1;
    float z = 1.0;
    std::string filename = "ours";
    std::string pathname = "./meshes/";

    for (int i = 1; i < argc; ++i) {
        if (strcmp(argv[i], "-a") == 0) {
            a = atoi(argv[++i]);
        } else if (strcmp(argv[i], "-b") == 0) {
            b = atoi(argv[++i]);
        } else if (strcmp(argv[i], "-d") == 0) {
            d = atoi(argv[++i]);
        } else if (strcmp(argv[i], "-p") == 0) {
            filename = argv[++i];
        } else if (strcmp(argv[i], "-z") == 0) {
            z = atof(argv[++i]);
        }
    }

    // ARGUMENTS -a -b -d -p : Si soit a, soit b, soit d, soit p n'ont pas été spécifiés, on quitte le programme
    if (a == -1 || b == -1 || d == -1) {
        cout << "Arguments nécéssaires: " << argv[0] << " -a <a> -b <b> -d <d> -p <obj>" << endl;
        // On dit que a est pour le sommet de départ, b pour le sommet d'arrivée et c pour l'algo (0 pour Dijkstra, 1 pour Dijkstra non pondéré)
        cout << "a: sommet de départ" << endl
             << "b: sommet d'arrivée" << endl
             << "d: algo (0 pour Dijkstra, 1 pour Dijkstra non pondéré)" << endl
             << "p: nom du obj dans ./meshes (par exemple ours)" << endl
             << "z: zoom (par défaut 1)" << endl;

        exit(1);
    }

    // ARGUMENT -p : Verification de l'existence du fichier
    pathname = pathname + filename + ".obj";
    std::ifstream file(pathname);
    if (file.is_open()) {
        std::cout << "Le fichier suivant a été correctement ouvert ./meshes/" << filename << ".obj !" << std::endl;
    } else {
        std::cout << "Le fichier suivant n'a pas été trouvé/pu être ouvert ./meshes/" << filename << ".obj" << std::endl;
    }

    // VerticesIn et facesIn sont des vecteurs de structures vertex et fface définies
    // dans gl_structs. Ils contiendront les sommets et faces comme lues dans le fichier obj.
    vector<vertex> verticesIn;
    vector<face> facesIn;

    // initialise un tableau de vertex qui représente un chemin de points. La trajectoire à afficher sur le maillage.
    vector<vertex> path;
    // verticesOut, facesOut et halfedgesOut sont des vecteurs de pointeurs vers
    // les structures vertex, face et halfedge définies dans halfedge.hpp. Ils
    // contiendront les sommets, faces et demi-arêtes du maillage half-edge.
    vector<he_vertex *> verticesOut;
    vector<he_face *> facesOut;
    vector<he_halfedge *> halfedgesOut;

    // ARGUMENT -z : Le zoom vaut entre 0.1 et 100
    if (z < 0.1 || z > 100) {
        cout << "Le zoom doit être compris entre 0.1 et 100" << endl;
        exit(1);
    }

    // On lit le fichier .obj et on remplit les vecteurs verticesIn et facesIn
    readObjFile(pathname.c_str(), verticesIn, facesIn, z);

    // On fait de même pour la sphère
    vector<vertex> verticesSphereIn;
    vector<face> facesSphereIn;
    /* vector<he_vertex *> verticesSphereOut;
    vector<he_face *> facesSphereOut;
    vector<he_halfedge *> halfedgesSphereOut; */

    // On remplit les 3 vecteurs du maillage half-edge à partir des vecteurs
    // verticesIn et facesIn
    buildHalfEdge(verticesIn, facesIn, verticesOut, facesOut, halfedgesOut);

    // ARGUMENT : Si a et b sont plus petit que 0 ou plus grand que le nombre de sommets, on quitte le programme
    if (a < 0 || (size_t)a > verticesIn.size() || b < 0 || (size_t)b > verticesIn.size()) {
        cout << "Les sommets de départ et d'arrivée doivent être compris entre 0 et " << verticesIn.size() << endl;
        exit(1);
    }

    // ARGUMENT : Si d ne vaut pas 0 ou 1, on quitte le programme
    if (d != 0 && d != 1) {
        cout << "d doit valoir 0 ou 1" << endl;
        exit(1);
    }

    vector<int> sommets_path = buildDijkstra(halfedgesOut, verticesOut, a, b, d);

    // Remplissage du vecteur path avec les sommets du chemin
    for (size_t i = 0; i < sommets_path.size(); i++) {
        path.push_back(verticesIn[sommets_path[i] - 1]);
    }

    bindExternalArrays(verticesIn, facesIn, path, verticesSphereIn, facesSphereIn);
    initDisplay();

    // Libération de la mémoire
    freeHalfEdge(verticesOut, facesOut, halfedgesOut);

    // Sortie du programme
    return 0;
}