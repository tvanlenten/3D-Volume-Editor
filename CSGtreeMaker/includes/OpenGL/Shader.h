#ifndef SHADER_H_
#define SHADER_H_

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <fstream>
#include <string>
#include <sstream>
#include <iostream>

enum shaderType {
	VF,
	VFG,
	COMP
};

/*
	Compiles shader files of all types including Vetex, Fragment, Geomotry, and Compute
	It also has simple functions to use the shader and send uniforms to the shader
*/

class Shader {
public:
	Shader(const GLchar* vertexPath, const GLchar* fragPath, const GLchar* geoPath, bool debug);

	/*
		Takes shaders in as char arrays already loaded in RAM
		This should be faster for quick shader compilation
	*/
	Shader(const char* vCode, const char* fCode, bool debug);

	//Compute Shader
	Shader(const GLchar* computePath, bool debug);

	void reCompile(const char* vCode, const char* fCode, bool debug);

	void use();

	//has a memory barrier to ensure what the compute shader is writing too is not read
	void invoke(glm::vec3 res);

	void memoryBarrior();


	//set Uniforms for Shader taken from www.learnopengl.com
	void setBool(const std::string &name, bool value);
	void setInt(const std::string &name, int value);
	void setFloat(const std::string &name, float value);
	void setVec2(const std::string &name, const glm::vec2 &value);
	void setVec2(const std::string &name, float x, float y);
	void setVec3(const std::string &name, const glm::vec3 &value);
	void setVec3(const std::string &name, float x, float y, float z);
	void setVec4(const std::string &name, const glm::vec4 &value);
	void setVec4(const std::string &name, float x, float y, float z, float w);
	void setMat2(const std::string &name, const glm::mat2 &mat);
	void setMat3(const std::string &name, const glm::mat3 &mat);
	void setMat4(const std::string &name, const glm::mat4 &mat);

	~Shader();
private:
	GLuint ID;
	shaderType type;
};

#endif //Shader.h