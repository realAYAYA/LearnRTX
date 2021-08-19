#pragma once

#include"Shader.h"
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

class Material
{
public:
	Shader* shader;
	unsigned int diffuse;
	unsigned int specular;
	glm::vec3 ambient;
	float shininess;

	Material(Shader* _shader, unsigned int _diffuse,unsigned int _specular, glm::vec3 _ambient, float _shininess) :
		shader(_shader), 
		diffuse(_diffuse),
		specular(_specular),
		ambient(_ambient),
		shininess(_shininess)
	{

	}
	~Material() {};
};
