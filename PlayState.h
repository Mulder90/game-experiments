#pragma once

#include "GameState.h"
#include "Game.h"
#include "EntityManager.h"
#include "Ball.h"
#include "Block.h"
#include "Paddle.h"
#include "Collision.h"
#include "SFML\Graphics.hpp"

class PlayState : public GameState
{
public:
	void init(Game* game)
	{
		const unsigned int windowWidth = game->getWindow().getSize().x;
		const unsigned int windowHeight = game->getWindow().getSize().y;
		sf::Vector2f blockSize{ 60.f, 20.f };
		const int countBlocksX = 11, countBlocksY = 4;
		const int margin = 3;
		const float padding = ((windowWidth - ((blockSize.x + margin) * countBlocksX)) / 2.f) - blockSize.x / 2.f;

		m_entityManager.clear();
		for (int i = 1; i <= countBlocksX; ++i)
		{
			for (int j = 1; j <= countBlocksY; ++j)
			{
				auto& block(m_entityManager.create<Block>(sf::Vector2f(i * (blockSize.x + margin) + padding, j * (blockSize.y + margin)), blockSize));
				block.setRequiredHits(1 + (i + j) % 3);
			}
		}
		m_entityManager.create<Paddle>(sf::Vector2f(windowWidth / 2.f, windowHeight - 30.f));
		m_entityManager.create<Ball>(sf::Vector2f(windowWidth / 2.f, windowHeight / 2.f));
	}

	void cleanUp() { }

	void pause() { }

	void resume() { }

	void handleEvent(Game* game)
	{
		sf::Event event;
		while (game->getWindow().pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				game->setStatus(Status::Ending);
				game->getWindow().close();
				break;
			}
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Key::Escape)
				game->setStatus(Status::Ending);
			if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Key::R)
				init(game);
			if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Key::Space)
			{
				m_entityManager.forEach<Ball>([](Ball& ball)
				{
					ball.setVelocity({ 0.6f, -0.6f });
				});
			}
		}
	}

	void update(Game* game, float deltaTime)
	{
		m_entityManager.update(deltaTime);
		m_entityManager.forEach<Ball>([this](Ball& ball)
		{
			m_entityManager.forEach<Block>([&ball](Block& block)
			{
				checkBlockBallCollision(block, ball);
			});
			m_entityManager.forEach<Paddle>([&ball](Paddle& paddle)
			{
				checkPaddleBallCollision(paddle, ball);
			});
		});
		m_entityManager.refresh();
	}

	void draw(Game* game)
	{
		m_entityManager.draw(game->getWindow());
	}

private:
	EntityManager m_entityManager;
};