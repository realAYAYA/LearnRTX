#pragma once
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include<string>

using std::string;
class Shader
{
public:
	Shader(const char* vertexPath, const char* fragmentPath, const char* geometryPath = nullptr);
	unsigned int GetID()const { return this->ID; }

	enum Slot {
		DIFFUSE,
		SPECULAR
	};

	void use();

	void UniformBlockBinding(const char* name, int slot);
	// You can only deliver variables after use()!
	void setBool(const char* name, bool value) const;
	void setInt(const char* paramNameString, int slot) const;
	void setFloat(const char* paramNameString, float param) const;
	void setVec2(const char* paramNameString, const glm::vec2& value) const;
	void setVec2(const char* paramNameString, float x, float y) const;
	void setVec3(const char* paramNameString, const glm::vec3& param)const;
	void setVec3(const char* paramNameString, float x, float y, float z) const;
	void setVec4(const char* paramNameString, const glm::vec4& value) const;
	void setVec4(const char* paramNameString, float x, float y, float z, float w);
	void setMat2(const char* paramNameString, const glm::mat2& mat) const;
	void setMat3(const char* paramNameString, const glm::mat3& mat) const;
	void setMat4(const char* paramNameString, const glm::mat4& param)const;
private:
	unsigned int ID;		//Shader Program ID
	// 
	void checkCompileErrors(unsigned int ID,std::string type);
};