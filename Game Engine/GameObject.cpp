#include "GameObject.h"
#include "TransformManager.h"

GameObject::GameObject()
{

}

GameObject::~GameObject()
{
}

void GameObject::create(int count)
{
	id = count;

	TransformManager::Instance()->create();
}

void GameObject::destroy()
{
	
}
