#include "Game.h"
#include "GameState.h"

#include <chrono>

using namespace std;
using namespace sf;

Game::Game(const string& title, const unsigned int width, const unsigned int height)
{
	m_window.create({ width, height }, title, Style::Titlebar | Style::Close);
	m_window.setVerticalSyncEnabled(true);
}

Game::~Game()
{
	while (!m_states.empty())
	{
		m_states.back()->cleanUp();
		m_states.pop_back();
	}
	m_window.close();
}

void Game::run()
{
	const float ftStep = 1.f, ftSlice = 1.f;
	float lastFt = 0.f;
	float currentSlice = 0.f;
	while (m_status != Status::Ending)
	{
		auto startTime = chrono::high_resolution_clock::now();
		m_window.clear();
		m_states.back()->handleEvent(this);
		currentSlice += lastFt;
		while (currentSlice >= ftSlice)
		{
			m_states.back()->update(this, ftStep);
			currentSlice -= ftSlice;
		}
		m_states.back()->draw(this);
		m_window.display();

		auto endTime = chrono::high_resolution_clock::now();
		auto elapsedTime = endTime - startTime;
		lastFt = chrono::duration_cast<chrono::duration<float, milli>>(elapsedTime).count();
#ifdef _DEBUG
		int fps = int(1.f / (lastFt / 1000.0f));
		m_window.setTitle(" FPS: " + to_string(fps));
#endif
	}
}

void Game::changeState(GameState* state)
{
	if (!m_states.empty())
	{
		m_states.back()->cleanUp();
		m_states.pop_back();
	}

	m_states.emplace_back(state);
	m_states.back()->init(this);
}

void Game::pushState(GameState* state)
{
	if (!m_states.empty())
	{
		m_states.back()->pause();
	}

	m_states.emplace_back(state);
	m_states.back()->init(this);
}

void Game::popState()
{
	if (!m_states.empty())
	{
		m_states.back()->cleanUp();
		m_states.pop_back();
	}

	if (!m_states.empty())
	{
		m_states.back()->resume();
	}
}