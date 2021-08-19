#pragma once
#include<string>

enum LightType
{
	Point,
	Spot,
	Directional
};

class Shader;

class Light
{
public:
	std::string name;
	LightType type;
	virtual void active(Shader* shader)const {}

};