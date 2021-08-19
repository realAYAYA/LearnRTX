#ifndef _FBO_H_
#define _FBO_H_

#include <CppUtil/OpenGL/Texture.h>

#include <vector>

namespace CppUtil {
	namespace OpenGL {
		class FBO {
		public:
			enum ENUM_TYPE
			{
				ENUM_TYPE_BASIC,
				ENUM_TYPE_RGBF1_DEPTH,
				ENUM_TYPE_RGBF2_DEPTH,
				ENUM_TYPE_RGBF3_DEPTH,
				ENUM_TYPE_MSAA,
				ENUM_TYPE_COLOR,
				ENUM_TYPE_RED,
				ENUM_TYPE_COLOR_FLOAT,
				ENUM_TYPE_DEPTH,
				ENUM_TYPE_CUBE_DEPTH,
				ENUM_TYPE_GBUFFER,
				ENUM_TYPE_RAYTRACING,
				ENUM_TYPE_RTX,
			};
			enum ENUM_PASS_TYPE {
				ENUM_PASS_COLOR,
				ENUM_PASS_DEPTH,
			};

			FBO(size_t width, size_t height, ENUM_TYPE type = ENUM_TYPE_BASIC);
			bool PassTo(const FBO & fbo, ENUM_PASS_TYPE passType = ENUM_PASS_COLOR) const;
			bool PassTo(size_t fboID, size_t width, size_t height, ENUM_PASS_TYPE passType = ENUM_PASS_COLOR) const;

			bool Use() const;
			static void UseDefault();
			static size_t DefaultBuffer;
			size_t GetID() const;
			const Texture & GetColorTexture(size_t idx = 0) const;
			const Texture & GetDepthTexture() const;
			bool IsValid() const;
		private:
			bool GenFBO_BASIC(size_t width, size_t height);
			bool GenFBO_RGBF_DEPTH(size_t width, size_t height, size_t colorBufferNum = 1);
			bool GenFBO_MSAA(size_t width, size_t height);
			bool GenFBO_COLOR(size_t width, size_t height, bool isFloat = false);
			bool GenFBO_RED(size_t width, size_t height);
			bool GenFBO_DEPTH(size_t width, size_t height);
			bool GenFBO_CUBE_DEPTH(size_t width, size_t height);
			bool GenFBO_GBUFFER(size_t width, size_t height);// deferredshading
			bool GenFBO_RAYTRACING(size_t width, size_t height);
			bool GenFBO_RTX(size_t width, size_t height);

			bool IsComplete() const;
			static size_t PassType2GL(ENUM_PASS_TYPE passType);

			FBO & operator=(const FBO & fbo) = delete;

			ENUM_TYPE type;
			size_t ID;
			std::vector<Texture> colorTextures;
			Texture depthTexture;
			size_t width;
			size_t height;
			bool isValid;
		};
	}
}
#endif // !_FBO_H_

/*
* 帧缓冲（FBO）的工作原理是：
* FBO绑定若干纹理贴图（Texture）用作颜色缓冲（离屏成像），及一个渲染缓冲对象（RBO）用于进行深度或模板检测（或二者都有）
* OpenGL初始就自带一个FBO，编号为0，开发者则可以自己创建并自定义
* 渲染时：
* 将创建的FBO进行bind，然后正常渲染，则GPU会对当前用户创建的FBO进行深度或模板检测，并将渲染的结果缓存到Texture上
* 因此最后显示的时候只需要单独设置一个VAO（屏幕空间），然后将Texture显示在上面
* 优点：
* 犹豫离屏成像结果已经缓存进一个Texture中，因此用户可以在此基础上进行操作（比如进行后期处理）
* 只需要将FBO的Texture成员载入到另外的shader程序中即可
*/