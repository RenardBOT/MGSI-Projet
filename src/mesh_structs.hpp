#ifndef MESH_STRUCTS_HPP
#define MESH_STRUCTS_HPP

#endif /* MESH_STRUCTS_HPP */

// Coordonnées d'un sommet
struct vertex {
    float x;  // Coordonnée x
    float y;  // Coordonnée y
    float z;  // Coordonnée z
};

// Face du modèle half-edge
struct face {
    int half_edge;  // Demi-arrête de la face
};

// Arrête du modèle half-edge
struct halfedge {
    int start;  // Sommet de départ
    int end;    // Sommet d'arrivée
    int twin;   // Demi-arrête opposée
    int face;   // Face dont la demi-arête fait partie
};