#version 330 core
precision highp float;
layout (location = 0) out vec4 out_SumColor;// 将最终光照结果累加并存储
layout (location = 1) out vec4 out_RayData0;
layout (location = 2) out vec4 out_RayData1;
layout (location = 3) out vec4 out_RayData2;

in vec2 TexCoords;
out vec4 FragColor;

// 常量声明
const float PI = 3.1415926;
const float tMin = 0.001;
const float FLT_MAX = 99999999999999999999999999999999999999.0;
const float rayP = 50.0/51.0;// depth = p/(1-p) --> p = depth/(depth+1)

// 纹理采样
float At(sampler2D data, float idx);
void GetPack(float idx, out vec3 pack);
void GetPack(float idx, out vec4 pack);

// 光线定义及其相关函数与全局变量声明
struct Ray{
    vec3 origin;
    vec3 dir;
    highp vec3 color;
    float tMax;
};
float depth;
float RayTime;
float SampleNum;
void Ray_Load(out struct Ray ray);
void Ray_Store(struct Ray ray);
void Ray_Update(inout struct Ray ray, vec3 origin, vec3 dir, vec3 attenuation);
void Ray_Transform(inout struct Ray ray, mat4 transform);

// Camera定义及其相关函数与全局变量声明
struct Camera{// 依据像素和Camera数据进行透视投影随机生成光线，这样也不需要gBuffer
    vec3 pos;
    vec3 BL_Corner;
    vec3 horizontal;
    vec3 vertical;
    vec3 right;
    vec3 up;
    vec3 front;
    float lenR;
    float t0;
    float t1;
};
void Camera_GenRay(out struct Ray ray);

// 输入变量
uniform sampler2D gPosition;
uniform sampler2D PackData;

uniform sampler2D SumColor;// FBO's texture, we import these back for read
uniform sampler2D RayData0;
uniform sampler2D RayData1;
uniform sampler2D RayData2;

uniform float rdSeed[4];
uniform float clear;// 摄像机发生变换，清楚纹理缓存的标识,值为1即发生了变换
uniform float curLoop;

uniform struct Camera camera;
uniform mat4 oldViewProjectMat;

// Vertex
struct Vertex{
    vec3 pos;
    vec3 normal;
    vec2 uv;
};
struct Vertex Vertex_InValid = struct Vertex(vec3(0), vec3(0), vec2(0));
void Vertex_Load(float idx, out struct Vertex vert);
void Vertex_Interpolate(vec3 abg, struct Vertex A, struct Vertex B, struct Vertex C, out struct Vertex vert);
void Vertex_Transform(inout struct Vertex vert, mat4 transform);
void Vertex_Transform(inout struct Vertex vert, mat4 transform , mat3 normTfm);

// BRDF
bool Scatter_Material(inout struct Ray ray, struct Vertex vertex, float matIdx);
bool Scatter_Lambertian(inout struct Ray ray, struct Vertex vertex, float matIdx);
bool Scatter_Metal(inout struct Ray ray, struct Vertex vertex, float matIdx);
bool Scatter_Dielectric(inout struct Ray ray, struct Vertex vertex, float matIdx);
bool Scatter_Light(inout struct Ray ray, struct Vertex vertex, float matIdx);
bool Scatter_Isotropic(inout struct Ray ray, struct Vertex vertex, float matIdx);

// 随机数工具
float RandXY(float x, float y);// [0.0, 1.0)
float Rand();// [0.0, 1.0)
vec2 RandInSquare();
vec2 RandInCircle();
vec3 RandInSphere();
vec3 RandOnSphere();
int rdCnt = 0;


// Main------------------------------------------------------------------------------------------
void main()
{
    float idx=At(PackData,1);
    if(idx==4)
    {
        vec3 FragPos = texture(gPosition, TexCoords).rgb;
        FragColor = vec4(FragPos, 1.0f);
    }
}
// END-------------------------------------------------------------------------------------------

// CPP-------------------------------------------------------------------------------------------
void Ray_Load(out struct Ray ray){
	vec4 val[3];
	val[0] = texture(RayData0, TexCoords);
	ray.origin = val[0].xyz;
	ray.tMax = val[0].w;
	val[1] = texture(RayData1, TexCoords);
	ray.dir = val[1].xyz;
	RayTime = val[1].w;
	val[2] = texture(RayData2, TexCoords);
	ray.color = val[2].xyz;
	depth = val[2].w;

	if(clear == 1.0 || ray.tMax == 0){
		Camera_GenRay(ray);
		return;
	}
}

