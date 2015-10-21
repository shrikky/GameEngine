#pragma once

#include <vector>
#include <string>

using namespace std;

class GameObject
{
public:
	GameObject();
	~GameObject();

	void create(int count);
	void destroy();

private:
	int id;
};


