#include <vector>

#include "Rigidbody.h"
#include "TaskManager.h"
using namespace std;

struct sharedUpdateData
{
	float t, dt;
};

class RigidbodyManager {
public:
	RigidbodyManager();
	~RigidbodyManager();
	
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
	static void update(void* in, void* out);
	void updateList(float t, float dt);
	
	static TaskManager _taskManager;
	static vector<Rigidbody*> rigidbodyList;
private:
	static RigidbodyManager* s_pInstance;
	vector<Rigidbody*> rigidbodyUpdateList;

	static sharedUpdateData updateData;
};
