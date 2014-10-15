#pragma once

#include "Entity.hpp"

class Paddle : public Entity
{
public:
	Paddle(sf::Vector2f position)
	{
		m_shape.setPosition(position);
		m_shape.setSize({ 80.f, 20.f });
		m_shape.setFillColor(sf::Color::Red);
		m_shape.setOrigin(m_shape.getSize().x / 2.f, m_shape.getSize().y / 2.f);
		m_velocity = { 0.7f, 0.f };
	}

	void update(float deltaTime) override
	{
		m_shape.move(m_velocity * deltaTime);
		processPlayerInput();
	}

	void draw(sf::RenderWindow& window) override { window.draw(m_shape); }

	sf::Vector2f getVelocity() const { return m_velocity; }
	void setVelocity(sf::Vector2f velocity) { m_velocity = velocity; }

	void setPosition(sf::Vector2f position) { m_shape.setPosition(position); }

	float x() const { return m_shape.getPosition().x; }
	float y() const { return m_shape.getPosition().y; }

	float left() const { return x() - m_shape.getSize().x / 2.f; }
	float right() const { return x() + m_shape.getSize().x / 2.f; }
	float top() const { return y() - m_shape.getSize().y / 2.f; }
	float bottom() const { return y() + m_shape.getSize().y / 2.f; }

private:
	sf::RectangleShape m_shape;
	sf::Vector2f m_velocity;

	void processPlayerInput()
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) && right() < 800)
			m_velocity.x = 0.7f;
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) && left() > 0)
			m_velocity.x = -0.7f;
		else
			m_velocity.x = 0;
	}

};