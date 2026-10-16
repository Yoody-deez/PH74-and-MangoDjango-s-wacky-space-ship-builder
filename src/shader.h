#pragma once
#include <glad/gl.h>
#include <string>

using namespace std;

class Shader {
public:
    static GLuint createShaderProgram(const string& vertexPath, const string& fragmentPath);

private:
    static string loadShaderSource(const string& filePath);
    static bool checkCompileErrors(GLuint shader, const string& type);
};