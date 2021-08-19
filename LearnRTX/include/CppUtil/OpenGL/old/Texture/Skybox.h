#pragma once
#include<glm.hpp>
#include<string>
#include<vector>
#include<gl/glew.h>
#include"Shader.h"

#include<assimp/Importer.hpp>
#include<assimp/scene.h>
#include<assimp/postprocess.h>
using std::string;
class Skybox
{
public:
	Skybox(std::vector<GLfloat>const& _vertices, std::vector<string>& _faces);// Draw Array,CubemapTexture
	GLuint GettextureID() { return this->textureID; };
	void stepMesh();
	void LoadCubemap(std::vector<string>& faces);
	void Draw(Shader* shader, glm::mat4 view, glm::mat4 projection);
	~Skybox() {};
private:
	GLuint textureID;// If possible.
	GLuint VAO, VBO;
	std::vector<GLfloat> vertices;
	std::vector<string> faces;
};

