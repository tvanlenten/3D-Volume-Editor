#include "Shader.h"

Shader::Shader(const GLchar* vertexPath, const GLchar* fragPath, const GLchar* geoPath, bool debug) {
	std::ifstream vertexFile;
	std::ifstream fragFile;
	std::ifstream geoFile;
	std::string vertexCode;
	std::string fragCode;
	std::string geoCode;

	if (geoPath != nullptr)
		type = VFG;
	else
		type = VF;

	//read vertex file
	vertexFile.open(vertexPath);
	if (vertexFile.is_open())
	{
		std::stringstream vertexStream;
		vertexStream << vertexFile.rdbuf();
		vertexCode = vertexStream.str();
	}
	else { std::cout << "ERROR: Can't open vertex shader file at: " << vertexPath << std::endl; }
	vertexFile.close();

	//read fragment file
	fragFile.open(fragPath);
	if (fragFile.is_open())
	{
		std::stringstream fragStream;
		fragStream << fragFile.rdbuf();
		fragCode = fragStream.str();
	}
	else { std::cout << "ERROR: Can't open fragment shader file at: " << fragPath << std::endl; }
	fragFile.close();

	if (geoPath != nullptr) {
		//read geometry file
		geoFile.open(geoPath);
		if (geoFile.is_open())
		{
			std::stringstream geoStream;
			geoStream << geoFile.rdbuf();
			geoCode = geoStream.str();
		}
		else { std::cout << "ERROR: Can't open geometry shader file at: " << geoPath << std::endl; }
		geoFile.close();
	}
	//cast string into array of GLchar
	const GLchar* vCode = vertexCode.c_str();
	const GLchar* fCode = fragCode.c_str();
	const GLchar* gCode = geoCode.c_str();

	if (debug) {
		std::cout << vCode << std::endl << std::endl;
		std::cout << fCode << std::endl << std::endl;
		if (geoPath != nullptr)std::cout << fCode << std::endl << std::endl;
	}

	GLuint vertex, fragment, geometry;
	GLint success;
	GLchar infoLog[512];


	//compile vertex shader
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vCode, NULL);
	glCompileShader(vertex);
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertex, 512, NULL, infoLog);
		std::cout << "ERROR: Vertex shader COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	else {
		std::cout << "Compiled Vertex Shader: " << vertexPath << std::endl;
	}
	//compile fragment shader
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fCode, NULL);
	glCompileShader(fragment);
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragment, 512, NULL, infoLog);
		std::cout << "ERROR: Fragment shader COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	else {
		std::cout << "Compiled Fragment Shader: " << fragPath << std::endl;
	}
	if (geoPath != nullptr) {
		//compile geometry shader
		geometry = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(geometry, 1, &gCode, NULL);
		glCompileShader(geometry);
		glGetShaderiv(geometry, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(geometry, 512, NULL, infoLog);
			std::cout << "ERROR: Geometry shader COMPILATION_FAILED\n" << infoLog << std::endl;
		}
		else {
			std::cout << "Compiled Geometry Shader: " << geoPath << std::endl;
		}
	}
	// link shaders to program
	ID = glCreateProgram();
	glAttachShader(ID, vertex);
	glAttachShader(ID, fragment);
	if (geoPath != nullptr)glAttachShader(ID, geometry);
	glLinkProgram(ID);
	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(ID, 512, NULL, infoLog);
		std::cout << "ERROR: Shader program LINKING_FAILED\n" << infoLog << std::endl;
	}

	//delete shaders
	glDeleteShader(vertex);
	glDeleteShader(fragment);
	if (geoPath != nullptr)glDeleteShader(fragment);
}


Shader::Shader(const char* vCode, const char* fCode, bool debug) {
	GLuint vertex, fragment, geometry;
	GLint success;
	GLchar infoLog[512];


	//compile vertex shader
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vCode, NULL);
	glCompileShader(vertex);

	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (success) {
		printf("Compiled Vertex Shader\n");
	}

	//compile fragment shader
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fCode, NULL);
	glCompileShader(fragment);

	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (success) {
		printf("Compiled Fragment shader\n");
	}

	// link shaders to program
	ID = glCreateProgram();
	glAttachShader(ID, vertex);
	glAttachShader(ID, fragment);
	glLinkProgram(ID);
	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	if (success) {
		printf("Linking Success\n");
	}

	//delete shaders
	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

