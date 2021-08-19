#pragma once
#include<vector>
#include<map>

using std::vector;
using std::map;

class Model;

class ModelManager
{
public:

	void push_back(Model* obj);
	int size()const { return this->objects.size(); }

	//void remove();

	vector<Model*> objects;

};

