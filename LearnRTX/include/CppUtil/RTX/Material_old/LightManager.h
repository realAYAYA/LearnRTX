#pragma once
#include<vector>

using std::vector;

class LightDirectional;
class LightPoint;
class LightSpot;
class Light;

class LightManager
{
public:
	LightManager() {};

	void CreateDirectionalLight(){};
	void CreatePointLight() {};
	void CreateSpotLight() {};

	vector<LightPoint*> PointLightPool;
	vector<LightSpot*> SpotLightPool;
	vector<LightDirectional*> DirectionalLightPool;
};