#ifndef DISPLAY_HPP
#define DISPLAY_HPP

#include <GL/glew.h>
#include <SDL/SDL.h>

#include <cstdlib>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <vector>

#include "halfedge.hpp"
#include "obj.hpp"
#include "shader.hpp"

#define ROUGE 1.0f, 0.0f, 0.0f
#define BLEU 0.0f, 0.0f, 1.0f
#define VERT 0.0f, 1.0f, 0.0f
#define JAUNE 1.0f, 1.0f, 0.0f
#define MAGENTA 1.0f, 0.0f, 1.0f
#define CYAN 0.0f, 1.0f, 1.0f
#define ORANGE 1.0f, 0.5f, 0.2f
#define LIME 0.75f, 1.0f, 0.75f
#define CUSTOM inputR, inputG, inputB

struct shader_vertex {
    // coordonnées x, y et z du sommet, et r g b de ses couleurs
    GLfloat x;
    GLfloat y;
    GLfloat z;
    GLfloat r;
    GLfloat g;
    GLfloat b;
};

// Taille de la fenêtre
#define HEIGHT 1200
#define WIDTH 1200

// Matrices GLM
extern glm::mat4 Projection;
extern glm::mat4 View;
extern glm::mat4 Model;
extern glm::mat4 MVP;

extern std::vector<shader_vertex> sommets;
extern std::vector<GLuint> faces;

extern GLuint vbo;
extern GLuint ibo;
extern GLuint vao;
extern GLuint IdProgram;
extern GLuint VShader;
extern GLuint FShader;
extern char presse;
extern int anglex, angley, x, y, xold, yold;

extern SDL_Surface *screen;

int initDisplay(int argc, char **argv);
void fillBuffers(std::vector<v> *sommetsIn, std::vector<f> *facesOut);
void genererVBOVAO(void);
void prepareProgammeShader(void);
void affichage();
void keyboard(SDL_Event event);
void reshape(int x, int y);
void mouse(int bouton, int etat, int x, int y);
void mousemotion(int x, int y);
void rotate(int x, int y);
//********************************************

#endif /* DISPLAY_HPP */
