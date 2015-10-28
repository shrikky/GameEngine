#include "TransformManager.h"

TransformManager* TransformManager::s_pInstance = 0;

TransformManager::TransformManager()
{
}

TransformManager::~TransformManager()
{
}

void TransformManager::create(int id)
{
	Transform *transform = new Transform;
	transform->create(id);

	transformList.push_back(transform);
	transformUpdateList.push_back(transform);
}

void TransformManager::destroy()
{
	for (unsigned int i = 0; i < transformList.size(); ++i)
		delete transformList[i];

	for (unsigned int i = 0; i < transformUpdateList.size(); ++i)
		delete transformUpdateList[i];
}