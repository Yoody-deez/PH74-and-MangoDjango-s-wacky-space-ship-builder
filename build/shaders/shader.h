#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glad/gl.h>

class Shader {
protected:
    unsigned int id;

public:
    Shader(const std::string& path, GLenum shaderType) : id(0) {
        std::string code;
        std::ifstream file;
        file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        try {
            file.open(path);
            std::stringstream stream;
            stream << file.rdbuf();
            file.close();
            code = stream.str();
        } catch (std::ifstream::failure& e) {
            std::cerr << "ERREUR::SHADER::FICHIER_INTROUVABLE : " << path << std::endl;
        }
        const char* shaderCode = code.c_str();

        id = glCreateShader(shaderType);
        glShaderSource(id, 1, &shaderCode, NULL);
    }

    virtual ~Shader() {
        if (id != 0) {
            glDeleteShader(id);
        }
    }

    bool compile() {
        glCompileShader(id);
        int success;
        char infoLog[512];
        glGetShaderiv(id, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(id, 512, NULL, infoLog);
            std::cerr << "ERREUR::SHADER::COMPILATION_ECHOUEE\n" << infoLog << std::endl;
            return false;
        }
        return true;
    }

    unsigned int getId() const { return id; }
};