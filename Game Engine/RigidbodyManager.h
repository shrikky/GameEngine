#include <vector>

#include "Rigidbody.h"

using namespace std;

class RigidbodyManager {
public:
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
	vector<Rigidbody*> rigidbodyList;
private:

	RigidbodyManager();
	~RigidbodyManager();
	static RigidbodyManager* s_pInstance;

	vector<Rigidbody*> rigidbodyUpdateList;
};
