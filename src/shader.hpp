/*
        CE FICHIER PROVIENT DU COURS
        Il permet de charger les shaders.
        Il n'a pas été modifié du tout.
*/

#ifndef SHADER_HPP
#define SHADER_HPP

/**
 * @brief Charge les shaders
 *
 * @param vertex_file_path chemin vers le vertex shader
 * @param fragment_file_path chemin vers le fragment shader
 * @param geometry_file_path chemin vers le geometry shader (peut être nullptr)
 * @return GLuint
 */
GLuint LoadShaders(const char* vertex_file_path, const char* fragment_file_path, const char* geometry_file_path);

#endif
