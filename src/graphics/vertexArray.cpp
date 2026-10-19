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

void VertexArray::addAttribute(const Buffer& vbo, int index, int size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer) {
		bind();
		vbo.bind();
		glVertexAttribPointer(index, size, type, normalized, stride, pointer);
		glEnableVertexAttribArray(index);
		vbo.unbind();
		unbind();
}