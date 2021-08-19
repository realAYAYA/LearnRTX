#ifndef _LAMBERTIAN_H_
#define _LAMBERTIAN_H_

#include <CppUtil/RTX/Material.h>

#include <glm/glm.hpp>

namespace RTX {
	class Texture;

	class Lambertian : public Material {
		MATERIAL_SETUP(Lambertian)
	public:
		Lambertian(float r, float g, float b);
		Lambertian(const glm::rgb & albedo);
		Lambertian(CppUtil::Basic::CPtr<Texture> albedo);

		// ����ֵΪ true ˵�����߼�������
		// ����ֵΪ false ˵�����߲��ٴ���
		//virtual bool Scatter(const HitRecord & rec) const;
		
		const CppUtil::Basic::CPtr<Texture> GetTexture() const { return albedo; }
	protected:
		CppUtil::Basic::CPtr<Texture> albedo;
	};
}

#endif // !_LAMBERTIAN_H_