void Shader::reCompile(const char* vCode, const char* fCode, bool debug) {
	GLuint vertex, fragment, geometry;
	GLint success;
	GLchar infoLog[512];

	//compile vertex shader
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vCode, NULL);
	glCompileShader(vertex);

	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (success) {
		printf("Compiled Vertex Shader\n");
	}

	//compile fragment shader
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fCode, NULL);
	glCompileShader(fragment);

	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (success) {
		printf("Compiled Fragment shader\n");
	}

	// link shaders to program
	ID = glCreateProgram();
	glAttachShader(ID, vertex);
	glAttachShader(ID, fragment);
	glLinkProgram(ID);
	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	if (success) {
		printf("Linking Success\n");
	}

	//delete shaders
	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

//Compute Shader
Shader::Shader(const GLchar* computePath, bool debug) {
	std::ifstream computeFile;
	std::string computeCode;

	type = COMP;

	//read compute file
	computeFile.open(computePath);
	if (computeFile.is_open())
	{
		std::stringstream computeStream;
		computeStream << computeFile.rdbuf();
		computeCode = computeStream.str();
	}
	else { std::cout << "ERROR: Can't open compute shader file at: " << computePath << std::endl; }
	computeFile.close();



	//cast string into array of GLchar
	const GLchar* cCode = computeCode.c_str();

	if (debug)std::cout << cCode << std::endl << std::endl;


	GLuint compute;
	GLint success;
	GLchar infoLog[512];


	//compile vertex shader
	compute = glCreateShader(GL_COMPUTE_SHADER);
	glShaderSource(compute, 1, &cCode, NULL);
	glCompileShader(compute);
	glGetShaderiv(compute, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(compute, 512, NULL, infoLog);
		std::cout << "ERROR: Compute shader COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	else {
		std::cout << "Compiled Compute Shader: " << computePath << std::endl;
	}


	// link shaders to program
	ID = glCreateProgram();
	glAttachShader(ID, compute);
	glLinkProgram(ID);
	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(ID, 512, NULL, infoLog);
		std::cout << "ERROR: Shader program LINKING_FAILED\n" << infoLog << std::endl;
	}

	//delete shaders
	glDeleteShader(compute);
}

void Shader::use() { 
	glUseProgram(ID);
}

//has a memory barrier to ensure what the compute shader is writing too is not read
void Shader::invoke(glm::vec3 res) {
	if (type == COMP) {
		glDispatchCompute((GLuint)res.x, (GLuint)res.y, (GLuint)res.z);
	}
}

void Shader::memoryBarrior() {
	glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);
}


//set Uniforms for Shader taken from www.learnopengl.com
void Shader::setBool(const std::string &name, bool value) { glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value); }
void Shader::setInt(const std::string &name, int value) { glUniform1i(glGetUniformLocation(ID, name.c_str()), value); }
void Shader::setFloat(const std::string &name, float value) { glUniform1f(glGetUniformLocation(ID, name.c_str()), value); }
void Shader::setVec2(const std::string &name, const glm::vec2 &value) { glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]); }
void Shader::setVec2(const std::string &name, float x, float y) { glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y); }
void Shader::setVec3(const std::string &name, const glm::vec3 &value) { glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]); }
void Shader::setVec3(const std::string &name, float x, float y, float z) { glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z); }
void Shader::setVec4(const std::string &name, const glm::vec4 &value) { glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]); }
void Shader::setVec4(const std::string &name, float x, float y, float z, float w) { glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w); }
void Shader::setMat2(const std::string &name, const glm::mat2 &mat) { glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]); }
void Shader::setMat3(const std::string &name, const glm::mat3 &mat) { glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]); }
void Shader::setMat4(const std::string &name, const glm::mat4 &mat) { glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]); }

Shader::~Shader() {
	
}