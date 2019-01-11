#ifndef BUFFER_H_
#define BUFFER_H_

#include <GL/glew.h>

/*
	add support for map range instead of bufferSubData
*/

class Buffer {
public:
	Buffer(GLenum buffer_type, unsigned int dataSize, GLvoid* data, GLenum memoryType);

	void update(int offset, int size, GLvoid* data);
	void bind();
	void bindTo(int base);
	void unbind();

	~Buffer();
private:
	GLuint ID;
	GLenum bufferType;
};

#endif //Buffer.h