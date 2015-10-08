#include "GameObject.h"
#include "TransformManager.h"
#include "ModelManager.h"

GameObject::GameObject()
{

}

GameObject::~GameObject()
{
}

void GameObject::create(int count, string type)
{
	id = count;

	TransformManager::Instance()->create();
}

void GameObject::destroy()
{
	
}
