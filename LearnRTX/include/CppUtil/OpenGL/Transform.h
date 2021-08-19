#include<CppUtil/OpenGL/Model.h>

namespace CppUtil {
	namespace OpenGL {
		class Shader;
		class Transform {
		public:
			Transform() { this->isValid = false; }
			Transform(Interface* _obj, const glm::mat4& _transform = glm::mat4(1));
			void Draw(Shader& shader);
			bool IsValid()const { return this->isValid; }
			void SetTransform(const glm::mat4& _transform) { transform = _transform; }
			void SetWorldLocation(const glm::vec3& pos) { worldLocation = pos; }

			glm::mat4 GetTransform()const { return this->transform; }
			glm::vec3 GetWorldLocation()const { return this->worldLocation; }
			glm::vec3 GetWorldRotation()const { return this->rotate; }
			glm::vec3 GetScale()const { return this->scale; }

		private:
			glm::mat4 transform;
			glm::vec3 worldLocation;
			glm::vec3 rotate;
			glm::vec3 scale;

			Interface* object;
			bool isValid;
		};
	}
}