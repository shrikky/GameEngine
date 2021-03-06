#include "RigidbodyManager.h"
RigidbodyManager* RigidbodyManager::s_pInstance = 0;

RigidbodyManager::RigidbodyManager()
{
	workers[0] = thread(&RigidbodyManager::WaitOnTasks, this, 0);
	threadStatus[0] = true; // running = true
	workers[1] = thread(&RigidbodyManager::WaitOnTasks, this, 1);
	threadStatus[1] = true; // running = true
	workers[2] = thread(&RigidbodyManager::WaitOnTasks, this, 2);
	threadStatus[2] = true; // running = true
}

RigidbodyManager::~RigidbodyManager()
{
	processQuit = true;

	for (int i = 0; i < 3; i++)
	{
		while (threadStatus[i] == true);
		if (workers[i].joinable())
			workers[i].join();
	}
}
void RigidbodyManager::WaitOnTasks(int ThreadId)
{

	packaged_task<int()> task;
	while (!processQuit) {
		{
			unique_lock<mutex>locker(mu);
			while (task_q.empty())
				cond.wait(locker);

			task = move(task_q.front());
			task_q.pop();
		}
		task();

		if (task_q.empty())
			processQuit = true;
	}
	threadStatus[ThreadId] = false;
}

int RigidbodyManager::update(void* in, void* out)
{
	Rigidbody* obj = (Rigidbody*)in;

	obj->update(updateData.t, updateData.dt);
	return 1;
}


void RigidbodyManager::create(int id)
{
	Rigidbody *rigidbody = new Rigidbody;
	rigidbody->Rigidbody_Init(id);

	rigidbodyList.push_back(rigidbody);
	rigidbodyUpdateList.push_back(rigidbody);
}
void RigidbodyManager::updateList(float f_t, float f_dt){
	
	updateData.dt = f_dt;
	updateData.t = f_t;
	for (int i = 0; i <rigidbodyList.size(); i++) {
		packaged_task<int()> task(bind(&RigidbodyManager::update, this, rigidbodyList[i], nullptr));
		{
			lock_guard<mutex> locker(mu);
			task_q.push(move(task));
		}
		cond.notify_one();
	}
}
void RigidbodyManager::destroy()
{
	for (unsigned int i = 0; i < rigidbodyList.size(); ++i)
		delete rigidbodyList[i];

	for (unsigned int i = 0; i < rigidbodyUpdateList.size(); ++i)
		delete rigidbodyUpdateList[i];
}