#ifndef _ISOTROPIC_H_
#define _ISOTROPIC_H_

#include <CppUtil/RTX/Material.h>

namespace RTX {
	class Texture;

	class Isotropic : public Material{
		MATERIAL_SETUP(Isotropic)
	public:
		Isotropic(const glm::rgb & color);

		// ����ֵΪ true ˵�����߼�������
		// ����ֵΪ false ˵�����߲��ٴ���
		//virtual bool Scatter(const HitRecord & rec) const;
		const CppUtil::Basic::CPtr<Texture> GetTexture() const { return tex; }
	protected:
		CppUtil::Basic::CPtr<Texture> tex;
	};
}

#endif // !_ISOTROPIC_H_
