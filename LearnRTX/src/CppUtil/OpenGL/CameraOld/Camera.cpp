#include "Camera.h"
#include<GL/glew.h>
#include<GLFW/glfw3.h>

Camera::Camera(glm::vec3 position, glm::vec3 target, glm::vec3 worldup) {
	Position = position;
	Forward = glm::normalize(target - position);
	WorldUp = worldup;
	Right = glm::normalize(glm::cross(Forward, WorldUp));
	Up = glm::normalize(glm::cross(Right, Forward));
}

Camera::Camera(glm::vec3 position, float pitch, float yaw, glm::vec3 worldup) {
	Position = position;
	WorldUp = worldup;
	Pitch = pitch;
	Yaw = yaw;
	Forward.x = glm::cos(Pitch) * glm::sin(Yaw);
	Forward.y = glm::sin(Pitch);
	Forward.z = glm::cos(Pitch) * glm::cos(Yaw);
	Right = glm::normalize(glm::cross(Forward, WorldUp));
	Up = glm::normalize(glm::cross(Forward, Right));
}

Camera::~Camera() {

}

glm::mat4 Camera::GetViewMarix()const {
	// The glm::LookAt function requires a position, target and up vector respectively.
	return glm::lookAt(Position, Position + Forward, WorldUp);
}

void Camera::UpdateCameraVectors() {
	Forward.x = glm::cos(Pitch) * glm::sin(Yaw);
	Forward.y = glm::sin(Pitch);
	Forward.z = glm::cos(Pitch) * glm::cos(Yaw);
	Right = glm::normalize(glm::cross(Forward, WorldUp));
	Up = glm::normalize(glm::cross(Right, Forward));
}

void Camera::ProcessMouseMovement(float deltaX, float deltaY) {
    float temp = Pitch - deltaY * MouseSensitivity;
    if (temp > 89.0f) {
        Pitch = 89.0f;
    }else if (temp < -89.0f) {
        Pitch = -89.0f;
    }else{
        Pitch = temp;
    }

	Yaw -= deltaX * MouseSensitivity;
	UpdateCameraVectors();
}

void Camera::ProcessMouseScroll(float yoffset)
{
    Zoom -= (float)yoffset;
    if (Zoom < 1.0f)
        Zoom = 1.0f;
    if (Zoom > 45.0f)
        Zoom = 45.0f;
}

void Camera::processInput(GLFWwindow* window, const float& deltaTime)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
    float velocity = MovementSpeed * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        Position += Forward * velocity;
    }
    if (glfwGetKey(window, GLFW_KEY_S)) {
        Position -= Forward * velocity;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        Position -= Right * velocity;
    }
    if (glfwGetKey(window, GLFW_KEY_D)) {
        Position += Right * velocity;
    }
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        Position += Up * velocity;
    }
    if (glfwGetKey(window, GLFW_KEY_X)) {
        Position -= Up * velocity;
    }
}
