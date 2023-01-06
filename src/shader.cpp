/*
        CE FICHIER PROVIENT DU COURS
        Il permet de charger les shaders.
        Il n'a pas été modifié du tout.
*/

#include <stdio.h>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
#include <stdlib.h>
#include <string.h>

#include <sstream>

#include "shader.hpp"

GLuint LoadShaders(const char* vertex_file_path, const char* fragment_file_path, const char* geometry_file_path = nullptr) {
    // Create the shaders
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    GLuint geometryShader;
    if (geometry_file_path != nullptr)
        geometryShader = glCreateShader(GL_GEOMETRY_SHADER);

    // Read the Vertex Shader code from the file
    std::string vertexShaderCode;
    std::ifstream vertexShaderStream(vertex_file_path, std::ios::in);
    if (vertexShaderStream.is_open()) {
        std::stringstream sstr;
        sstr << vertexShaderStream.rdbuf();
        vertexShaderCode = sstr.str();
        vertexShaderStream.close();
    } else {
        std::cerr << "Failed to open vertex shader file: " << vertex_file_path << std::endl;
        return 0;
    }

    // Read the Fragment Shader code from the file
    std::string fragmentShaderCode;
    std::ifstream fragmentShaderStream(fragment_file_path, std::ios::in);
    if (fragmentShaderStream.is_open()) {
        std::stringstream sstr;
        sstr << fragmentShaderStream.rdbuf();
        fragmentShaderCode = sstr.str();
        fragmentShaderStream.close();
    } else {
        std::cerr << "Failed to open fragment shader file: " << fragment_file_path << std::endl;
        return 0;
    }

    // Read the Geometry Shader code from the file if specified
    std::string geometryShaderCode;
    if (geometry_file_path != nullptr) {
        std::ifstream geometryShaderStream(geometry_file_path, std::ios::in);
        if (geometryShaderStream.is_open()) {
            std::stringstream sstr;
            sstr << geometryShaderStream.rdbuf();
            geometryShaderCode = sstr.str();
            geometryShaderStream.close();
        } else {
            std::cerr << "Failed to open geometry shader file: " << geometry_file_path << std::endl;
            return 0;
        }
    }

    GLint result = GL_FALSE;
    int infoLogLength;

    // Compile Vertex Shader
    std::cout << "Compiling vertex shader: " << vertex_file_path << std::endl;
    char const* vertexSourcePointer = vertexShaderCode.c_str();
    glShaderSource(vertexShader, 1, &vertexSourcePointer, NULL);
    glCompileShader(vertexShader);

    // Check Vertex Shader
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &result);
    glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &infoLogLength);
    if (infoLogLength > 0) {
        std::vector<char> vertexShaderErrorMessage(infoLogLength + 1);
        glGetShaderInfoLog(vertexShader, infoLogLength, NULL, &vertexShaderErrorMessage[0]);
        std::cerr << &vertexShaderErrorMessage[0] << std::endl;
    }

    // Compile Fragment Shader
    std::cout << "Compiling fragment shader: " << fragment_file_path << std::endl;
    char const* fragmentSourcePointer = fragmentShaderCode.c_str();
    glShaderSource(fragmentShader, 1, &fragmentSourcePointer, NULL);
    glCompileShader(fragmentShader);

    // Check Fragment Shader
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &result);
    glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &infoLogLength);
    if (infoLogLength > 0) {
        std::vector<char> fragmentShaderErrorMessage(infoLogLength + 1);
        glGetShaderInfoLog(fragmentShader, infoLogLength, NULL, &fragmentShaderErrorMessage[0]);
        std::cerr << &fragmentShaderErrorMessage[0] << std::endl;
    }

    // Compile Geometry Shader if specified
    if (geometry_file_path != nullptr) {
        std::cout << "Compiling geometry shader: " << geometry_file_path << std::endl;
        char const* geometrySourcePointer = geometryShaderCode.c_str();
        glShaderSource(geometryShader, 1, &geometrySourcePointer, NULL);
        glCompileShader(geometryShader);

        // Check Geometry Shader
        glGetShaderiv(geometryShader, GL_COMPILE_STATUS, &result);
        glGetShaderiv(geometryShader, GL_INFO_LOG_LENGTH, &infoLogLength);
        if (infoLogLength > 0) {
            std::vector<char> geometryShaderErrorMessage(infoLogLength + 1);
            glGetShaderInfoLog(geometryShader, infoLogLength, NULL, &geometryShaderErrorMessage[0]);
            std::cerr << &geometryShaderErrorMessage[0] << std::endl;
        }
    }

    // Link the program
    std::cout << "Linking program" << std::endl;
    GLuint program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    if (geometry_file_path != nullptr)
        glAttachShader(program, geometryShader);
    glLinkProgram(program);

    // Check the program
    glGetProgramiv(program, GL_LINK_STATUS, &result);
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);
    if (infoLogLength > 0) {
        std::vector<char> programErrorMessage(infoLogLength + 1);
        glGetProgramInfoLog(program, infoLogLength, NULL, &programErrorMessage[0]);
        std::cerr << &programErrorMessage[0] << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    if (geometry_file_path != nullptr)
        glDeleteShader(geometryShader);

    return program;
}