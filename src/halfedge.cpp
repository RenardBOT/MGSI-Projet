#include "halfedge.hpp"

void buildHalfEdge(vector<vertex> &verticesIn, vector<face> &facesIn,
                   vector<he_vertex *> &verticesOut,
                   vector<he_face *> &facesOut,
                   vector<he_halfedge *> &halfedgesOut) {
    // ALGORITHME DE REMPLISSAGE DE LA STRUCTURE HALF-EDGE

    // Index de départ pour chaque tableau
    int idVertex = 1;  // Par convention, le premier sommet est le sommet 1
    int idFace = 0;
    int idHalfedge = 0;

    // Remplissage du tableau de sommets
    for (vertex &vertexIn : verticesIn) {
        he_vertex *v =
            new he_vertex{idVertex++, vertexIn.x, vertexIn.y, vertexIn.z};
        verticesOut.push_back(v);
    }

    // Remplissage du tableau de faces
    for (face faceIn : facesIn) {
        (void)faceIn;  // Pour éviter le warning "unused variable"
        he_face *f = new he_face{idFace++, nullptr};
        facesOut.push_back(f);
    }

    // Parcours des faces pour remplir le tableau de demi-arêtes (manque les
    // twins)
    for (size_t faceIndex = 0; faceIndex < facesIn.size(); faceIndex++) {
        he_halfedge *h0 = new he_halfedge;
        he_halfedge *h1 = new he_halfedge;
        he_halfedge *h2 = new he_halfedge;

        // Définition d'un id pour chaque demi-arête à des fins de débuggage
        h0->id = idHalfedge++;
        h1->id = idHalfedge++;
        h2->id = idHalfedge++;

        // L'origine de chaque demi-arête est son sommet d'origine.
        h0->origin =
            verticesOut[facesIn[faceIndex].v1 -
                        1];  // -1 car les indices des sommets commencent à 1
        h1->origin = verticesOut[facesIn[faceIndex].v2 - 1];
        h2->origin = verticesOut[facesIn[faceIndex].v3 - 1];

        // Définition des demi-arêtes suivantes et précédentes
        h0->next = h1;
        h1->next = h2;
        h2->next = h0;

        h0->prev = h2;
        h1->prev = h0;
        h2->prev = h1;

        // Définition des demi-arêtes opposées plus tard
        h0->twin = nullptr;
        h1->twin = nullptr;
        h2->twin = nullptr;

        h0->incident_face = facesOut[faceIndex];
        h1->incident_face = facesOut[faceIndex];
        h2->incident_face = facesOut[faceIndex];

        facesOut[faceIndex]->half_edge = h0;

        halfedgesOut.push_back(h0);
        halfedgesOut.push_back(h1);
        halfedgesOut.push_back(h2);
    }

    // Il reste à associer un twin à chaque demi-arête
    for (he_face *f : facesOut) {
        he_halfedge *h = f->half_edge;

        if (h->twin !=
            nullptr)  // Si elle a déjà un twin, pas besoin de le chercher
            continue;

        // Sinon on cherche un twin pour l'arête
        do {
            for (he_halfedge *other_h : halfedgesOut) {
                if (other_h->origin == h->next->origin &&
                    other_h->next->origin == h->origin) {
                    h->twin = other_h;
                    other_h->twin = h->twin;
                    break;
                }
            }
            h = h->next;
        } while (h != f->half_edge);
    }
}

void printVertices(vector<he_vertex *> &vertices) {
    // Affichage des du sommet de la forme (id : x y z)
    for (vector<he_vertex *>::iterator it = vertices.begin();
         it != vertices.end(); ++it) {
        cout << "V " << (*it)->id << " : " << (*it)->x << " " << (*it)->y << " "
             << (*it)->z << endl;
    }
}
void printFaces(vector<he_face *> &faces) {
    // Affichage des faces de la forme (id : h0 h1 h2)
    for (vector<he_face *>::iterator it = faces.begin(); it != faces.end();
         ++it) {
        cout << "F " << (*it)->id << " : " << (*it)->half_edge->id << endl;
    }
}
void printHalfedges(vector<he_halfedge *> &halfedges) {
    // Affichage des demi-arêtes de la forme (id : origin next prev twin
    // incident_face)
    cout << "Halfedge : origin next prev twin incident_face" << endl;

    int twinid;
    for (vector<he_halfedge *>::iterator it = halfedges.begin();
         it != halfedges.end(); ++it) {
        // On récupère l'id seulement s'il n'est pas nullptr, sinon il vaut -1
        // (arête sur le bord)
        if ((*it)->twin != nullptr)
            twinid = (*it)->twin->id;
        else
            twinid = -1;
        cout << "H " << (*it)->id << " : " << (*it)->origin->id << " "
             << (*it)->next->id << " " << (*it)->prev->id << " " << twinid
             << " " << (*it)->incident_face->id << endl;
    }
}

int getVertexId(he_vertex *v) { return v->id; }
int getFaceId(he_face *f) { return f->id; }
int getHalfedgeId(he_halfedge *h) { return h->id; }

void freeHalfEdge(vector<he_vertex *> &vertices, vector<he_face *> &faces, vector<he_halfedge *> &halfedges) {
    for (he_vertex *v : vertices) {
        delete v;
    }
    for (he_face *f : faces) {
        delete f;
    }
    for (he_halfedge *h : halfedges) {
        delete h;
    }
}