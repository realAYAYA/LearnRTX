#pragma once
#include "Light.h"
#include <glm.hpp>
//#include <gtc/matrix_transform.hpp>
#include<gtx/rotate_vector.hpp>// 
class Shader;
class LightPoint:public Light
{
public:
	LightPoint(glm::vec3 _position, glm::vec3 _color = glm::vec3(1.0f, 1.0f, 1.0f));
	~LightPoint() {};

	glm::vec3 position;
	glm::vec3 color;

	float constant = 1.0f;
	float linear = 0.7f;
	float quadratic = 1.8f;
};

