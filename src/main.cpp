

#include <cstdlib>
#include <iostream>
#include <vector>

#include "halfedge.hpp"
#include "obj.hpp"
#include "display.hpp"

int main(int argc, char **argv)
{ 

  vector<v> verticesIn;
  vector<f> facesIn;
  vector<vertex*> verticesOut;
  vector<face*> facesOut;
  vector<halfedge*> halfedgesOut;

  readObjFile("meshes/hexagone.obj", verticesIn, facesIn);

  printV(verticesIn);
  printF(facesIn);

  cout << "*************" << endl;

  buildHalfEdge(verticesIn,facesIn,verticesOut,facesOut,halfedgesOut);

  printVertices(verticesOut);
  cout << "*************" << endl;
  printFaces(facesOut);
  cout << "*************" << endl;
  printHalfedges(halfedgesOut);


  exit(EXIT_FAILURE);

  init(argc, argv);
}