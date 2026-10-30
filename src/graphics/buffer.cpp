#include "buffer.h"


Buffer::Buffer(Type t) : id(0), type(static_cast<GLenum>(t)) {
		glGenBuffers(1, &id);
}

Buffer::~Buffer() {
		if (id != 0) {
				glDeleteBuffers(1, &id);
		}
}

void Buffer::bind() const {
		glBindBuffer(type, id);
}

void Buffer::unbind() const {
		glBindBuffer(type, 0);
}

void Buffer::setData(void* data, size_t size) {
		bind();
		glBufferData(type, size, data, GL_STATIC_DRAW);
}

unsigned int Buffer::getId() const { return id; }