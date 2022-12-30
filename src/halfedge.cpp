#include "halfedge.hpp"

void buildHalfEdge( vector<v> &verticesIn, vector<f> &facesIn,vector<vertex> &verticesOut, vector<face> &facesOut, vector<halfedge> &halfedgesOut){

    // ALGORITHME DE REMPLISSAGE DE LA STRUCTURE HALF-EDGE

    
    // Remplissage du tableau de sommets
    for (size_t i = 0; i < verticesIn.size(); i++){
        vertex v;
        v.id = i+1;
        v.x = verticesIn[i].x;
        v.y = verticesIn[i].y;
        v.z = verticesIn[i].z;
        verticesOut.push_back(v);
    }

    // Création d'un half edge par sommet du tableau de sommets
    for (size_t i = 0; i < verticesOut.size(); i++){
        halfedge h;
        h.id = i;
        h.origin = &verticesOut[i];
        h.next = NULL;
        h.prev = NULL;
        h.twin = NULL;
        h.incident_face = NULL;
        halfedgesOut.push_back(h);
    }
    


};

void printVertices(vector<vertex> &vertices){
    // Affichage des du sommet de la forme (id : x y z)
    for (vector<vertex>::iterator it = vertices.begin(); it != vertices.end(); ++it){
        cout << "V " << it->id << " : " << it->x << " " << it->y << " " << it->z << endl;
    }
}
void printFaces(vector<face> &faces){
    int i = 0;
    for (vector<face>::iterator it = faces.begin(); it != faces.end(); ++it){
        cout << "F " << i << " : " << it->half_edge << endl;
        i++;
    }
}
void printHalfedges(vector<halfedge> &halfedges){
    int i = 0;
    cout << "Halfedges : Origin Next Prev Twin Face" << endl;
    for (vector<halfedge>::iterator it = halfedges.begin(); it != halfedges.end(); ++it){
        cout << "H " << i << " : " << it->origin->id << " " << it->next << " " << it->prev << " " << it->twin << " " << it->incident_face << endl;
        i++;
    }
}