void Ray_Store(struct Ray ray){
	out_RayData0 = vec4(ray.origin, ray.tMax);
	out_RayData1 = vec4(ray.dir, RayTime);
	out_RayData2 = vec4(ray.color, depth);

	vec4 oldColor;
	if(clear==1.0){// 摄像机位置发生变化，颜色结果需要重新计算
		if(ray.tMax != 0){
			vec4 tmp = oldViewProjectMat * vec4(ray.origin, 1);// 将光线变换到摄像机视角
			vec2 texc = (tmp.xy / tmp.w + 1)/2;// 转换为采样坐标(0,1)
			texc.y = 1 - texc.y;// y轴逆置
			
			if(texc.x>0 && texc.x<1 && texc.y>0 && texc.y<1){// 如果坐标位置位于屏幕中
				oldColor = texture(SumColor, texc);
				if(oldColor.w != 0)
					oldColor /= oldColor.w / 4;
				else
					oldColor = vec4(0);
					
				vec2 offset = 1.0/textureSize(SumColor,0);// 设置偏移量，动态模糊
				vec4 c0 = texture(SumColor, texc+offset);
				if(c0.w != 0)
					c0 /= c0.w;
				else
					c0 = vec4(0);
				vec4 c1 = texture(SumColor, texc-offset);
				if(c1.w != 0)
					c1 /= c1.w;
				else
					c1 = vec4(0);
				oldColor += c0+c1;
				if(oldColor.w != 0)
					oldColor /= oldColor.w;
				else
					oldColor = vec4(0);
			}
			else
				oldColor = vec4(0);
		}else
			oldColor = vec4(0);
	}else// 摄像机位置和视角未发生变换，可以在前结果上继续收敛
		oldColor = texture(SumColor, TexCoords);
	vec4 newColor = ray.tMax == 0 ? vec4(ray.color, 1) : vec4(0);
	out_SumColor = oldColor + newColor;
}

void Ray_Transform(inout struct Ray ray, mat4 transform){
	ray.dir = mat3(transform) * ray.dir;
	vec4 originQ = transform * vec4(ray.origin, 1.0f);
	ray.origin = originQ.xyz / originQ.w;
}

void Camera_GenRay(out struct Ray ray){
    vec2 st = TexCoords + (RandInSquare()-0.5) / textureSize(SumColor, 0);
    vec2 rd = camera.lenR * RandInCircle();
    
    ray.origin = camera.pos + rd.x * camera.right + rd.y * camera.up;
    ray.dir = camera.BL_Corner + st.s * camera.horizontal + st.t * camera.vertical - ray.origin;
    ray.color = vec3(1);
    ray.tMax = FLT_MAX;
    RayTime = mix(camera.t0, camera.t1, Rand());
	depth = 0;
}

// 随机数实现，“有就能用”原则
float RandXY(float x, float y){
    return fract(cos(dot(vec2(x,y), vec2(12.9898, 4.1414))) * 43758.5453);
}

float Rand(){
    float a = RandXY(TexCoords.x, rdSeed[0]);
    float b = RandXY(rdSeed[1], TexCoords.y);
    float c = RandXY(rdCnt++, rdSeed[2]);
    float d = RandXY(rdSeed[3], a);
    float e = RandXY(b, c);
    float f = RandXY(d, e);
 
    return f;
}

vec2 RandInSquare(){
    return vec2(Rand(), Rand());
}

vec2 RandInCircle(){
    vec2 rst;
    do {
        rst = vec2(Rand(), Rand())*2.0f - 1.0f;
    } while (dot(rst, rst) >= 1.0);
    return rst;
}
 
vec3 RandInSphere(){
    vec3 rst;
    do {
        rst = vec3(Rand(), Rand(), Rand())*2.0f - 1.0f;
    } while (dot(rst, rst) >= 1.0);
    return rst;
}

vec3 RandOnSphere(){
	vec3 rst;
    do {
        rst = vec3(Rand(), Rand(), Rand())*2.0f - 1.0f;
    } while (dot(rst, rst) >= 1.0 || rst == vec3(0));
    return normalize(rst);
}

// Note:
// 1. ivec2 textureSize(sample2D tex,int lop) 该方法返回纹理贴图的ivec2(列,行)
// 2. float At(sampler2D data, float idx) 该方法的可以将纹理数据作为超长数组使用，原理如下：
// 所在行row = (数组下标/偏差)/列数
// 所在列(转换为纹理采样坐标(0,1)内)y = row/行数
// 所在行(转换为纹理采样坐标(0,1)内)x = (数组下标-所在行*列数+)/列数
// vec2 texCoords = vec2(x, y); 最后采样texture2D(data, texCoords)

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
