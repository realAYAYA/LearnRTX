/*
* 
*/
#ifndef _GLOBALDEFINES_H_
#define _GLOBALDEFINES_H_

#include<iostream>

#include<GL/glew.h>
#include<GLFW/glfw3.h>

#include <CppUtil/OpenGL/Camera.h>
#include<SOIL/SOIL.h> //#include<CppUtil/Basic/stb_image.h>

const unsigned int SCR_WIDTH = 1920;
const unsigned int SCR_HEIGHT = 1080;

float lastX, lastY;
bool firstMouse = true;

float deltaTime = 0.0f;
float lastFrame = 0.0f;

std::string rootPath;
std::string shaderPath;
std::string texturePath;
std::string modelPath;

#pragma region Camera Declare
CppUtil::OpenGL::Camera mainCamera(glm::vec3(0.0f, 0.0f, 10.0f), glm::radians(-15.0f), glm::radians(180.0f), (GLfloat)SCR_WIDTH / (GLfloat)SCR_HEIGHT, 0.1f, 100, glm::vec3(0, 1.0f, 0), CppUtil::OpenGL::Camera::PROJECTION_PERSEPCTIVE);
#pragma endregion

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(class GLFWwindow* window, double xPos, double yPos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

// SOIL: 
// ---------------------------------------------------------------------------------------------
unsigned int LoadImageToGPU(const char* filename);

// Texture to Map: 
// ---------------------------------------------------------------------------------------------
size_t DataToMap(vector<float>& data);

float lerp(float a, float b, float f);// Accelerating interpolation function

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xPos, double yPos)
{
    if (firstMouse) {
        lastX = xPos;
        lastY = yPos;
        firstMouse = false;
    }
    float deltaX, deltaY;

    deltaX = xPos - lastX;
    deltaY = yPos - lastY;

    lastX = xPos;
    lastY = yPos;

	mainCamera.ProcessMouseMovement(deltaTime * deltaX, deltaTime * deltaY);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	mainCamera.ProcessMouseScroll(yoffset);
}

// Is called whenever a key is pressed/released via GLFW
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}


unsigned int LoadImageToGPU(const char* filename) {
	unsigned int TexBuffer;
	glGenTextures(1, &TexBuffer);

	int width, height, nrComponents;
	unsigned char* data = SOIL_load_image(filename, &width, &height, &nrComponents, 0);
	if (data) {
		GLenum format;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA; //GL_SRGB;

		glBindTexture(GL_TEXTURE_2D, TexBuffer);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);// this fun must be first than behinds

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}
	else {
		std::cout << "Image load failed: " << filename << std::endl;
	}
	SOIL_free_image_data(data);
	glBindTexture(GL_TEXTURE_2D, 0);
	return TexBuffer;
}


float lerp(float a, float b, float f)
{
	return a + f * (b - a);
}

size_t DataToMap(vector<float>& data) {
	size_t n = static_cast<size_t>(sqrt(data.size()));
	if (n * n < data.size())
		n++;
	data.resize(n * n);
	return n;
}

#endif// ! _GLOBALDEFINES_H_