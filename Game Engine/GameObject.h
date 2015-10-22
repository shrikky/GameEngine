#pragma once

#include "Model.h"

#include <vector>
#include <string>

using namespace std;

class GameObject
{
public:
	GameObject();
	~GameObject();

	void create(int count, string type);
	void destroy();

private:
	int id;
	Model model;
};


