#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <glad/gl.h>
#include "shader.h"

class ShaderProgram {
private:
    unsigned int id;

public:
    ShaderProgram() : id(0) {
        id = glCreateProgram();
    }

    ~ShaderProgram() {
        if (id != 0) {
            glDeleteProgram(id);
        }
    }

    void attach(Shader* shader) {
        if (shader) {
            glAttachShader(id, shader->getId());
        }
    }

    bool link() {
        glLinkProgram(id);
        int success;
        char infoLog[512];
        glGetProgramiv(id, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(id, 512, NULL, infoLog);
            std::cerr << "ERREUR::SHADER::PROGRAMME::LINK_ECHOE\n" << infoLog << std::endl;
            return false;
        }
        return true;
    }

    void use() {
        glUseProgram(id);
    }

    int getUniformLocation(const std::string& name) const {
        return glGetUniformLocation(id, name.c_str());
    }

   bool saveBinary(const std::string& path) {
        GLint length = 0;
        glGetProgramiv(id, GL_PROGRAM_BINARY_LENGTH, &length);
        if (length <= 0) {
            std::cerr << "ERREUR::SHADER::BINARY : Taille du binaire invalide." << std::endl;
            return false;
        }

        std::vector<unsigned char> buffer(length);
        GLenum binaryFormat = 0;
        glGetProgramBinary(id, length, NULL, &binaryFormat, buffer.data());

        std::ofstream file(path, std::ios::binary);
        if (!file.is_open()) {
            std::cerr << "ERREUR::SHADER::BINARY : Impossible d'ouvrir le fichier en écriture : " << path << std::endl;
            return false;
        }

        file.write(reinterpret_cast<const char*>(&binaryFormat), sizeof(binaryFormat));
        file.write(reinterpret_cast<char*>(buffer.data()), length);
        file.close();

        return true;
    }

    bool loadBinary(const std::string& path) {
        std::ifstream file(path, std::ios::binary);
        if (!file.is_open()) {
            return false;
        }

        GLenum binaryFormat;
        file.read(reinterpret_cast<char*>(&binaryFormat), sizeof(binaryFormat));

        file.seekg(0, std::ios::end);
        std::streamsize length = file.tellg();
        file.seekg(sizeof(binaryFormat), std::ios::beg);

        std::streamsize dataLength = length - sizeof(binaryFormat);
        std::vector<unsigned char> buffer(dataLength);
        file.read(reinterpret_cast<char*>(buffer.data()), dataLength);
        file.close();

        glProgramBinary(id, binaryFormat, buffer.data(), dataLength);

        GLint success = 0;
        glGetProgramiv(id, GL_LINK_STATUS, &success);
        if (!success) {
            char infoLog[512];
            glGetProgramInfoLog(id, 512, NULL, infoLog);
            std::cerr << "ERREUR::SHADER::BINARY::LOAD_ECHOE\n" << infoLog << std::endl;
            return false;
        }

        return true;
    }

    unsigned int getId() const { return id; }
};