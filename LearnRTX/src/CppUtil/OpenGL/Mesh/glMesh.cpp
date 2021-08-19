#include<CppUtil/OpenGL/Mesh.h>
#include<CppUtil/OpenGL/Shader.h>
using CppUtil::OpenGL::Mesh;

Mesh::Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<TextureInfo> textures)
{
	this->vertices = vertices;
	this->indices = indices;
	this->textures = textures;

	setupMesh();
}

Mesh::~Mesh()
{
	//glDeleteVertexArrays(1, &VAO);
	//glDeleteBuffers(1, &VBO);
}

void Mesh::Draw(Shader& shader)
{
	for (unsigned int i = 0; i < textures.size(); i++) {
		glActiveTexture(GL_TEXTURE0 + i);// 选中贴图缓存区域（cpu）
		if (textures[i].type == "texture_diffuse")
		{
			shader.SetInt("texture_diffuse1", i);// 告诉shader使用的贴图缓存编号
		}
		else if (textures[i].type == "texture_specular") {
			shader.SetInt("texture_specular1", i);
		}
		else if (textures[i].type == "texture_normal") {
			shader.SetInt("material.normal", i);
		}
		else if (textures[i].type == "texture_height") {
			shader.SetInt("material.height", i);
		}
		glBindTexture(GL_TEXTURE_2D, textures[i].id);// 将贴图数据绑定到对应编号贴图缓存（cpu）
	}

	// Draw
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	glActiveTexture(GL_TEXTURE0);// 复位
}

//void Mesh::DrawArrays(Shader* shader, const glm::mat4& modelMat)
//{
//	shader->Use();
//
//	shader->SetMat4f("modelMat", modelMat);
//
//	glBindVertexArray(VAO);
//	if (textures.size()) {
//		glActiveTexture(GL_TEXTURE0);
//		glBindTexture(GL_TEXTURE_2D, textures[0].id);
//	}
//	glDrawArrays(GL_TRIANGLES, 0, EBO);
//	glBindVertexArray(0);
//}
//
//void Mesh::DrawElements(Shader* shader)
//{
//	shader->Use();
//	glBindVertexArray(VAO);
//	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
//	glBindVertexArray(0);
//}

void Mesh::setupMesh()
{
	// This has the advantage that when configuring vertex attribute pointers you only have to make those calls once
	// and whenever we want to draw the object, we can just bind the corresponding VAO.
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	unsigned int VBO, EBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), &vertices[0], GL_STATIC_DRAW);// GL_DYNAMIC_DRAW,GL_STREAM_DRAW

	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), &indices[0], GL_STATIC_DRAW);
	
	// 
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3 * sizeof(GL_FLOAT)));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(6 * sizeof(GL_FLOAT)));
	
	glBindVertexArray(0);
}

/*
|	About Function: glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(6 * sizeof(GL_FLOAT))):
|	The first parameter specifies which vertex attribute we want to configure. Remember that we specified the location of 
|the position vertex attribute in the vertex shader with layout (location = 0). This sets the location of the vertex attribute 
|to 0 and since we want to pass data to this vertex attribute, we pass in 0.
|	The next argument specifies the size of the vertex attribute. The vertex attribute is a vec3 so it is composed of 3 values.
|	The third argument specifies the type of the data which is GL_FLOAT (a vec* in GLSL consists of floating point values).
|	The next argument specifies if we want the data to be normalized. If we're inputting integer data types (int, byte) and 
|we've set this to GL_TRUE, the integer data is normalized to 0 (or -1 for signed data) and 1 when converted to float. 
|This is not relevant for us so we'll leave this at GL_FALSE.
|	The fifth argument is known as the stride and tells us the space between consecutive vertex attributes. Since the next set of 
|position data is located exactly 3 times the size of a float away we specify that value as the stride. Note that since we know 
|that the array is tightly packed (there is no space between the next vertex attribute value) we could've also specified the stride 
|as 0 to let OpenGL determine the stride (this only works when values are tightly packed). Whenever we have more vertex attributes 
|we have to carefully define the spacing between each vertex attribute but we'll get to see more examples of that later on.
|	The last parameter is of type void* and thus requires that weird cast. This is the offset of where the position data begins 
|in the buffer. Since the position data is at the start of the data array this value is just 0. We will explore this parameter 
|in more detail later on
*/

using CppUtil::OpenGL::SimpleMesh;

