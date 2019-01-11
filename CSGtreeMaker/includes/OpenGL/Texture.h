#ifndef TEXTURE_H_
#define TEXTURE_H_


#include <string.h>
#include <GL/glew.h>
#include <SOIL.h>
#include "time.h"
#include <math.h>
#include <iostream>

/*
	Creates a texture to be used in shaders
*/

class Texture {
public:
	/*
		loads in a 2D texture with the SOIL library
		always bind a texture before writing to or using!
	*/
	Texture(std::string filename, GLenum param1, GLenum param2, GLenum param3, GLenum param4, bool mipmap);

	/*
		create Cubemap
	*/
	Texture(std::string faces[6], GLenum param1, GLenum param2);

	/*
		create custom 2D texture
	*/
	Texture(GLenum intFormat, GLenum format, GLenum dataType, int width, int height,
		GLenum param1, GLenum param2, unsigned char* image, bool mipmap);
	
	/*
		create custom 3D texture
	*/
	Texture(GLenum intFormat, GLenum format, GLenum dataType, int x, int y, int z,
		GLenum param1, GLenum param2, unsigned char* image, bool mipmap);

	/*
		USE GL_WRITE_ONLY
	*/
	void bindTo(int bind, GLenum memoryType);

	void bind();
	void unbind();
	int getID();
	void use(GLuint tex);
	unsigned char* random2D(int width, int height);
	unsigned char* random3D(int RES);

	~Texture();
private:
	GLuint ID;
	GLenum type;
	GLenum internalFormat;
};

#endif //Texture.h