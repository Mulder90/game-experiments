#pragma once

#include <vector>
#include <memory>
#include <string>

#include "SFML\Graphics.hpp"

class GameState;

enum class Status{ Running, Ending };

class Game
{
public:
	Game(const std::string& title, const unsigned int width = 800, const unsigned int height = 600);
	~Game();

	void run();

	void changeState(GameState* state);
	void pushState(GameState* state);
	void popState();

	sf::RenderWindow& getWindow() { return m_window; }

	Status& getStatus() { return m_status; }
	void setStatus(Status status) { m_status = status; }

private:
	sf::RenderWindow m_window;
	Status m_status{ Status::Running };
	std::vector <std::unique_ptr<GameState>> m_states;
};