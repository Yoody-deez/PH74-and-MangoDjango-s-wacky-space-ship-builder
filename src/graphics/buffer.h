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
    Buffer(Type t);

    ~Buffer();

    void bind() const;

    void unbind() const;

    void setData(void* data, size_t size);

    unsigned int getId() const;
};