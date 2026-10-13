#pragma once
#include <glad/gl.h>

class Buffer {
public:
    enum class Type {
        VERTEX = GL_ARRAY_BUFFER,
        INDEX = GL_ELEMENT_ARRAY_BUFFER
    };

private:
    unsigned int id;
    GLenum type;

public:
    Buffer(Type t) : id(0), type(static_cast<GLenum>(t)) {
        glGenBuffers(1, &id);
    }

    ~Buffer() {
        if (id != 0) {
            glDeleteBuffers(1, &id);
        }
    }

    void bind() const {
        glBindBuffer(type, id);
    }

    void unbind() const {
        glBindBuffer(type, 0);
    }

    void setData(void* data, size_t size) {
        bind();
        glBufferData(type, size, data, GL_STATIC_DRAW);
    }

    unsigned int getId() const { return id; }
};