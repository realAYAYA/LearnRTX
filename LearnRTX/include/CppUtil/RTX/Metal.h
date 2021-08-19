#ifndef _METAL_H_
#define _METAL_H_

#include <CppUtil/RTX/Material.h>

namespace RTX {
	class Texture;

	class Metal : public Material{
		MATERIAL_SETUP(Metal)
	public:
		Metal(float r, float g, float b, float fuzz = 0.0f);
		Metal(const glm::rgb & specular, float fuzz = 0.0f);
		Metal(CppUtil::Basic::CPtr<Texture> specular, float fuzz = 0.0f);

		// ����ֵΪ true ˵�����߼�������
		// ����ֵΪ false ˵�����߲��ٴ���
		//virtual bool Scatter(const HitRecord & rec) const;

		const CppUtil::Basic::CPtr<Texture> GetTexture() const { return specular; }
		float GetFuzz() const { return fuzz; }
	protected:
		const CppUtil::Basic::CPtr<Texture> specular;
		float fuzz;
	};
}

#endif // !_METAL_H_
