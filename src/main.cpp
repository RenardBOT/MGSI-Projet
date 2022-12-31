#include <cstdlib>
#include <iostream>
#include <vector>

#include "halfedge.hpp"
#include "obj.hpp"
#include "display.hpp"

int main(int argc, char **argv)
{ 
  // VerticesIn et facesIn sont des vecteurs de structures v et f définies dans obj.hpp
  // Ils contiendront les sommets et faces du fichier .obj
  vector<v> verticesIn;
  vector<f> facesIn;

  // verticesOut, facesOut et halfedgesOut sont des vecteurs de pointeurs vers les 
  // structures vertex, face et halfedge définies dans halfedge.hpp.
  // Ils contiendront les sommets, faces et demi-arêtes du maillage half-edge. 
  vector<vertex*> verticesOut;
  vector<face*> facesOut;
  vector<halfedge*> halfedgesOut;

  // On lit le fichier .obj et on remplit les vecteurs verticesIn et facesIn
  readObjFile("meshes/hexagone.obj", verticesIn, facesIn);

  // On remplit les 3 vecteurs du maillage half-edge à partir des vecteurs verticesIn et facesIn
  buildHalfEdge(verticesIn,facesIn,verticesOut,facesOut,halfedgesOut);

  // On affiche pour débug
  printVertices(verticesOut);
  cout << "*************" << endl;
  printFaces(facesOut);
  cout << "*************" << endl;
  printHalfedges(halfedgesOut);

  exit(EXIT_SUCCESS);

  init(argc, argv);
}