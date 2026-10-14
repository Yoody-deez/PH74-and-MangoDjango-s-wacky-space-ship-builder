#include "vertexArray.h"

VertexArray::VertexArray() : id(0) {
		glGenVertexArrays(1, &id);
}

VertexArray::~VertexArray() {
		if (id != 0) {
				glDeleteVertexArrays(1, &id);
		}
}

void VertexArray::bind() const {
		glBindVertexArray(id);
}

void VertexArray::unbind() const {
		glBindVertexArray(0);
}

void VertexArray::addAttribute(const Buffer& vbo, int index, int size, GLenum type = GL_FLOAT, GLboolean normalized = GL_FALSE, GLsizei stride = 0, const void* pointer = 0) {
		bind();
		vbo.bind();
		glVertexAttribPointer(index, size, type, normalized, stride, pointer);
		glEnableVertexAttribArray(index);
		vbo.unbind();
		unbind();
}