#include "Skybox.h"
#include<iostream>
#include"SOIL.h"

Skybox::Skybox(std::vector<GLfloat>const& _vertices, std::vector<string>& _faces)
{
	vertices = _vertices;
	stepMesh();
	LoadCubemap(_faces);
}

void Skybox::stepMesh()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * vertices.size(), &vertices[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	//glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Skybox::LoadCubemap(std::vector<string>& faces)
{
	glGenTextures(1, &textureID);

	int width, height;

	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
	for (GLuint i = 0; i < faces.size(); i++)
	{
		unsigned char* image = SOIL_load_image(faces[i].c_str(), &width, &height, 0, SOIL_LOAD_RGB);// ???
		if (image) {
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
			SOIL_free_image_data(image);
		}
		else
		{
			std::cout << "Load Cubemap failed." << std::endl;
		}
	}
	// Because a cubemap is a texture like any other texture, we will also specify its wrapping and filtering methods:
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

void Skybox::Draw(Shader* shader, glm::mat4 view, glm::mat4 projection)
{
	glDepthFunc(GL_LEQUAL);  // Change depth function so depth test passes when values are equal to depth buffer's content
	shader->use();
	/* We want the skybox to be centered around the player so that no matter how far the player moves,
	|the skybox won't get any closer, giving the impression the surrounding environment is extremely large.
	|The current view matrix however transforms all the skybox's positions by rotating, scaling and translating them,
	|so if the player moves, the cubemap moves as well! We want to remove the translation part of the view matrix
	|so only rotation will affect the skybox's position vectors.
	*/
	glm::mat4 view2 = glm::mat4(glm::mat3(view));	// Remove any translation component of the view matrix
	shader->setMat4("view", view2);
	shader->setMat4("projection", projection);
	//glUniformMatrix4fv(glGetUniformLocation(shader->GetID(), "view"), 1, GL_FALSE, glm::value_ptr(view2));
	//glUniformMatrix4fv(glGetUniformLocation(shader->GetID(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));
	// skybox cube
	glBindVertexArray(VAO);
	glActiveTexture(GL_TEXTURE0);
	glUniform1i(glGetUniformLocation(shader->GetID(), "skybox"), 0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, GettextureID());
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
	glDepthFunc(GL_LESS); // Set depth function back to default
}