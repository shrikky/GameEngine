#include <vector>

#include "Rigidbody.h"
#include<thread>
#include <string>
#include <fstream>
#include <mutex>
#include <condition_variable>
#include<future>
#include <queue>
using namespace std;

struct sharedUpdateData
{
	float t, dt;
};

class RigidbodyManager {
public:
	RigidbodyManager();
	~RigidbodyManager();
	queue<packaged_task<int()>> task_q;
	mutex mu;
	condition_variable cond;
	bool processQuit = false;
	bool notified = false;

	static RigidbodyManager* Instance()
	{
		if (s_pInstance == 0)
		{
			s_pInstance = new RigidbodyManager();
			return s_pInstance;
		}

		return s_pInstance;
	}

	void create(int id);
	void destroy();
	int update(void* in, void* out);
	void WaitOnTasks();
	thread workers[3];
	void updateList(float t, float dt);
	
	vector<Rigidbody*> rigidbodyList;
private:
	static RigidbodyManager* s_pInstance;
	vector<Rigidbody*> rigidbodyUpdateList;

	sharedUpdateData updateData;
};
