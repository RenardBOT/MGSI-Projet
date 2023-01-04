#ifndef DISPLAY_HPP
#define DISPLAY_HPP

#include <GL/glew.h>
#include <SDL/SDL.h>

#include <cstdlib>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <vector>

#include "gl_structs.hpp"
#include "halfedge.hpp"
#include "obj.hpp"
#include "shader.hpp"

// Quelques définitions de couleurs
#define ROUGE 1.0f, 0.0f, 0.0f
#define BLEU 0.0f, 0.0f, 1.0f
#define VERT 0.0f, 1.0f, 0.0f
#define JAUNE 1.0f, 1.0f, 0.0f
#define MAGENTA 1.0f, 0.0f, 1.0f
#define CYAN 0.0f, 1.0f, 1.0f
#define ORANGE 1.0f, 0.5f, 0.2f
#define LIME 0.75f, 1.0f, 0.75f
#define CUSTOM inputR, inputG, inputB

// Taille de la fenêtre
#define HEIGHT 900
#define WIDTH 1200

int initDisplay(int argc, char **argv, const vector<vertex> &, const vector<face> &);
void fillBuffers(std::vector<vertex> *sommetsIn, std::vector<face> *facesOut);
void genererVBOVAO();
void remplissageVBOVAOmesh(const vector<vertex> &verticesIn, const vector<face> &facesIn);
void remplissageVBOVAOpath();
void prepareProgammeShader(void);
void affichage(GLuint size_array);
void keyboard(SDL_Event event);
void reshape(int x, int y);
void mouse(int bouton, int etat, int x, int y);
void mousemotion(int x, int y);
void rotate(int x, int y);
//********************************************

#endif /* DISPLAY_HPP */
