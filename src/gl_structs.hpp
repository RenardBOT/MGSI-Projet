#ifndef GL_STRUCTS_HPP
#define GL_STRUCTS_HPP

#include <GL/gl.h>

// === Structures ===

/**
 * @brief Une structure un sommet par ses trois coordonnées
 */
struct vertex {
    // La coordonnée en x du point
    GLfloat x;
    // La coordonnée en y du point
    GLfloat y;
    // La coordonnée en z du point
    GLfloat z;
};

/**
 * @brief Une structure représentant une face par trois indices de sommets
 */
struct face {
    // L'indice du premier sommet de la face
    GLint v1;
    // L'indice du deuxième sommet de la face
    GLint v2;
    // L'indice du troisième sommet de la face
    GLint v3;
};

#endif /* GL_STRUCTS_HPP */