#include "TaskManager.h"

TaskManager::TaskManager()
{
	processQuit = false;
}

TaskManager::TaskManager(const TaskManager &other)
{
	processQuit = false;
	for (int i = 0; i < numberOfThreads; i++)
		threadRunning[i] = false;
}

void TaskManager::stopAllThreads()
{
	processQuit = true;
	for (int i = 0; i < numberOfThreads; i++)
	{
		while (threadRunning[i] == true);
		if (p_threads[i].joinable())
			p_threads[i].join();
	}
}

TaskManager::~TaskManager()
{
	processQuit = true;

	for (int i = 0; i < numberOfThreads; i++)
	{
		while (threadRunning[i] == true);
		if (p_threads[i].joinable())
			p_threads[i].join();
	}
}

void TaskManager::start()
{
	for (int i = 0; i < numberOfThreads; i++)
	{
		p_threads[i] = std::thread(&TaskManager::threadFunction, this, i);
		threadRunning[i] = true;
	}
}

void TaskManager::addTask(void(*func)(void*, void*), void* in, void* out)
{

	uniqueLock locker(p_queueAccess);
	p_taskQueue.push(std::bind(func, in, out));
	locker.unlock();
	cond.notify_all();
}

void TaskManager::threadFunction(int threadNumber)
{
	std::function<void()> currentTask;
	while (!processQuit)
	{
		uniqueLock locker(p_queueAccess);

		while (p_taskQueue.empty())			// to avoid spurious wake
			cond.wait(locker);
		//{
		//locker.lock();
		currentTask = (p_taskQueue.front());
		p_taskQueue.pop();
		locker.unlock();

		//std::cout << "From Thread " << threadNumber;
		currentTask();					// Execute the task
		//}
		//cond.wait(locker);

	}

	threadRunning[threadNumber] = false;
}
