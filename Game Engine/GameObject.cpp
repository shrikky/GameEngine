#include "GameObject.h"
#include "TransformManager.h"


GameObject::GameObject()
{

}

GameObject::~GameObject()
{
}

void GameObject::create(int count, string type)
{
	id = count;
	model(type);
	TransformManager::Instance()->create();
}

void GameObject::destroy()
{
	
}
