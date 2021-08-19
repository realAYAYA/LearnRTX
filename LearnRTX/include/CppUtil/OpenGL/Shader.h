#ifndef SHADER_H_
#define SHADER_H_
#include <CppUtil/Basic/File.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace CppUtil {
	namespace OpenGL {
		class Shader {
		public:
			// constructor generates the shader on the fly
			Shader(const std::string &  vertexPath, const std::string & fragmentPath, const std::string & geometryPath = "");

			size_t GetID() const;
			bool IsValid() const;

			// activate the shader
			bool Use() const;

			// utility uniform functions
			void SetBool(const char* name, bool value) const;
			void SetInt(const char* name, int value) const;
			void SetFloat(const char* name, float value) const;
			void SetFloats(const char* name, size_t n, const float * values) const;
			void SetVec2f(const char* name, float value0, float value1) const;
			void SetVec2f(const char* name, const glm::vec2 & v) const;
			void SetVec3f(const char* name, float value0, float value1, float value2) const;
			void SetVec3f(const char* name, const glm::vec3 & v) const;
			void SetVec3fs(const char* name, size_t n, const float * data) const;
			void SetVec4f(const char* name, float value0, float value1, float value2, float value3) const;
			void SetVec4f(const char* name, const glm::vec4 & v) const;
			void SetMat4f(const char* name, const float * matValue) const;
			void SetMat4f(const char* name, const glm::mat4& mat4) const;

			//------------
			void UniformBlockBind(const std::string &name, size_t bindPoint);
		private:
			static size_t curID;
			// utility function for checking shader compilation/linking errors.
			int CheckCompileErrors(size_t shader, std::string type);
			//------------
			size_t ID;
			bool valid;
		};
	}
}

#endif // !SHADER_H_
