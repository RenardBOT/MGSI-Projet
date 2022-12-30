#include <GL/glew.h>

#ifdef __cplusplus
#include <cstdlib>
#else
#include <stdlib.h>
#endif
#include <iostream>
#include <SDL/SDL.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>
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

//************************************************

GLfloat inputR = 1.0f;
GLfloat inputG = 1.0f;
GLfloat inputB = 1.0f;
// bool flipInputCol = false;

GLint height = 1200;
GLint width = 1200;

glm::mat4 Projection;
glm::mat4 View;
glm::mat4 Model;
glm::mat4 MVP;

typedef struct
{
  // coordonnées x, y et z du sommet
  GLfloat x;
  GLfloat y;
  GLfloat z;
  GLfloat r;
  GLfloat g;
  GLfloat b;
} Sommet;

// vector pour stocker les sommets du cube et leur couleur
std::vector<Sommet> Cube = {
    // AFAIRE 2 définir un cube entre (-.5,-.5,-.5) et (.5, .5 ,.5)
    // COORDONNEES        COULEURS RGB
    {-.5f, -.5f, -.5f,    ORANGE  }, //0
    {-.5f, .5f, -.5f,     BLEU    }, //1
    {.5f, .5f, -.5f,      MAGENTA }, //2
    {.5f, -.5f, -.5f,     CYAN    }, //3
    {-.5f, -.5f, .5f,     JAUNE   }, //4
    {-.5f, .5f, .5f,      VERT    }, //5 
    {.5f, .5f, .5f,       ROUGE   }, //6
    {.5f, -.5f, .5f,       LIME    }  //7
};

// Tableau pour stocker les indices des sommets par face pour le cube
std::vector<GLuint> indexFaceCube = {
    // AFAIRE 3 définir les faces triangulaires
    0, 1, 2,
    0, 2, 3,
    3, 6, 7,
    3, 2, 6,
    4, 7, 5,
    7, 6, 5,
    4, 5, 1,
    4, 1, 0,
    5, 6, 1,
    6, 2, 1,
    4, 0, 3,
    4, 3, 7 };

// initialise à 0 = pas d’indice
GLuint vbo = 0;
GLuint ibo = 0;
GLuint vao = 0;
GLuint IdProgram = 0;
GLuint VShader = 0;
GLuint FShader = 0;

void genererVBOVAO(void)
{
  // AFAIRE 4
  //  VBO
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(GLfloat) * Cube.size(), &Cube[0], GL_STATIC_DRAW);

  // IBO
  glGenBuffers(1, &ibo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * indexFaceCube.size(), &indexFaceCube[0], GL_STATIC_DRAW);

  // VAO
  // Créer un nouveau VAO, annoncer que l'on travaille dessus
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao); 

  // Layers 0 et 1 activés
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);

  // Travailler avec le VBO et attacher le IBO
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo); // 1 seul par VAO

  // Association des positions au layer 0
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, 6 * sizeof(GLfloat), 0);

  // Association des couleurs au layer 1
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, 6 * sizeof(GLfloat), (void *)(0 + 3 * sizeof(GLfloat)));

  // Desactivation des Arraybuffer
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}

void prepareProgammeShader(void)
{
  // vous avez de la chance ce n'est pas AF AIRE 6
  IdProgram = LoadShaders("shaders/shader.vert", "shaders/shader.frag");
}
void initMatrices(void)
{
  GLfloat zoom = 2.0f;
  // TRANSFORMATIONS
  // Matrice de Projection : 45° Field of View, ratio 1, intervalle affichage : 0.1 unité <-> 100 unités
   Projection = glm::perspective(45.0f, (float) width / (float)height, 0.1f, 100.0f);

  // Or, for an ortho camera :
  //Projection = glm::ortho(-10.0f,10.0f,-10.0f,10.0f,0.0f,100.0f); // In world coordinates

  // Camera matrix
  View = glm::lookAt(glm::vec3(5, 0, 0), // Place de la Camera ( World Space)
                     glm::vec3(0, 0, 0), // pointe a l'origine
                     glm::vec3(00, 1, 0)  // on regarde en haut
  );
  // Matrice de modelisarion : identité + transfos
  Model = glm::mat4(1.0f);
  Model = glm::translate(Model, glm::vec3(-.0f, -.0f, -.0f));
  Model = glm::scale(Model, glm::vec3(1.0f*zoom, 1.0f*zoom, 1.0f*zoom));
  // Our ModelViewProjection : multiplication des 3 matrices
}

