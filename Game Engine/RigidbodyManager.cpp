#include "RigidbodyManager.h"
RigidbodyManager* RigidbodyManager::s_pInstance = 0;

RigidbodyManager::RigidbodyManager()
{
	_taskManager.start();
}

RigidbodyManager::~RigidbodyManager()
{
}

void RigidbodyManager::update(void* in, void* out)
{
	Rigidbody* obj = (Rigidbody*)in;

	obj->update(updateData.t, updateData.dt);
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
		_taskManager.addTask(RigidbodyManager::update,&rigidbodyList[i], nullptr);
	}
}
void RigidbodyManager::destroy()
{
	for (unsigned int i = 0; i < rigidbodyList.size(); ++i)
		delete rigidbodyList[i];

	for (unsigned int i = 0; i < rigidbodyUpdateList.size(); ++i)
		delete rigidbodyUpdateList[i];
}