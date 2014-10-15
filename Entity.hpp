#pragma once

#include "SFML\Graphics.hpp"

class Entity
{
public:
	virtual ~Entity() {}
	virtual void update(float deltaTime) {};
	virtual void draw(sf::RenderWindow& window) {};
	bool isAlive() const { return m_alive; }
	void destroy() { m_alive = false; }

private:
	bool m_alive{ true };
};