#pragma once

#include "Transform.h"

#include <vector>

using namespace std;

class TransformManager
{
public:

	static TransformManager* Instance()
	{
		if (s_pInstance == 0)
		{
			s_pInstance = new TransformManager();
			return s_pInstance;
		}

		return s_pInstance;
	}

	void create(int id);
	void destroy();
	vector<Transform*> transformList;
private:

	TransformManager();
	~TransformManager();
	static TransformManager* s_pInstance;
	
	vector<Transform*> transformUpdateList;
};

