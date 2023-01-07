#include "display.hpp"

/* -------------------------------------------------------------------------- */
/*                             Variables globales                             */
/* -------------------------------------------------------------------------- */

/* ----------------------- Matrices de transformation ----------------------- */

glm::mat4 Projection;  // Matrice de projection
glm::mat4 View;        // Matrice de vue
glm::mat4 Model;       // Matrice de modèle
glm::mat4 MVP;         // Matrice MVP qui est le produit des 3 matrices précédentes
GLuint MVPid;          // Id de la variable uniforme MVP dans le shader

/* ---------------- Données du maillage et de la trajectoire ---------------- */

std::vector<vertex> mesh_vertices;    // Liste des sommets du maillage
std::vector<face> mesh_faces;         // Liste des indices des sommets des faces triangulaire du maillage
std::vector<vertex> sphere_vertices;  // Liste des sommets du maillage de la sphère
std::vector<face> sphere_faces;       // Liste des indices des sommets des faces triangulaire du maillage de la sphère
std::vector<vertex> path_vertices;    // Liste des points de la trajectoire

/* --------------------------------- Shaders -------------------------------- */

GLuint mesh_shader = 0;  // Shader pour le maillage
GLuint path_shader = 0;  // Shader pour la trajectoire
GLuint sphere_shader = 0;
GLuint mesh_vao = 0;  // VAO pour le maillage
GLuint path_vao = 0;  // VAO pour la trajectoire
GLuint sphere_vao = 0;
GLuint mesh_vbo = 0;  // VBO pour le maillage
GLuint path_vbo = 0;  // VBO pour la trajectoire
GLuint sphere_vbo = 0;
GLuint mesh_ibo = 0;  // IBO pour le maillage
GLuint sphere_ibo = 0;

/* --------------------------- Affichage à l'écran -------------------------- */

char presse;                           // Touche enfoncée
int anglex, angley, x, y, xold, yold;  // Variables pour la rotation de la scène
SDL_Surface* screen;                   // Surface pour l'affichage

/* -------------------------------------------------------------------------- */
/*                                  Méthodes                                  */
/* -------------------------------------------------------------------------- */

/* ------------- Initialisation des shaders, buffers et matrices ------------ */

void genShaders(void) {
    mesh_shader = LoadShaders("shaders/shader.vert", "shaders/shader.frag", nullptr);
    path_shader = LoadShaders("shaders/shader.vert", "shaders/shader.frag", nullptr);
    sphere_shader = LoadShaders("shaders/shader.vert", "shaders/shader.frag", nullptr);
}

void genMatrices(void) {
    GLfloat zoom = 0.1f;
    // TRANSFORMATIONS
    // Matrice de Projection : 45° Field of View, ratio 1, intervalle affichage : 0.1 unité <-> 100 unités
    Projection = glm::perspective(45.0f, (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);

    // Matrice de vue (camera)
    View = glm::lookAt(glm::vec3(0, 0, 5),  // Place de la Camera ( World Space)
                       glm::vec3(0, 0, 0),  // pointe a l'origine
                       glm::vec3(00, 1, 0)  // on regarde en haut
    );
    // Matrice de modelisation : identité + transfos
    Model = glm::mat4(1.0f);
    Model = glm::translate(Model, glm::vec3(-.0f, -.0f, -.0f));
    Model = glm::scale(Model, glm::vec3(1.0f * zoom, 1.0f * zoom, 1.0f * zoom));

    // MVP est donc le produit des 3 matrices (l'ordre est important dans une multiplication de matrices!)
    MVP = Projection * View * Model;
}

void genBuffers(void) {
    // Génération VAO, VBO et IBO pour le maillage
    glGenVertexArrays(1, &mesh_vao);
    glGenBuffers(1, &mesh_vbo);
    glGenBuffers(1, &mesh_ibo);

    // Génération VAO, VBO pour la trajectoire
    glGenVertexArrays(1, &path_vao);
    glGenBuffers(1, &path_vbo);

    // Génération VAO, VBO et IBO pour le maillage de la sphere
    glGenVertexArrays(1, &sphere_vao);
    glGenBuffers(1, &sphere_vbo);
    glGenBuffers(1, &sphere_ibo);
}

void fillMeshBuffers(void) {
    // Bind du VAO
    glBindVertexArray(mesh_vao);

    // Bind et remplissage du VBO
    glBindBuffer(GL_ARRAY_BUFFER, mesh_vbo);
    glBufferData(GL_ARRAY_BUFFER, mesh_vertices.size() * sizeof(vertex), &mesh_vertices[0], GL_STATIC_DRAW);

    // Bind et remplissage du IBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh_ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh_faces.size() * sizeof(face), &mesh_faces[0], GL_STATIC_DRAW);

    // On active l'attribut 0 qui correspond à la position des sommets
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), nullptr);

    // Unbind du VAO et du VBO. Pas besoin de débind le IBO puisqu'il est lié au VAO
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);
}

