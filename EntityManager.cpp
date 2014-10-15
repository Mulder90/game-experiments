#include "EntityManager.h"

using namespace std;

void EntityManager::clear()
{
	m_entities.clear();
	m_groupEntities.clear();
}

void EntityManager::refresh()
{
	for (auto& pair : m_groupEntities)
	{
		auto& vec(pair.second);
		vec.erase(
			remove_if(begin(vec), end(vec),
			[](Entity* entity) { return !entity->isAlive(); }),
			end(vec));
	}

	m_entities.erase(
		remove_if(begin(m_entities), end(m_entities),
		[](const unique_ptr<Entity>& entity) { return !entity->isAlive(); }),
		end(m_entities));
}

void EntityManager::update(float deltaTime)
{
	for (auto& entity : m_entities)
	{
		entity->update(deltaTime);
	}
}

void EntityManager::draw(sf::RenderWindow& window)
{
	for (auto& entity : m_entities)
	{
		entity->draw(window);
	}
}