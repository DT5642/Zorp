#include "GameObject.h"
#include "GameDefines.h"

GameObject::GameObject() : m_mapPosition{ 0, 0 }, m_priority{ PRIORITY_DEFAULT }
{
}

GameObject::GameObject(Point2D position) : m_mapPosition{ position }
{
}

GameObject::~GameObject()
{
}

Point2D GameObject::GetPosition()
{
	return m_mapPosition;
}

void GameObject::SetPosition(const Point2D& position)
{
	m_mapPosition = position;
}

bool GameObject::Compare(const GameObject* p1, const GameObject* p2)
{
	return p1->m_priority < p2->m_priority;
}