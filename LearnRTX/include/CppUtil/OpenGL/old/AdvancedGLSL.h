#pragma once
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include"GL/glew.h"

/* Advanced GLSL*/
GLuint CreateUniformBufferObject(int point, int size, int offset);
void BufferSubData(const GLuint& ubo, int offset, int size, const glm::mat4& object);




GLuint CreateUniformBufferObject(int point, int size, int offset) {
    GLuint ubo;
    glGenBuffers(1, &ubo);
    glBindBuffer(GL_UNIFORM_BUFFER, ubo);
    glBufferData(GL_UNIFORM_BUFFER, size, 0, GL_STATIC_DRAW);// Allocate memory but not fill it now
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
    // Define the range of the buffer that links to a uniform binding point
    glBindBufferRange(GL_UNIFORM_BUFFER, point, ubo, offset, size);

    return ubo;
}

void BufferSubData(const GLuint& ubo, int offset, int size, const glm::mat4& object) {
    glBindBuffer(GL_UNIFORM_BUFFER, ubo);
    glBufferSubData(GL_UNIFORM_BUFFER, offset, size, glm::value_ptr(object));
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}