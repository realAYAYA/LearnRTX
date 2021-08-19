#ifndef _GLSCENE_H_
#define _GLSCENE_H_

#include<vector>
using std::vector;

namespace CppUtil {
	namespace OpenGL {
		//class Hitable;
		class Shader;
		class Transform;
		class SceneRA {
		public:
			SceneRA() { this->IsValid = true; }
			
			void Draw(Shader& shader)const;

			void Push(Transform* _obj);

		private:
			vector<Transform*> objects;

			bool IsValid;
		};
	}
}

#endif// ! _GLSCENE_H_