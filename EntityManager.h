#pragma once

#include <vector>
#include <memory>
#include <map>
#include <typeinfo>

#include "Entity.hpp"

class EntityManager
{
public:
	template<typename T, typename... TArgs>
	T& create(TArgs&&... args)
	{
		static_assert(std::is_base_of<Entity, T>::value, "'T' must be derived from 'Entity'");
		auto uPtr(std::make_unique<T>(std::forward<TArgs>(args)...));
		auto ptr(uPtr.get());
		m_groupEntities[typeid(T).hash_code()].emplace_back(ptr);
		m_entities.emplace_back(move(uPtr));
		return *ptr;
	}

	template<typename T>
	std::vector<Entity*>& getAll()
	{
		return m_groupEntities[typeid(T).hash_code()];
	}

	template<typename T, typename TFunc>
	void forEach(const TFunc& func)
	{
		auto& vec(getAll<T>());
		for (auto ptr : vec)
		{
			func(*reinterpret_cast<T*>(ptr));
		}
	}

	void clear();
	void refresh();
	void update(float deltaTime);
	void draw(sf::RenderWindow& window);

private:
	std::vector<std::unique_ptr<Entity>> m_entities;
	std::map<std::size_t, std::vector<Entity*>> m_groupEntities;
};
