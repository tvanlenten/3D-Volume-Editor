#ifndef MESH_H_
#define MESH_H_

#include <GL/glew.h>
#include "Buffer.h"
#include <iostream>
#include <vector>

#include <glm/glm.hpp>

/*
	This Mesh Builder is very simple and is mainly used just to create the basic
	area where the shader will do ray casting or volume rendering

	This will later be expanded to allow for more complex meshes so that they can be
	converted into signed distance fields probably using the Jump Flooding Algorithm

	TOD0
	-add support for .obj loading
	-add basic primatives
*/

class Mesh {
public:
	Mesh();

	//The vertex array buffer being attach must be bound before this function is called
	void attach(GLenum type, int numberComponents, int stride, int offset, bool instance);

	void setVextexSize(int size);
	void setInstanceSize(int size);
	void bind();
	void draw();
	void unbind();
	void createCube();
	void createRect2D();

	~Mesh();
private:
	GLuint ID;
	unsigned int vertexSize;
	unsigned int instanceSize;
	unsigned int attachSize;
};

#endif //Mesh.h