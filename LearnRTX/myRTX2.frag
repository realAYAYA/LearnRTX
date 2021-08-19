#version 330 core
precision highp float;
out vec4 FragColor;
layout (location = 0) out vec4 out_SumColor;// 将最终光照结果累加并存储

struct Ray{
    vec3 origin;
    vec3 dir;
    highp vec3 color;
    float tMax;
};

// 此次生成光线的方式为：根据Camera的pos和gBuffer中的pos位置来生成光线，所以Camera的数据少很多
struct Camera{
    vec3 pos;
    float t0;
    float t1;
};
void Camera_GenRay(out struct Ray ray);

in vec2 TexCoords;

// The lighting pass shader accepts 3 uniform textures that represent the G-buffer
// and hold all the data we've stored in the geometry pass.
uniform sampler2D gPosition;

uniform sampler2D PackData;

float At(sampler2D data, float idx);
void GetPack(float idx, out vec3 pack);
void GetPack(float idx, out vec4 pack);

void main()
{
    float idx=At(PackData,1);
    if(idx==4)
    {
        vec3 FragPos = texture(gPosition, TexCoords).rgb;
        FragColor = vec4(FragPos, 1.0f);
    }
}

float At(sampler2D data, float idx){
	float row = (idx+0.5)/textureSize(data, 0).x;
	float y = (int(row)+0.5)/textureSize(data, 0).y;
	float x = (idx + 0.5 - int(row) * textureSize(data, 0).x)/textureSize(data, 0).x;
    vec2 texCoords = vec2(x, y);
    return texture2D(data, texCoords).x;
}

void GetPack(float idx, out vec4 pack){
	float row = (idx+0.5)/textureSize(PackData, 0).x;
	float y = (int(row)+0.5)/textureSize(PackData, 0).y;
	float x = (idx + 0.5 - int(row) * textureSize(PackData, 0).x)/textureSize(PackData, 0).x;
    vec2 texCoords = vec2(x, y);
	pack = texture2D(PackData, texCoords);
}

void GetPack(float idx, out vec3 pack){
	float row = (idx+0.5)/textureSize(PackData, 0).x;
	float y = (int(row)+0.5)/textureSize(PackData, 0).y;
	float x = (idx + 0.5 - int(row) * textureSize(PackData, 0).x)/textureSize(PackData, 0).x;
    vec2 texCoords = vec2(x, y);
	pack = texture2D(PackData, texCoords).xyz;
}

// Note:
// 1. ivec2 textureSize(sample2D tex,int lop) 该方法返回纹理贴图的ivec2(列,行)
// 2. float At(sampler2D data, float idx) 该方法的可以将纹理数据作为超长数组使用，原理如下：
// 所在行row = (数组下标/偏差)/列数
// 所在列(转换为纹理采样坐标(0,1)内)y = row/行数
// 所在行(转换为纹理采样坐标(0,1)内)x = (数组下标-所在行*列数+)/列数
// vec2 texCoords = vec2(x, y); 最后采样texture2D(data, texCoords)