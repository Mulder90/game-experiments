#pragma once

#include "Entity.hpp"

class Ball : public Entity
{
public:
	Ball(sf::Vector2f position)
	{
		m_shape.setOrigin(10.f, 10.f);
		m_shape.setRadius(10.f);
		m_shape.setPosition(position);
		m_shape.setFillColor(sf::Color::Green);
		m_velocity = { 0.6f, -0.6f };
		m_maxVelocity = 0.7f;
	}

	void update(float deltaTime) override
	{
		m_shape.move(m_velocity * deltaTime);
		solveBoundCollision();
		if (bottom() > 570)
		{
			setPosition({ 800 / 2.f, 600 / 2.f });
			setVelocity({ 0.f, 0.f });
		}
	}

	void draw(sf::RenderWindow& window) override { window.draw(m_shape); }

	sf::Vector2f getVelocity() const { return m_velocity; }
	void setVelocity(sf::Vector2f velocity) { m_velocity = velocity; }

	float getMaxVelocity() const { return m_maxVelocity; }

	void setPosition(sf::Vector2f position) { m_shape.setPosition(position); }

	float x() const { return m_shape.getPosition().x; }
	float y() const { return m_shape.getPosition().y; }

	float left() const { return x() - m_shape.getRadius(); }
	float right() const { return x() + m_shape.getRadius(); }
	float top() const { return y() - m_shape.getRadius(); }
	float bottom() const { return y() + m_shape.getRadius(); }

private:
	sf::CircleShape m_shape;
	sf::Vector2f m_velocity;
	float m_maxVelocity;

	void solveBoundCollision()
	{
		if (left() < 0 || right() > 800)
			m_velocity.x *= -1;
		if (top() < 0)
			m_velocity.y *= -1;
	}
};