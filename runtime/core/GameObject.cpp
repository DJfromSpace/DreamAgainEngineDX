/* Author: DJfromSpace (Dillon E Jones) */
#include "GameObject.h"

GameObject::GameObject() : id(0), name("GameObject"), active(true)
{
}

GameObject::GameObject(Id objectId, std::string objectName, bool isActive)
	: id(objectId), name(std::move(objectName)), active(isActive)
{
}

GameObject::~GameObject()
{
}

GameObject::Id GameObject::GetId() const
{
	return id;
}

const std::string& GameObject::GetName() const
{
	return name;
}

bool GameObject::IsActive() const
{
	return active;
}

void GameObject::SetName(const std::string& objectName)
{
	name = objectName;
}

void GameObject::SetActive(bool isActive)
{
	active = isActive;
}
