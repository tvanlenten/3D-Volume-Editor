#include "Buffer.h"

Buffer::Buffer(GLenum buffer_type, unsigned int dataSize, GLvoid* data, GLenum memoryType) {
	bufferType = buffer_type;
	glGenBuffers(1, &ID);
	glBindBuffer(bufferType, ID);
	glBufferData(bufferType, dataSize, data, memoryType);
	glBindBuffer(bufferType, 0);
}

void Buffer::update(int offset, int size, GLvoid* data) {
	glBindBuffer(bufferType, ID);
	glBufferSubData(bufferType, offset, size, data);
	glBindBuffer(bufferType, 0);
}

void Buffer::bind() {
	glBindBuffer(bufferType, ID);
}

void Buffer::bindTo(int base) {
	glBindBufferBase(bufferType, base, ID);
}

void Buffer::unbind() {
	glBindBuffer(bufferType, 0);
}

Buffer::~Buffer() {
	glDeleteBuffers(1, &ID);
}