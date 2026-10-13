#pragma once
#include <glad/gl.h>
#include "Buffer.h"

class VertexArray {
private:
    unsigned int id;

public:
    VertexArray() : id(0) {
        glGenVertexArrays(1, &id);
    }

    ~VertexArray() {
        if (id != 0) {
            glDeleteVertexArrays(1, &id);
        }
    }

    void bind() const {
        glBindVertexArray(id);
    }

    void unbind() const {
        glBindVertexArray(0);
    }

    void addAttribute(const Buffer& vbo, int index, int size, GLenum type = GL_FLOAT, GLboolean normalized = GL_FALSE, GLsizei stride = 0, const void* pointer = 0) {
        bind();
        vbo.bind();
        glVertexAttribPointer(index, size, type, normalized, stride, pointer);
        glEnableVertexAttribArray(index);
        vbo.unbind();
        unbind();
    }
};