void dessinerCube(void)
{

  // AFAIRE 5
  // on spécifie avec quel shader on veut afficher
  glUseProgram(IdProgram);
  // on active le VAO
  glBindVertexArray(vao);
  // on appelle la fonction dessin
  glDrawElements(GL_TRIANGLES, indexFaceCube.size(), GL_UNSIGNED_INT, 0);
  // on désactive le VAO
  glBindVertexArray(0);

  //Calcul du MVP
  GLuint MatriceID = glGetUniformLocation(IdProgram, "MVP");
  MVP = Projection * View * Model; // ordre inverse pour multiplication matrices
  glUniformMatrix4fv(MatriceID, 1, GL_FALSE, &MVP[0][0]);

  // Envoi des couleurs
  GLuint inputColor = glGetUniformLocation(IdProgram, "inputColor") ;
  glUniform3f(inputColor,inputG,inputR,inputB);
  glUseProgram(0);
}



char presse;
int anglex, angley, x, y, xold, yold;

/* Prototype des fonctions */
void affichage();
void clavier(unsigned char touche, int x, int y);
void keyboard(SDL_Event event);
void reshape(int x, int y);
void idle();
void mouse(int bouton, int etat, int x, int y);
void mousemotion(int x, int y);
void rotate(int x, int y);
void changeInputColor(GLfloat * col, GLfloat pas);
//********************************************

SDL_Surface *screen;
//********************************************
int main(int argc, char **argv)
{
  // initialize SDL video
  if (SDL_Init(SDL_INIT_VIDEO) < 0)
  {
    printf("Unable to init SDL: %s\n", SDL_GetError());
    return 1;
  }

  // make sure SDL cleans up before exit
  atexit(SDL_Quit);

  // create a new window
  screen = SDL_SetVideoMode(width, height, 16, SDL_OPENGL | SDL_DOUBLEBUF);
  if (!screen)
  {
    printf("Unable to set 640x480 video: %s\n", SDL_GetError());
    return 1;
  }

  glEnable(GL_DEPTH_TEST);

  // ATTENTION ne pas oublier l'initialisation de GLEW
  GLenum err = glewInit();

  // info version oenGL / GLSL :
  //  AFAIRE 1 : récupérer les infos sur la cater version d'openGL/GLSL
  std::cout << std::endl
            << "***** Info GPU *****" << std::endl;
  std::cout << "Fabricant : " << glGetString(GL_VENDOR) << std::endl;
  std::cout << "Carte graphique: " << glGetString(GL_RENDERER) << std::endl;
  std::cout << "Version : " << glGetString(GL_VERSION) << std::endl;
  std::cout << "Version GLSL : " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl
            << std::endl;

  prepareProgammeShader();
  initMatrices();
  genererVBOVAO();


  // program main loop
  bool done = false;
  while (!done)
  {
    // message processing loop
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
      // check for messages
      switch (event.type)
      {
        // exit if the window is closed
      case SDL_QUIT:
        done = true;
        break;

        // check for keypresses
      case SDL_KEYDOWN:
        if (event.key.keysym.sym == SDLK_ESCAPE)
          done = true;
        else
          keyboard(event);
        
        break;
        // check for keypresses
      case SDL_MOUSEBUTTONDOWN:
        mouse(event.button.button, SDL_MOUSEBUTTONDOWN, event.button.x, event.button.y);
        break;
      case SDL_MOUSEBUTTONUP:
        mouse(event.button.button, SDL_MOUSEBUTTONUP, event.button.x, event.button.y);
        break;
      case SDL_MOUSEMOTION:
        mousemotion(event.button.x, event.button.y);
        break;

      } // end switch
    }   // end of message processing

    // DRAWING STARTS HERE
    affichage();
  } // end main loop

  // all is well ;)
  printf("Exited cleanly\n");
  return 0;
}

