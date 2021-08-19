#include<CppUtil/OpenGL/Scene.h>
#include<CppUtil/OpenGL/Shader.h>
#include<CppUtil/OpenGL/Transform.h>

void CppUtil::OpenGL::SceneRA::Push(Transform* _obj)
{
	if (_obj->IsValid()) {
		this->objects.push_back(_obj);
	}
}

void CppUtil::OpenGL::SceneRA::Draw(Shader& shader) const
{
	for (int i = 0; i < this->objects.size(); i++) {
		objects[i]->Draw(shader);
	}
}