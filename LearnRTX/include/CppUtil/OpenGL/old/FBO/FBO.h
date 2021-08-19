#pragma once
#include<gl/glew.h>

class Framebuffer
{
public:
	Framebuffer(const GLuint& width,const GLuint& height);
	void GenTextureAttachment(GLboolean depth, GLboolean stencil);
	void CreateRboAttachments();
	void bind();
	void unbind();

	GLuint GetTexture()const { return this->texture; }
	GLuint GetFbo()const { return this->fbo; }
	GLuint GetRbo()const { return this->rbo; }
private:
	GLuint fbo;
	GLuint texture;
	GLuint rbo;

	GLuint screenWidth, screenHeight;
};
