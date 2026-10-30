#pragma once
#include "Buffer.h"

class VertexArray {
private:
    unsigned int id;

public:
    VertexArray();

    ~VertexArray();

    void bind() const;

    void unbind() const;

    void addAttribute(const Buffer& vbo, int index, int size, GLenum type = GL_FLOAT, GLboolean normalized = GL_FALSE, GLsizei stride = 0, const void* pointer = 0);
};