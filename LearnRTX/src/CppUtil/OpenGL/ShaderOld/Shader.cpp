#include "Shader.h"
#include<iostream>
#include<fstream>
#include<sstream>


#include<GL/glew.h>
#include<GLFW/glfw3.h>

using std::ifstream;
using std::exception;
using std::stringstream;

/*What makes the geometry shader interesting is that it is able to convert the original primitive (set of vertices) 
| to completely different primitives, possibly generating more vertices than were initially given.*/
Shader::Shader(const char* vertexPath, const char* fragmentPath, const char* geometryPath) {
	ifstream vertexFile;
	ifstream fragmentFile;
	ifstream geometryFile;

	string vertexString;
	string fragmentString;
	string geometryString;

	const char* vertexSource;
	const char* fragmentSource;
	const char* geometrySource;
	
	// 
	vertexFile.exceptions(ifstream::failbit || ifstream::badbit);
	fragmentFile.exceptions(ifstream::failbit || ifstream::badbit);
	geometryFile.exceptions(ifstream::failbit || ifstream::badbit);

	try {
		vertexFile.open(vertexPath);
		fragmentFile.open(fragmentPath);

		stringstream vertexSStream;
		stringstream fragmentSStream;
		vertexSStream << vertexFile.rdbuf();
		fragmentSStream << fragmentFile.rdbuf();
		vertexFile.close();
		fragmentFile.close();

		// 
		vertexString = vertexSStream.str();
		fragmentString = fragmentSStream.str();

		vertexSource = vertexString.c_str();
		fragmentSource = fragmentString.c_str();

		if (geometryPath != nullptr)
		{
			geometryFile.open(geometryPath);
			stringstream geomtrySStream;
			geomtrySStream << geometryFile.rdbuf();
			geometryFile.close();
			geometryString = geomtrySStream.str();
		}

		// 
		unsigned int vertex, fragment;

		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vertexSource, NULL);
		glCompileShader(vertex);
		checkCompileErrors(vertex, "VERTEX");

		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fragmentSource, NULL);
		glCompileShader(fragment);
		checkCompileErrors(fragment, "FRAGMENT");

		unsigned int geometry;
		if (geometryPath != nullptr)
		{
			geometrySource = geometryString.c_str();
			geometry = glCreateShader(GL_GEOMETRY_SHADER);
			glShaderSource(geometry, 1, &geometrySource, NULL);
			glCompileShader(geometry);
			checkCompileErrors(geometry, "GEOMETRY");
		}

		ID = glCreateProgram();
		glAttachShader(ID, vertex);
		glAttachShader(ID, fragment);
		if (geometryPath != nullptr)
			glAttachShader(ID, geometry);
		glLinkProgram(ID);
		checkCompileErrors(ID, "PROGRAM");

		// Don't forget to delete the shader objects once we've linked them into the program object
		glDeleteShader(vertex);
		glDeleteShader(fragment);
		if (geometryPath != nullptr)
			glDeleteShader(geometry);
	}
	catch (std::ifstream::failure& e) {
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}
}

void Shader::use() {
	glUseProgram(ID);
}

/* Advanced GLSL*/
void Shader::UniformBlockBinding(const char* name, int slot)
{
	GLuint uniformBlockIndex = glGetUniformBlockIndex(ID, name);// First. We get the relevant block indices
	glUniformBlockBinding(ID, uniformBlockIndex, slot);// Then we link each shader's uniform block to this uniform binding point
}

void Shader::checkCompileErrors(unsigned int ID, string type) {
	int success;
	char infoLog[512];

	if (type != "PROGRAM") {
		glGetShaderiv(ID, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(ID, 512, NULL, infoLog);
			std::cout << "shader compile error:" << infoLog << std::endl;
		}
	}
	else {
		glGetProgramiv(ID, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(ID, 512, NULL, infoLog);
			std::cout << "compile program error:" << infoLog << std::endl;
		}
	}
}

void Shader::setBool(const char* name, bool slot) const
{
	glUniform1i(glGetUniformLocation(ID, name), slot);
}

void Shader::setInt(const char* paramNameString, int slot) const
{
	glUniform1i(glGetUniformLocation(ID, paramNameString), slot);
}

void Shader::setFloat(const char* paramNameString, float param) const
{
	glUniform1f(glGetUniformLocation(ID, paramNameString), param);
}

void Shader::setVec2(const char* paramNameString, const glm::vec2& value) const
{
	glUniform2fv(glGetUniformLocation(ID, paramNameString), 1, &value[0]);
}

void Shader::setVec2(const char* paramNameString, float x, float y) const
{
	glUniform2f(glGetUniformLocation(ID, paramNameString), x, y);
}

void Shader::setVec3(const char* paramNameString, const glm::vec3& param)const
{
	glUniform3fv(glGetUniformLocation(ID, paramNameString), 1, &param[0]);
}

void Shader::setVec3(const char* paramNameString, float x, float y, float z) const
{
	glUniform3f(glGetUniformLocation(ID, paramNameString), x, y, z);
}

void Shader::setVec4(const char* paramNameString, const glm::vec4& value) const
{
	glUniform4fv(glGetUniformLocation(ID, paramNameString), 1, &value[0]);
}

void Shader::setVec4(const char* paramNameString, float x, float y, float z, float w)
{
	glUniform4f(glGetUniformLocation(ID, paramNameString), x, y, z, w);
}

void Shader::setMat2(const char* paramNameString, const glm::mat2& mat) const
{
	glUniformMatrix2fv(glGetUniformLocation(ID, paramNameString), 1, GL_FALSE, &mat[0][0]);
}

void Shader::setMat3(const char* paramNameString, const glm::mat3& mat) const
{
	glUniformMatrix3fv(glGetUniformLocation(ID, paramNameString), 1, GL_FALSE, &mat[0][0]);
}

void Shader::setMat4(const char* paramNameString, const glm::mat4& param)const
{
	glUniformMatrix4fv(glGetUniformLocation(ID, paramNameString), 1, GL_FALSE, glm::value_ptr(param));
}
