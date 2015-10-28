#include "RigidbodyManager.h"
RigidbodyManager* RigidbodyManager::s_pInstance = 0;

RigidbodyManager::RigidbodyManager()
{
}

RigidbodyManager::~RigidbodyManager()
{
}

void RigidbodyManager::create(int id)
{
	Rigidbody *rigidbody = new Rigidbody;
	rigidbody->Rigidbody_Init(id);

	rigidbodyList.push_back(rigidbody);
	rigidbodyUpdateList.push_back(rigidbody);
}

void RigidbodyManager::destroy()
{
	for (unsigned int i = 0; i < rigidbodyList.size(); ++i)
		delete rigidbodyList[i];

	for (unsigned int i = 0; i < rigidbodyUpdateList.size(); ++i)
		delete rigidbodyUpdateList[i];
}