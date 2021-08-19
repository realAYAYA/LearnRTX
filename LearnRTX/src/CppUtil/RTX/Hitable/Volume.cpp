#include <CppUtil/RTX/Volume.h>

//#include <CppUtil/RTX/Ray.h>

#include <CppUtil/Basic/Math.h>

using namespace RTX;
using namespace CppUtil::Basic;
using namespace glm;

Volume::Volume(Hitable::CPtr boundary, float density, Material::CPtr material)
	: Hitable(material), density(density), boundary(boundary) { }

//HitRst Volume::RayIn(CppUtil::Basic::Ptr<Ray> & ray) const {
//	if (boundary == NULL)
//		return HitRst::InValid;
//
//	float originTMax = ray->GetTMax();
//
//	auto boundaryHitRst = boundary->RayIn(ray);
//	if (!boundaryHitRst.hit)
//		return HitRst::InValid;
//
//	auto reverseRay = ToPtr(new Ray(ray->At(Ray::tMin*1.5f), - ray->GetDir()));
//	auto reverseHitRst = boundary->RayIn(reverseRay);
//	
//	float t0;
//	float tMaxFromT0;
//	if (reverseHitRst.hit) {
//		// �������ײ�����߽�, ˵���������ڲ�, ���ʱ����ڲ������Ϊ �������
//		// ��ʱ�Ը�����ײ�������Ϊǰ�ߵ� boundaryHitRst
//		t0 = 0;
//		tMaxFromT0 = boundaryHitRst.record.ray->GetTMax();
//		//t0HitRst = boundaryHitRst;
//	}
//	else {
//		// ����˵���������ⲿ, ���ʱ����ڲ������Ϊ ����ײ����
//		// ��ʱ�Ը�����ײ����������
//		t0 = boundaryHitRst.record.ray->GetTMax();
//		auto t0Ray = ToPtr(new Ray(ray->At(t0), ray->GetDir()));
//		HitRst t0HitRst = boundary->RayIn(t0Ray);
//
//		//̫��
//		if (!t0HitRst.hit) {
//			ray->SetTMax(originTMax);
//			return HitRst::InValid;
//		}
//
//		tMaxFromT0 = t0HitRst.record.ray->GetTMax();
//	}
//
//	float t1 = min(originTMax, t0 + tMaxFromT0);
//	//�˴��� len δ���� transform �� scale
//	float lenInVolume = (t1 - t0) * length(ray->GetDir());
//
//	// p = C * dL
//	// p(L) = lim(n->inf, (1 - CL/n)^n) = exp(-CL)
//	// L = -(1/C)ln(pL)
//	float hitLen = -(1.0f / density)*log(Math::Rand_F());
//
//	if (hitLen >= lenInVolume) {
//		ray->SetTMax(originTMax);
//		return HitRst::InValid;
//	}
//
//	float tFinal = t0 + hitLen / length(ray->GetDir());
//	ray->SetTMax(tFinal);
//
//	HitRst hitRst(true);
//	hitRst.record = HitRecord(ray, ray->At(tFinal));
//	hitRst.material = GetMat();
//	hitRst.isMatCoverable = IsMatCoverable();
//	return hitRst;
//}