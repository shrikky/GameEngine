#pragma once

#include "Transform.h"

#include <vector>
#include<thread>
#include <string>
#include <fstream>
#include <mutex>
#include <condition_variable>
#include<future>
#include <queue>
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
	queue<packaged_task<int()>> task_q;
	mutex mu;
	condition_variable cond;
	bool processQuit = false;
	bool notified = false;
	int update(void* in);
	void WaitOnTasks();
	thread workers[3];
	void create(int id);
	void destroy();
	void updateList();
	vector<Transform*> transformList;
private:

	TransformManager();
	~TransformManager();
	static TransformManager* s_pInstance;
	
	vector<Transform*> transformUpdateList;
};

