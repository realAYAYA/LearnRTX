#ifndef _GROUP_H_
#define _GROUP_H_

#include <CppUtil/RTX/Hitable.h>
#include <vector>

namespace RTX {
	class Group : public Hitable{
		HITABLE_SETUP(Group)
	public:
		Group(Material::CPtr material = NULL);

		// ���� true ˵�����߼�������
		// ���� false ˵�����ߴ�������
		//virtual HitRst RayIn(CppUtil::Basic::Ptr<Ray> & ray) const;
		inline void push_back(Hitable::CPtr hitable) { (*this) << hitable; }
		Group & operator <<(Hitable::CPtr hitable);
		virtual const AABB GetBoundingBox() const { return box; }
		const std::vector<Hitable::CPtr> & GetChildren() const { return children; }
	private:
		std::vector<Hitable::CPtr> children;
		AABB box;
	};
}
#endif //!_GROUP_H_

