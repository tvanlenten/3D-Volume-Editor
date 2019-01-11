#include "Texture.h"

//loads in a 2D texture with the SOIL library
//always bind a texture before writing to or using!
Texture::Texture(std::string filename, GLenum param1, GLenum param2, GLenum param3, GLenum param4, bool mipmap) {
	type = GL_TEXTURE_2D;
	glGenTextures(1, &ID);
	int width, height;
	unsigned char* image = SOIL_load_image(filename.c_str(), &width, &height, 0, SOIL_LOAD_RGB);
	glBindTexture(type, ID);
	glTexImage2D(type, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	if (mipmap)glGenerateMipmap(type);
	glTexParameteri(type, GL_TEXTURE_WRAP_S, param1);
	glTexParameteri(type, GL_TEXTURE_WRAP_T, param2);
	glTexParameteri(type, GL_TEXTURE_MIN_FILTER, param3);
	glTexParameteri(type, GL_TEXTURE_MAG_FILTER, param4);
	glBindTexture(type, 0);
	SOIL_free_image_data(image);
}

Texture::Texture(std::string faces[6], GLenum param1, GLenum param2) {
	type = GL_TEXTURE_CUBE_MAP;
	glGenTextures(1, &ID);
	int width, height;
	unsigned char* image;
	glBindTexture(type, ID);
	for (GLuint i = 0; i < 6; i++) {
		image = SOIL_load_image(faces[i].c_str(), &width, &height, 0, SOIL_LOAD_RGB);
		glTexImage2D(
			GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0,
			GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image
		);
	}
	glTexParameteri(type, GL_TEXTURE_MAG_FILTER, param1);
	glTexParameteri(type, GL_TEXTURE_MIN_FILTER, param1);
	glTexParameteri(type, GL_TEXTURE_WRAP_S, param2);
	glTexParameteri(type, GL_TEXTURE_WRAP_T, param2);
	glTexParameteri(type, GL_TEXTURE_WRAP_R, param2);
	glBindTexture(type, 0);
}

Texture::Texture(GLenum intFormat, GLenum format, GLenum dataType, int width, int height,
	GLenum param1, GLenum param2, unsigned char* image, bool mipmap) {
	type = GL_TEXTURE_2D;
	internalFormat = intFormat;
	glGenTextures(1, &ID);
	glBindTexture(type, ID);
	glTexImage2D(type, 0, internalFormat, width, height, 0, format, dataType, image);
	if (mipmap)glGenerateMipmap(type);
	glTexParameteri(type, GL_TEXTURE_WRAP_S, param1);
	glTexParameteri(type, GL_TEXTURE_WRAP_T, param1);
	glTexParameteri(type, GL_TEXTURE_MIN_FILTER, param2);
	glTexParameteri(type, GL_TEXTURE_MAG_FILTER, param2);
	glBindTexture(type, 0);
}
//3D texture
Texture::Texture(GLenum intFormat, GLenum format, GLenum dataType, int x, int y, int z,
	GLenum param1, GLenum param2, unsigned char* image, bool mipmap) {
	type = GL_TEXTURE_3D;
	internalFormat = intFormat;
	glGenTextures(1, &ID);
	glBindTexture(type, ID);
	glTexImage3D(type, 0, internalFormat, x, y, z, 0, format, dataType, image);
	if (mipmap)glGenerateMipmap(type);
	glTexParameteri(type, GL_TEXTURE_WRAP_S, param1);
	glTexParameteri(type, GL_TEXTURE_WRAP_T, param1);
	glTexParameteri(type, GL_TEXTURE_MIN_FILTER, param2);
	glTexParameteri(type, GL_TEXTURE_MAG_FILTER, param2);
	glBindTexture(type, 0);
}

//use GL_WRITE_ONLY
void Texture::bindTo(int bind, GLenum memoryType) {
	glBindTexture(type, ID);
	glBindImageTexture(bind, ID, 0, GL_TRUE, 0, memoryType, internalFormat);
	glBindTexture(type, 0);
}

void Texture::bind() { 
	glBindTexture(type, ID);
}

void Texture::unbind() { 
	glBindTexture(type, 0);
}

int Texture::getID() { 
	return ID;
}

void Texture::use(GLuint tex) {
	glActiveTexture(GL_TEXTURE0 + tex);
	glBindTexture(type, ID);
}

unsigned char* Texture::random2D(int width, int height)
{
	srand(time(NULL));
	unsigned char* image = (unsigned char*)malloc(width * height * 4);
	for (int i = 0; i < (width * height); i++)
	{
		image[i * 4] = rand() % 255;
		image[i * 4 + 1] = rand() % 255;
		image[i * 4 + 2] = rand() % 255;
		image[i * 4 + 3] = 255;
	}
	return image;
}

unsigned char* Texture::random3D(int RES)
{
	srand(time(NULL));
	unsigned char* volume = (unsigned char*)malloc(RES*RES*RES * 4);
	for (int i = 0; i < RES*RES*RES * 4; i += 4) {

		bool fill = rand() % 1000 < 300;

		volume[i] = unsigned char(i % 255);
		volume[i + 1] = unsigned char((i*i) % 255);
		volume[i + 2] = unsigned char(rand() % 255);
		volume[i + 3] = (fill) ? unsigned char(255) : unsigned char(0);
	}
	return volume;
}

Texture::~Texture() {
	
}