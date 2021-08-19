#ifndef _MATH_H_
#define _MATH_H_

#include <glm/glm.hpp>
#include <vector>

namespace CppUtil {
	namespace Basic {
		namespace Math {
			const float EPSILON = 10e-6f;
			const float PI = 3.1415926f;

			glm::vec2 RandInCircle();

			glm::vec3 RandInSphere();

			// [-0x7FFFFFFFF, 0x7FFFFFFF]
			int Rand_I();

			// [0, 0xFFFFFFFF]
			unsigned int Rand_UI();

			// [0.0f, 1.0f]
			float Rand_F();

			// [0.0, 1.0]
			double Rand_D();

			// dor( (0.299, 0.587, 0.114), color )
			float Gray(const glm::vec3 & color);

			// ����
			// rationNiNt ������֮�� == Ni / Nt
			//     Ni Ϊ ����������ڽ��ʵ�������
			//     Nt Ϊ ����������ڽ��ʵ�������
			bool Refract(const glm::vec3 & viewDir, const glm::vec3 & normal, float ratioNiNt, glm::vec3 & refractDir);

			// ������
			// viewDir Ϊ ���߷���(����㵽�ӵ�ķ���)
			// halfway Ϊ ���߷�������߷����ƽ��
			// rationNtNi ������֮�� == Nt / Ni
			//     Ni Ϊ ����������ڽ��ʵ�������
			//     Nt Ϊ ����������ڽ��ʵ�������
			float FresnelSchlick(const glm::vec3 & viewDir, const glm::vec3 & halfway, float ratioNtNi);

			template <typename T>
			T Mean(const std::vector<T> & data);

			template<typename T>
			T Variance(const std::vector<T> & data);

			// �������Ԫ�ص�λ��, ��λ�õĸ���ƽ��
			template<typename T>
			void Permute(std::vector<T> data);

			// ����ά����ת��Ϊ��������
			glm::vec2 Sphere2UV(const glm::vec3 & normal);

			// ����ֵ: (alpah, beta, gamma, t)
			// e + t * d == alpha * a + beta * b + gamma * c
			// alpha + beta + gammma == 1
			// ���ƽ��, ���� (0, 0, 0, 0)
			glm::vec4 Intersect_RayTri(const glm::vec3 & e, const glm::vec3 & d, const glm::vec3 & a, const glm::vec3 & b, const glm::vec3 & c);

			template<typename T>
			T min(const std::vector<T> & val);

			template<typename T>
			T max(const std::vector<T> & val);

			//--------------����Ϊģ���ʵ��----------------
			//--------------����Ϊģ���ʵ��----------------
			//--------------����Ϊģ���ʵ��----------------
			//--------------����Ϊģ���ʵ��----------------
			//--------------����Ϊģ���ʵ��----------------
			//--------------����Ϊģ���ʵ��----------------
			//--------------����Ϊģ���ʵ��----------------
			template <typename T>
			T Mean(const std::vector<T> & data) {
				if (data.size() == 0)
					return static_cast<T>(0);

				T sum = static_cast<T>(0);
				for (size_t i = 0; i < data.size(); i++)
					sum += data[i];

				return sum / data.size();
			}

			template<typename T>
			T Variance(const std::vector<T> & data) {
				if (data.size() <= 1)
					return static_cast<T>(0);

				T mean = Mean(data);
				T sum = static_cast<T>(0);
				for (size_t i = 0; i < data.size(); i++)
					sum += pow(data[i] - mean, 2);

				return sum / (data.size() - 1);
			}

			template<typename T>
			void Permute(std::vector<T> data) {
				for (size_t i = data.size() - 1; i > 0; i--) {
					size_t target = Rand_UI() % i;
					std::swap(data[i], data[target]);
				}
			}

			template<typename T>
			T min(const std::vector<T> & val) {
				if (val.empty())
					return static_cast<T>(0);

				T rst = val[0];
				for (size_t i = 1; i < val.size(); i++)
					rst = glm::min(rst, val[i]);

				return rst;
			}

			template<typename T>
			T max(const std::vector<T> & val) {
				if (val.empty())
					return static_cast<T>(0);

				T rst = val[0];
				for (size_t i = 1; i < val.size(); i++)
					rst = glm::max(rst, val[i]);

				return rst;
			}
		}
	}
}

#endif // !_MATH_H_
