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
GLuint vbo_path = 0;
GLuint ibo_path = 0;
GLuint vao_path = 0;
GLuint IdProgram = 0;
GLuint IdProgram_path = 0;
GLuint VShader = 0;
GLuint FShader = 0;
char presse;
int anglex, angley, x, y, xold, yold;

// initialise un tableau de vertex qui représente un chemin de points
vector<vertex> path = {

    {0, 0, 0},
    {0.1, 0.3, 0.2},
    {0.2, -0.9, 0.1},
    {-0.3, -0.8, 0.5},
    {0.2, 0, 0},
};

SDL_Surface* screen;

void genererVBOVAO() {
    // Generate and bind the VAO for the mesh
    glGenVertexArrays(1, &vao);

    // Generate and bind the VBO for the mesh vertices
    glGenBuffers(1, &vbo);

    // Generate and bind the VAO for the lines
    glGenVertexArrays(1, &vao_path);

    // Generate and bind the VBO for the line vertices
    glGenBuffers(1, &vbo_path);
}

void remplissageVBOVAOmesh(const vector<vertex>& verticesIn, const vector<face>& facesIn) {
    // Génération du VAO
    glBindVertexArray(vao);

    // Génération du VBO
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, verticesIn.size() * sizeof(vertex), &verticesIn[0], GL_STATIC_DRAW);

    // Génération du IBO
    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, facesIn.size() * sizeof(face), &facesIn[0], GL_STATIC_DRAW);

    // On active l'attribut 0 (position)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), nullptr);
    glEnableVertexAttribArray(0);

    // On désactive le VAO
    glBindVertexArray(0);
}

void remplissageVBOVAOpath() {
    glBindVertexArray(vao_path);

    // Génération du VBO
    glBindBuffer(GL_ARRAY_BUFFER, vbo_path);
    glBufferData(GL_ARRAY_BUFFER, path.size() * sizeof(vertex), &path[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), nullptr);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
}

void prepareProgammeShader(void) {
    IdProgram = LoadShaders("shaders/shader_path.vert", "shaders/shader_path.frag", "shaders/shader_path.geom");
    IdProgram_path = LoadShaders("shaders/shader_path.vert", "shaders/shader_path.frag", "shaders/shader_path.geom");
}

void initMatrices(void) {
    GLfloat zoom = 2.0f;
    // TRANSFORMATIONS
    // Matrice de Projection : 45° Field of View, ratio 1, intervalle affichage : 0.1 unité <-> 100 unités
    Projection = glm::perspective(45.0f, (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);

    // Or, for an ortho camera :
    // Projection = glm::ortho(-10.0f,10.0f,-10.0f,10.0f,0.0f,100.0f); // In world coordinates

    // Camera matrix
    View = glm::lookAt(glm::vec3(5, 0, 0),  // Place de la Camera ( World Space)
                       glm::vec3(0, 0, 0),  // pointe a l'origine
                       glm::vec3(00, 1, 0)  // on regarde en haut
    );
    // Matrice de modelisarion : identité + transfos
    Model = glm::mat4(1.0f);
    Model = glm::translate(Model, glm::vec3(-.0f, -.0f, -.0f));
    Model = glm::scale(Model, glm::vec3(1.0f * zoom, 1.0f * zoom, 1.0f * zoom));
    // Our ModelViewProjection : multiplication des 3 matrices

    MVP = Projection * View * Model;
}

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
    initMatrices();
    genererVBOVAO();
    remplissageVBOVAOmesh(v, f);
    remplissageVBOVAOpath();

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

    glUseProgram(IdProgram_path);
    glBindVertexArray(vao_path);
    glLineWidth(5);

    GLuint MatriceID = glGetUniformLocation(IdProgram_path, "MVP");
    // ordre inverse pour multiplication matrices
    glUniformMatrix4fv(MatriceID, 1, GL_FALSE, &MVP[0][0]);

    glDrawArrays(GL_LINES, 0, path.size());

    glBindVertexArray(0);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glUseProgram(IdProgram);
    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, size_array, GL_UNSIGNED_INT, 0);
    MatriceID = glGetUniformLocation(IdProgram, "MVP");
    // ordre inverse pour multiplication matrices
    glUniformMatrix4fv(MatriceID, 1, GL_FALSE, &MVP[0][0]);
    glBindVertexArray(0);

    /*
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glUseProgram(IdProgram);
        glBindVertexArray(vao);

        glDrawElements(GL_TRIANGLES, size_array, GL_UNSIGNED_INT, 0);

        // Calcul du MVP
        GLuint MatriceID = glGetUniformLocation(IdProgram, "MVP");
        // ordre inverse pour multiplication matrices
        glUniformMatrix4fv(MatriceID, 1, GL_FALSE, &MVP[0][0]);

        glBindVertexArray(0); */
    SDL_GL_SwapBuffers();
}

void keyboard(SDL_Event event) {
    switch (event.key.keysym.sym) {
        // Appui sur echap -> Quitter
        case SDLK_ESCAPE:
            exit(0);
            break;
        // appui sur arrow left
        case SDLK_LEFT: {
            glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), (float)(1.f / 360.f) * 20, glm::vec3(0, 1, 0));
            MVP = MVP * rotation;
            break;
        }
        case SDLK_RIGHT: {
            glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), (float)(1.f / 360.f) * -20, glm::vec3(0, 1, 0));
            MVP = MVP * rotation;
            break;
        }
        case SDLK_UP: {
            glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), (float)(1.f / 360.f) * 20, glm::vec3(1, 0, 0));
            MVP = MVP * rotation;
            break;
        }
        case SDLK_DOWN: {
            glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), (float)(1.f / 360.f) * -20, glm::vec3(1, 0, 0));
            MVP = MVP * rotation;
            break;
        }

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
