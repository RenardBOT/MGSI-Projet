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

SDL_Surface* screen;

void genererVBOVAO(const vector<vertex>& verticesIn, const vector<face>& facesIn) {
    // On attribue aux vao, vbo et ibo un identifiant
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &vao);
    glGenBuffers(1, &ibo);

    // On lie et on indique avec quels buffers on va travailler
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

    // On envoie les données des sommets et des indices de faces au GPU
    glBufferData(GL_ARRAY_BUFFER, verticesIn.size() * sizeof(vertex), &verticesIn[0], GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, facesIn.size() * sizeof(face), &facesIn[0], GL_STATIC_DRAW);

    // On indique au GPU comment lire le tableau verticesIn
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), nullptr);

    // Puis une fois que l'on n'utilise plus les VBO, VAO et IBO, on les désactive
    // glBindVertexArray(0);
    // glBindBuffer(GL_ARRAY_BUFFER, 0);
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void prepareProgammeShader(void) {
    IdProgram = LoadShaders("shaders/shader.vert", "shaders/shader.frag");
}

/* Prototype des fonctions */

//********************************************
int initDisplay(int argc, char** argv, const vector<vertex>& v, const vector<face>& f) {
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
    std::cout << std::endl
              << "***** Info GPU *****" << std::endl;
    std::cout << "Fabricant : " << glGetString(GL_VENDOR) << std::endl;
    std::cout << "Carte graphique: " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "Version : " << glGetString(GL_VERSION) << std::endl;
    std::cout << "Version GLSL : " << glGetString(GL_SHADING_LANGUAGE_VERSION)
              << std::endl
              << std::endl;

    prepareProgammeShader();
    genererVBOVAO(v, f);

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
        affichage(f.size() * sizeof(face));
    }  // end main loop

    // all is well ;)
    printf("Exited cleanly\n");
    return 0;
}

void affichage(GLuint size_array) {
    /* effacement de l'image avec la couleur de fond */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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

    // A FAIRE 2 : dessiner le maillage
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    // on spécifie avec quel shader on veut afficher
    glUseProgram(IdProgram);
    // on active le VAO
    glBindVertexArray(vao);
    // on appelle la fonction dessin
    glDrawElements(GL_TRIANGLES, size_array, GL_UNSIGNED_INT, 0);
    // on désactive le VAO
    glBindVertexArray(0);

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

void fillBuffers(std::vector<vertex>* sommets, std::vector<face>* faces) {
    // remplir le tableau de shader_vertex avec les sommets, et rgb valant 1,1,1
}
