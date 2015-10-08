#include "TransformManager.h"

TransformManager* TransformManager::s_pInstance = 0;

TransformManager::TransformManager()
{
}

TransformManager::~TransformManager()
{
}

void TransformManager::create()
{
	Transform *transform = new Transform;
	transform->create();

	transformList.push_back(transform);
	transformUpdateList.push_back(transform);
}

void TransformManager::destroy()
{
	for (int i = 0; i < transformList.size(); ++i)
		delete transformList[i];

	for (int i = 0; i < transformUpdateList.size(); ++i)
		delete transformUpdateList[i];
}