void affichage()
{
  int i, j;
  /* effacement de l'image avec la couleur de fond */
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Dessin du cube
  dessinerCube();
/* 
  // Repère (fait à l'ancienne
  // axe x en rouge
  glBegin(GL_LINES);
  glColor3f(1.0, 0.0, 0.0);
  glVertex3f(0, 0, 0.0);
  glVertex3f(1, 0, 0.0);
  glEnd();
  // axe des y en vert
  glBegin(GL_LINES);
  glColor3f(0.0, 1.0, 0.0);
  glVertex3f(0, 0, 0.0);
  glVertex3f(0, 1, 0.0);
  glEnd();
  // axe des z en bleu
  glBegin(GL_LINES);
  glColor3f(0.0, 0.0, 1.0);
  glVertex3f(0, 0, 0.0);
  glVertex3f(0, 0, 1.0);
  glEnd(); */

  // On echange les buffers
  SDL_GL_SwapBuffers();
}

void keyboard(SDL_Event event)
{
  switch (event.key.keysym.sym){

/*     case SDLK_KP0:
    flipInputCol = !flipInputCol;
    if(flipInputCol)
      std::cout << "Custom colors ON" << std::endl;
    else
      std::cout << "Custom colors OFF" << std::endl;
    break; */

    case SDLK_KP4:
      changeInputColor(&inputR, 0.1f);
      std::cout << "Red : " << inputR << std::endl;
      break;
    case SDLK_KP1:
      changeInputColor(&inputR, -0.1f);
      std::cout << "Red : " << inputR << std::endl;
      break;

    case SDLK_KP5:
      changeInputColor(&inputG, 0.1f);
      std::cout << "Green : " << inputG << std::endl;
      break;
    case SDLK_KP2:
      changeInputColor(&inputG, -0.1f);
      std::cout << "Green : " << inputG << std::endl;
      break;

    case SDLK_KP6:
      changeInputColor(&inputB, 0.1f);
      std::cout << "Blue : " << inputB << std::endl;
      break;
    case SDLK_KP3:
      changeInputColor(&inputB, -0.1f);
      std::cout << "Blue : " << inputB << std::endl;
      break;

    case 'd':
      glDisable(GL_DEPTH_TEST);
      break;

    default:
      std::cout << "ok" << std::endl;
  }
}

void reshape(int x, int y)
{
  std::cout << "Reshape";
  if (x < y)
    glViewport(0, (y - x) / 2, x, x);
  else
    glViewport((x - y) / 2, 0, y, y);
}

void mouse(int button, int state, int x, int y)
{

  /* si on appuie sur le bouton gauche */
  if (button == SDL_BUTTON_LEFT && state == SDL_MOUSEBUTTONDOWN)
  {
    presse = 1; /* le booleen presse passe a 1 (vrai) */
    xold = x;   /* on sauvegarde la position de la souris */
    yold = y;
    std::cout << "Clic :\tX = " << xold << "\t||\tY = " << yold << std::endl;
    
  }
  /* si on relache le bouton gauche */
  if (button == SDL_BUTTON_LEFT && state == SDL_MOUSEBUTTONUP)
  {
    presse = 0; /* le booleen presse passe a 0 (faux) */
  }
}

void mousemotion(int x, int y)
{
  if (presse) /* si le bouton gauche est presse */
  {
    /* on modifie les angles de rotation de l'objet
       en fonction de la position actuelle de la souris et de la derniere
       position sauvegardee */
    rotate(x-xold,y-yold);
    std::cout << "delta X" << x-xold << " || delta Y " << y-yold << std::endl;

    // glutPostRedisplay(); /* on demande un rafraichissement de l'affichage */
  }
  

  xold = x; /* sauvegarde des valeurs courante de le position de la souris */
  yold = y;
}

void rotate(int x, int y){
  View = glm::rotate(View, (float)x*0.006f, glm::vec3(0.0f, 1.0f, 0.0f));
  View = glm::rotate(View, (float)y*0.006f, glm::vec3(0.0f, 0.0f, 1.0f));
  dessinerCube();
}

void changeInputColor(GLfloat * col, GLfloat pas){
  *col += pas;
  if(*col<0)
    *col = 0;
  if(*col >1)
    *col = 1;
  
  
}