void fillPathBuffers(void) {
    // Bind du VAO
    glBindVertexArray(path_vao);

    // Bind et remplissage du VBO
    glBindBuffer(GL_ARRAY_BUFFER, path_vbo);
    glBufferData(GL_ARRAY_BUFFER, path_vertices.size() * sizeof(vertex), &path_vertices[0], GL_STATIC_DRAW);

    // On active l'attribut 0 qui correspond à la position des sommets
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), nullptr);

    // Unbind du VAO et du VBO
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);
}

void fillMeshSphereBuffers(void) {
    // Bind du VAO
    glBindVertexArray(sphere_vao);

    // Bind et remplissage du VBO
    glBindBuffer(GL_ARRAY_BUFFER, sphere_vbo);
    glBufferData(GL_ARRAY_BUFFER, sphere_vertices.size() * sizeof(vertex), &sphere_vertices[0], GL_STATIC_DRAW);

    // Bind et remplissage du IBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, sphere_ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sphere_faces.size() * sizeof(face), &sphere_faces[0], GL_STATIC_DRAW);

    // On active l'attribut 0 qui correspond à la position des sommets
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), nullptr);

    // Unbind du VAO et du VBO. Pas besoin de débind le IBO puisqu'il est lié au VAO
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);
}

void bindExternalArrays(const vector<vertex>& mesh_vertices_in, const vector<face>& mesh_faces_in, const vector<vertex>& path_vertices_in, const vector<vertex>& sphere_vertices_in, const vector<face>& sphere_faces_in) {
    mesh_vertices = mesh_vertices_in;
    mesh_faces = mesh_faces_in;
    path_vertices = path_vertices_in;
    sphere_vertices = sphere_vertices_in;
    sphere_faces = sphere_faces_in;
}

/* ------------------- Affichage de l'interface graphique ------------------- */

int initDisplay() {
    // Initialisation de SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Unable to init SDL: %s\n", SDL_GetError());
        return 1;
    }

    // Fonction appelée à la fermeture du programme
    atexit(SDL_Quit);

    // Création de la fenêtre
    screen = SDL_SetVideoMode(WIDTH, HEIGHT, 16, SDL_OPENGL | SDL_DOUBLEBUF);
    if (!screen) {
        printf("Unable to set screen  : %s\n", SDL_GetError());
        return 1;
    }

    glEnable(GL_DEPTH_TEST);

    // Initialisation de GLEW
    GLenum err = glewInit();
    if (GLEW_OK != err) {
        // ERREUR : initialisation de GLEW a échoué
        std::cerr << "Error: " << glewGetErrorString(err) << std::endl;
    }

    // affichage des infos sur la carte graphique
    std::cout << std::endl
              << "***** Info GPU *****" << std::endl;
    std::cout << "Fabricant : " << glGetString(GL_VENDOR) << std::endl;
    std::cout << "Carte graphique: " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "Version : " << glGetString(GL_VERSION) << std::endl;
    std::cout << "Version GLSL : " << glGetString(GL_SHADING_LANGUAGE_VERSION)
              << std::endl
              << std::endl;

    // Phase d'initialisation des shaders, des matrices et des buffers
    genShaders();
    genMatrices();
    genBuffers();
    fillMeshBuffers();
    fillPathBuffers();

    // Boucle principale de gestion des évènements
    bool done = false;
    while (!done) {
        // message processing loop
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            // check for messages
            switch (event.type) {
                // Sortie de la boucle principale si fermeture de la fenêtre
                case SDL_QUIT:
                    done = true;
                    break;

                // Lecture du clavier à l'appui d'une touche
                case SDL_KEYDOWN:
                    keyboard(event);
                    break;
            }
        }

        // Affichage de la scène à chaque itération
        display();
    }  // end main loop

    printf("Sortie de display\n");
    return 0;
}

