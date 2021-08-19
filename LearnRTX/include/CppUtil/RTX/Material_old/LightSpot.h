#pragma once
#include "Light.h"
#include<glm.hpp>
//#include <gtc/matrix_transform.hpp>
#include<gtx/rotate_vector.hpp>// 
class Shader;
class LightSpot:public Light
{
public:
	LightSpot(std::string _name, glm::vec3 _position, glm::vec3 _angles, glm::vec3 _color = glm::vec3(1.0f, 1.0f, 1.0f));
	~LightSpot() {};

	glm::vec3 position;
	glm::vec3 angles;
	glm::vec3 direction = glm::vec3(0, 0, 1.0f);
	glm::vec3 color;

	float constant;
	float linear;
	float quadratic;

	float cosPhyInner = 0.95f;
	float cosPhyOutter = 0.85f;

	void UpdateDirection();

	void active(Shader* shader)const;
};

