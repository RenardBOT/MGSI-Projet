#ifndef GL_STRUCTS_HPP
#define GL_STRUCTS_HPP

#include <GL/gl.h>

// === Structures ===

/**
 * @brief Une structure représentant les coordonnées d'un point du format obj
 */
struct v {
    // La coordonnée en x du point
    GLfloat x;
    // La coordonnée en y du point
    GLfloat y;
    // La coordonnée en z du point
    GLfloat z;
};

/**
 * @brief Une structure représentant une face du format obj
 */
struct f {
    // L'indice du premier sommet de la face
    GLint v1;
    // L'indice du deuxième sommet de la face
    GLint v2;
    // L'indice du troisième sommet de la face
    GLint v3;
};

#endif /* GL_STRUCTS_HPP */