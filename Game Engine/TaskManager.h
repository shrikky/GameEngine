#pragma once
#include <iostream>
#include <thread>
#include <mutex>
#include <queue>
#include <condition_variable>


#define numberOfThreads 2

class TaskManager
{
private:
	bool threadRunning[numberOfThreads];
	bool processQuit;
	std::mutex p_queueAccess;
	std::queue<std::function<void()>> p_taskQueue;
	std::thread p_threads[numberOfThreads];
	std::condition_variable cond;

	typedef std::unique_lock<std::mutex> uniqueLock;

	void threadFunction(int threadNumber);
public:
	TaskManager();
	TaskManager(const TaskManager& other);
	~TaskManager();

	void start();
	void stopAllThreads();
	void addTask(void(*func)(void*, void*), void*, void*);
};
