#pragma once
#define GLEW_STATIC

#include"Object.h"
#include<glm.hpp>
#include<gtc/matrix_transform.hpp>

enum Camera_Movement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

// Default camera values
const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 3.5f;
const float SENSITIVITY = 0.007f;
const float ZOOM = 45.0f;

class Camera :Object
{
public:
	Camera(glm::vec3 position, glm::vec3 target, glm::vec3 worldup);
	Camera(glm::vec3 position, float pitch, float yaw, glm::vec3 worldup);
	~Camera();

	glm::vec3 GetPosition()const { return this->Position; }
	glm::mat4 GetViewMarix()const;
	void ProcessMouseMovement(float deltaX, float deltaY);
	void ProcessMouseScroll(float yoffset);

	/* Input helper*/
	void processInput(class GLFWwindow* window,const float& deltaTime);

private:
	void UpdateCameraVectors();

	glm::vec3 Position;
	glm::vec3 Forward;
	glm::vec3 Right;
	glm::vec3 Up;
	glm::vec3 WorldUp;

	float Pitch;
	float Yaw;

	float MovementSpeed = SPEED;
	float MouseSensitivity = SENSITIVITY;
	float Zoom;
};