void display() {
    // Effacement de l'écran
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Qu'il s'agisse de la trajectoire ou du maillage, on dessine des lignes
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    GLint color_uniform;  // Uniform pour la couleur

    // Affichage de la trajectoire sur la scène
    glLineWidth(8);                                                   // Grosse épaisseur de trait
    glUseProgram(mesh_shader);                                        // Utilisation du shader de la trajectoire
    glBindVertexArray(path_vao);                                      // Bind du VAO de la trajectoire
    MVPid = glGetUniformLocation(mesh_shader, "MVP");                 // Bind de la matrice MVP
    glUniformMatrix4fv(MVPid, 1, GL_FALSE, &MVP[0][0]);               // Envoi de la matrice MVP
    color_uniform = glGetUniformLocation(mesh_shader, "inputColor");  // Bind de la couleur
    glUniform4f(color_uniform, 1.f, 1.f, 1.f, 1.f);                   // blanc
    glDrawArrays(GL_LINE_STRIP, 0, path_vertices.size());             // Dessin de la trajectoire
    glBindVertexArray(0);                                             // Désactivation du VAO

    // Affichage du maillage sur la scène
    glLineWidth(2);                                                           // Épaisseur de trait normale
    glBindVertexArray(mesh_vao);                                              // Bind du VAO du maillage
    MVPid = glGetUniformLocation(mesh_shader, "MVP");                         // Bind de la matrice MVP
    glUniformMatrix4fv(MVPid, 1, GL_FALSE, &MVP[0][0]);                       // Envoi de la matrice MVP
    color_uniform = glGetUniformLocation(mesh_shader, "inputColor");          // Bind de la couleur
    glUniform4f(color_uniform, 0.1f, 0.9f, 0.7f, 1.0f);                       // blanc
    glDrawElements(GL_TRIANGLES, mesh_faces.size() * 3, GL_UNSIGNED_INT, 0);  // Dessin du maillage
    glBindVertexArray(0);                                                     // Désactivation du VAO

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    // Affichage des faces sur la scène
    glBindVertexArray(mesh_vao);                                              // Bind du VAO du maillage
    MVPid = glGetUniformLocation(mesh_shader, "MVP");                         // Bind de la matrice MVP
    glUniformMatrix4fv(MVPid, 1, GL_FALSE, &MVP[0][0]);                       // Envoi de la matrice MVP
    color_uniform = glGetUniformLocation(mesh_shader, "inputColor");          // Bind de la couleur
    glUniform4f(color_uniform, 0.9f, 0.7f, 0.0f, 0.1f);                       // blanc
    glDrawElements(GL_TRIANGLES, mesh_faces.size() * 3, GL_UNSIGNED_INT, 0);  // Dessin du maillage
    glBindVertexArray(0);                                                     // Désactivation du VAO

    /*
        // Affichage du maillage de la sphère sur la scène
        glBindVertexArray(sphere_vao);                                              // Bind du VAO du maillage
        MVPid = glGetUniformLocation(mesh_shader, "MVP");                           // Bind de la matrice MVP
        glUniformMatrix4fv(MVPid, 1, GL_FALSE, &MVP[0][0]);                         // Envoi de la matrice MVP
        color_uniform = glGetUniformLocation(mesh_shader, "inputColor");            // Bind de la couleur
        glUniform4f(color_uniform, 0.9f, 0.7f, 0.0f, 0.1f);                         // blanc
        glDrawElements(GL_TRIANGLES, sphere_faces.size() * 3, GL_UNSIGNED_INT, 0);  // Dessin du maillage
        glBindVertexArray(0); */

    // Échange des buffers d'affichage
    SDL_GL_SwapBuffers();
}

void keyboard(SDL_Event event) {
    switch (event.key.keysym.sym) {
        // Appui sur echap -> Quitter
        case SDLK_ESCAPE:
            exit(0);
            break;
        // Rotation de la scène
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
            glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), (float)(1.f / 360.f) * 20, glm::vec3(0, 0, 1));
            MVP = MVP * rotation;
            break;
        }
        case SDLK_DOWN: {
            glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), (float)(1.f / 360.f) * -20, glm::vec3(0, 0, 1));
            MVP = MVP * rotation;
            break;
        }

        default:
            std::cout << "Touche non reconnue" << std::endl;
    }
}
