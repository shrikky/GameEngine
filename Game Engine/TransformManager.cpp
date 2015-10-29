#include "TransformManager.h"

TransformManager* TransformManager::s_pInstance = 0;

TransformManager::TransformManager()
{
	workers[0] = thread(&TransformManager::WaitOnTasks, this);
	workers[1] = thread(&TransformManager::WaitOnTasks, this);
	workers[2] = thread(&TransformManager::WaitOnTasks, this);
}

TransformManager::~TransformManager()
{
}
void TransformManager::WaitOnTasks()
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
}

void TransformManager::create(int id)
{
	Transform *transform = new Transform;
	transform->create(id);

	transformList.push_back(transform);
	transformUpdateList.push_back(transform);
}
int TransformManager::update(void* in)
{
	Transform* obj = (Transform*)in;

	obj->update();
	return 1;
}
void TransformManager::updateList(){

	for (int i = 0; i <transformList.size(); i++) {
		packaged_task<int()> task(bind(&TransformManager::update, this, transformList[i]));
		{
			lock_guard<mutex> locker(mu);
			task_q.push(move(task));
		}
		cond.notify_one();
	}
}

void TransformManager::destroy()
{
	for (unsigned int i = 0; i < transformList.size(); ++i)
		delete transformList[i];

	for (unsigned int i = 0; i < transformUpdateList.size(); ++i)
		delete transformUpdateList[i];
}