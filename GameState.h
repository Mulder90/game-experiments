#pragma once

class Game;

class GameState
{
public:
	virtual void init(Game* game) = 0;
	virtual void cleanUp() = 0;

	virtual void pause() = 0;
	virtual void resume() = 0;

	virtual void handleEvent(Game* game) = 0;
	virtual void update(Game* game, float deltaTime) = 0;
	virtual void draw(Game* game) = 0;
};