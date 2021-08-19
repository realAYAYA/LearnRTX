#ifndef _DIELETRIC_H_
#define _DIELETRIC_H_

#include <CppUtil/RTX/Material.h>

namespace RTX {
	class Dielectric : public Material {
		MATERIAL_SETUP(Dielectric)
	public:
		Dielectric(float refractIndex, glm::vec3 attenuationConst = glm::vec3(0));
		
		// ����ֵΪ true ˵�����߼�������
		// ����ֵΪ false ˵�����߲��ٴ���
		//virtual bool Scatter(const HitRecord & rec) const;
		float GetRafractIndex() const { return refractIndex; }
	private:
		float refractIndex;
		glm::vec3 attenuationConst;
	};
}

#endif // !_DIELETRIC_H_