SimpleMesh::SimpleMesh(const GLfloat _vertices[], const int size, Type _type)
{
	this->type = _type;
	if (_type == ENUM_FORMAT_PNT) {// 正常构造
		for (size_t i = 0; i < size; i += 6) {
			glm::vec3 pos(_vertices[i], _vertices[i + 1], _vertices[i + 2]);
			glm::vec3 normal(_vertices[i + 3], _vertices[i + 4], _vertices[i + 5]);
			glm::vec2 texcoord(_vertices[i + 6], _vertices[i + 7]);
			Vertex v;
			v.Position = pos; v.Normal = normal; v.TexCoords = texcoord;
			vertices.push_back(v);
		}
		drawCount = size / 8;
	}
	else if (type == ENUM_FORMAT_PCT) {// 依据shader程序，对这种数组仅需要pos
		for (size_t i = 0; i < size; i += 8) {
			glm::vec3 pos(_vertices[i], _vertices[i + 1], _vertices[i + 2]);
			Vertex v;
			v.Position = pos;
			vertices.push_back(v);
			drawCount = size / 8;
		}
	}
	else if (_type == ENUM_FORMAT_P) {// 只有顶点数据
		for (size_t i = 0; i < size; i += 6) {
			glm::vec3 pos(_vertices[i], _vertices[i + 1], _vertices[i + 2]);
			Vertex v;
			v.Position = pos;
			vertices.push_back(v);
		}
		drawCount = size / 3;
	}
	else if (_type == ENUM_FORMAT_PN) {// 顶点数据和normal数据
		for (size_t i = 0; i < size; i += 6) {
			glm::vec3 pos(_vertices[i], _vertices[i + 1], _vertices[i + 2]);
			glm::vec3 normal(_vertices[i + 3], _vertices[i + 4], _vertices[i + 5]);
			Vertex v;
			v.Position = pos; v.Normal = normal;
			vertices.push_back(v);
		}
		drawCount = size / 6;
	}
	else if (_type == ENUM_FORMAT_PT) {// 顶点数据和纹理坐标
		for (size_t i = 0; i < size; i += 5) {
			glm::vec3 pos(_vertices[i], _vertices[i + 1], _vertices[i + 2]);
			glm::vec2 texcoord(_vertices[i + 3], _vertices[i + 4]);
			Vertex v;
			v.Position = pos; v.TexCoords = texcoord;
			vertices.push_back(v);
		}
		drawCount = size / 5;
	}
	setupMesh();
}

CppUtil::OpenGL::SimpleMesh::SimpleMesh(const GLfloat _vertices[], const int size1, Type _type, const GLuint _indices[], const int size2)
{
	this->type = _type;
	if (type == ENUM_FORMAT_PNT) {
		for (size_t i = 0; i < size1; i += 6) {
			glm::vec3 pos(_vertices[i], _vertices[i + 1], _vertices[i + 2]);
			glm::vec3 normal(_vertices[i + 3], _vertices[i + 4], _vertices[i + 5]);
			glm::vec2 texcoord(_vertices[i + 6], _vertices[i + 7]);
			Vertex v;
			v.Position = pos; v.Normal = normal; v.TexCoords = texcoord;
			vertices.push_back(v);
		}
	}
	else if (type == ENUM_FORMAT_P) {
		for (size_t i = 0; i < size1; i += 6) {
			glm::vec3 pos(_vertices[i], _vertices[i + 1], _vertices[i + 2]);
			Vertex v;
			v.Position = pos;
			vertices.push_back(v);
		}
	}
	else if (type == ENUM_FORMAT_PN) {
		for (size_t i = 0; i < size1; i += 6) {
			glm::vec3 pos(_vertices[i], _vertices[i + 1], _vertices[i + 2]);
			glm::vec3 normal(_vertices[i + 3], _vertices[i + 4], _vertices[i + 5]);
			Vertex v;
			v.Position = pos; v.Normal = normal;
			vertices.push_back(v);
		}
	}
	else if (_type == ENUM_FORMAT_PT) {
		for (size_t i = 0; i < size1; i += 5) {
			glm::vec3 pos(_vertices[i], _vertices[i + 1], _vertices[i + 2]);
			glm::vec2 texcoord(_vertices[i + 3], _vertices[i + 4]);
			Vertex v;
			v.Position = pos; v.TexCoords = texcoord;
			vertices.push_back(v);
		}
	}
	else if (type == ENUM_FORMAT_PCT) {
		for (size_t i = 0; i < size1; i += 8) {
			glm::vec3 pos(_vertices[i], _vertices[i + 1], _vertices[i + 2]);
			Vertex v;
			v.Position = pos;
			vertices.push_back(v);
		}
	}
	for (size_t i = 0; i < size2; i++) {
		this->indices.push_back(_indices[i]);
	}
	setupMesh();
}

void CppUtil::OpenGL::SimpleMesh::Draw(Shader& shader)
{
	for (unsigned int i = 0; i < textures.size(); i++) {
		glActiveTexture(GL_TEXTURE0 + i);// 选中贴图缓存区域（cpu）
		if (textures[i].type == "texture_diffuse")
		{
			shader.SetInt("texture_diffuse1", i);// 告诉shader使用的贴图缓存编号
		}
		else if (textures[i].type == "texture_specular") {
			shader.SetInt("texture_specular1", i);
		}
		else if (textures[i].type == "texture_normal") {
			shader.SetInt("material.normal", i);
		}
		else if (textures[i].type == "texture_height") {
			shader.SetInt("material.height", i);
		}
		glBindTexture(GL_TEXTURE_2D, textures[i].id);// 将贴图数据绑定到对应编号贴图缓存（cpu）
	}

	// Draw
	glBindVertexArray(VAO);
	if (this->indices.size() > 0) {
		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	}
	else
	{
		glDrawArrays(GL_TRIANGLES, 0, drawCount);
	}
	glBindVertexArray(0);
	glActiveTexture(GL_TEXTURE0);// 纹理复位
}

void CppUtil::OpenGL::SimpleMesh::setupMesh()
{
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	unsigned int VBO, EBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), &vertices[0], GL_STATIC_DRAW);// GL_DYNAMIC_DRAW,GL_STREAM_DRAW

	if (this->indices.size() > 0) {
		glGenBuffers(1, &EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), &indices[0], GL_STATIC_DRAW);
	}

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);// pos
	if (this->type == ENUM_FORMAT_PNT) {
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3 * sizeof(GL_FLOAT)));// normal
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(6 * sizeof(GL_FLOAT)));// texcoord
	}
	if (this->type == ENUM_FORMAT_PT) {
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(6 * sizeof(GL_FLOAT)));
	}
	glBindVertexArray(0);
}
