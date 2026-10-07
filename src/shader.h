#pragma once
#include <glad/gl.h>
#include <string>

class Shader {
public:
    static GLuint createShaderProgram(const std::string& vertexPath, const std::string& fragmentPath);

private:
    static std::string loadShaderSource(const std::string& filePath);
    static bool checkCompileErrors(GLuint shader, const std::string& type);
};