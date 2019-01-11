#ifndef FRAMEBUFFER_H_
#define FRAMEBUFFER_H_

#include <GL/glew.h>
#include <glm/glm.hpp>

class FrameBuffer {
public:
	FrameBuffer(int w, int h);

	FrameBuffer(int w, int h, GLuint texID);
	void use();
	void clearToColor(glm::vec4 col);
	void clear();

	~FrameBuffer();
private:
	GLuint ID;
	int width;
	int height;
};

#endif //FrameBuffer.h