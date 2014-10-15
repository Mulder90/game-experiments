#pragma once

#include "Entity.hpp"

class Block : public Entity
{
public:
	Block(sf::Vector2f position, sf::Vector2f size)
	{
		m_shape.setPosition(position);
		m_shape.setSize(size);
		m_shape.setFillColor(sf::Color(255, 255, 255));
		m_shape.setOrigin(size.x / 2.f, size.y / 2.f);
		m_size = size;
	}

	void update(float deltaTime) override
	{
		if (m_requiredHits == 1)
			m_shape.setFillColor(sf::Color(255, 255, 255));
		else if (m_requiredHits == 2)
			m_shape.setFillColor(sf::Color(170, 170, 170));
		else
			m_shape.setFillColor(sf::Color(100, 100, 100));
	}

	void draw(sf::RenderWindow& window) override { window.draw(m_shape); }

	int getRequiredHits() const { return m_requiredHits; }
	void setRequiredHits(int hits) { m_requiredHits = hits; }

	float x() const { return m_shape.getPosition().x; }
	float y() const { return m_shape.getPosition().y; }

	float left() const { return x() - m_size.x / 2.f; }
	float right() const { return x() + m_size.x / 2.f; }
	float top() const { return y() - m_size.y / 2.f; }
	float bottom() const { return y() + m_size.y / 2.f; }

private:
	sf::RectangleShape m_shape;
	sf::Vector2f m_size;
	int m_requiredHits = 1;
};