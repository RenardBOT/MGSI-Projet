#include "display.hpp"

// Matrices GLM
glm::mat4 Projection;
glm::mat4 View;
glm::mat4 Model;
glm::mat4 MVP;

// initialise à 0 = pas d’indice
GLuint vbo = 0;
GLuint ibo = 0;
GLuint vao = 0;
GLuint IdProgram = 0;
GLuint VShader = 0;
GLuint FShader = 0;
char presse;
int anglex, angley, x, y, xold, yold;

SDL_Surface *screen;

void genererVBOVAO(void) {
    // A ecrire
}

void prepareProgammeShader(void) {
    IdProgram = LoadShaders("shaders/shader.vert", "shaders/shader.frag");
}

/* Prototype des fonctions */

//********************************************
int initDisplay(int argc, char **argv) {
    // initialize SDL video
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Unable to init SDL: %s\n", SDL_GetError());
        return 1;
    }

    // make sure SDL cleans up before exit
    atexit(SDL_Quit);

    // create a new window
    screen = SDL_SetVideoMode(WIDTH, HEIGHT, 16, SDL_OPENGL | SDL_DOUBLEBUF);
    if (!screen) {
        printf("Unable to set screen  : %s\n", SDL_GetError());
        return 1;
    }

    glEnable(GL_DEPTH_TEST);

    // ATTENTION ne pas oublier l'initialisation de GLEW
    GLenum err = glewInit();
    if (GLEW_OK != err) {
        // ERREUR : initialisation de GLEW a échoué
        std::cerr << "Error: " << glewGetErrorString(err) << std::endl;
    }

    // info version oenGL / GLSL :
    //  AFAIRE 1 : récupérer les infos sur la cater version d'openGL/GLSL
    std::cout << std::endl << "***** Info GPU *****" << std::endl;
    std::cout << "Fabricant : " << glGetString(GL_VENDOR) << std::endl;
    std::cout << "Carte graphique: " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "Version : " << glGetString(GL_VERSION) << std::endl;
    std::cout << "Version GLSL : " << glGetString(GL_SHADING_LANGUAGE_VERSION)
              << std::endl
              << std::endl;

    prepareProgammeShader();
    // genererVBOVAO();

    // program main loop
    bool done = false;
    while (!done) {
        // message processing loop
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            // check for messages
            switch (event.type) {
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
                    mouse(event.button.button, SDL_MOUSEBUTTONDOWN,
                          event.button.x, event.button.y);
                    break;
                case SDL_MOUSEBUTTONUP:
                    mouse(event.button.button, SDL_MOUSEBUTTONUP,
                          event.button.x, event.button.y);
                    break;
                case SDL_MOUSEMOTION:
                    mousemotion(event.button.x, event.button.y);
                    break;

            }  // end switch
        }      // end of message processing

        // DRAWING STARTS HERE
        affichage();
    }  // end main loop

    // all is well ;)
    printf("Exited cleanly\n");
    return 0;
}

void affichage() {
    /* effacement de l'image avec la couleur de fond */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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
    glEnd();

    // On echange les buffers
    SDL_GL_SwapBuffers();
}

void keyboard(SDL_Event event) {
    switch (event.key.keysym.sym) {
        // Appui sur echap -> Quitter
        case SDLK_ESCAPE:
            exit(0);
            break;

        default:
            std::cout << "Touche non reconnue" << std::endl;
    }
}

void reshape(int x, int y) {
    std::cout << "Reshape";
    if (x < y)
        glViewport(0, (y - x) / 2, x, x);
    else
        glViewport((x - y) / 2, 0, y, y);
}

void mouse(int button, int state, int x, int y) {
    /* si on appuie sur le bouton gauche */
    if (button == SDL_BUTTON_LEFT && state == SDL_MOUSEBUTTONDOWN) {
        presse = 1; /* le booleen presse passe a 1 (vrai) */
        xold = x;   /* on sauvegarde la position de la souris */
        yold = y;
        std::cout << "Clic :\tX = " << xold << "\t||\tY = " << yold
                  << std::endl;
    }
    /* si on relache le bouton gauche */
    if (button == SDL_BUTTON_LEFT && state == SDL_MOUSEBUTTONUP) {
        presse = 0; /* le booleen presse passe a 0 (faux) */
    }
}

void mousemotion(int x, int y) {
    if (presse) { /* si le bouton gauche est presse */
    }
}

void rotate(int x, int y) {
    View = glm::rotate(View, (float)x * 0.006f, glm::vec3(0.0f, 1.0f, 0.0f));
    View = glm::rotate(View, (float)y * 0.006f, glm::vec3(0.0f, 0.0f, 1.0f));
    // dessinerCube();
}

void fillBuffers(std::vector<v> *sommets, std::vector<f> *faces) {
    // remplir le tableau de shader_vertex avec les sommets, et rgb valant 1,1,1
}
