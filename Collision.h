#pragma once

#include "Paddle.h"
#include "Ball.h"
#include "Block.h"

template<class T1, class T2> bool rectCollision(const T1& a, const T2& b)
{
	return !(b.left() >= a.right() || b.right() <= a.left() || b.top() >= a.bottom() || b.bottom() <= a.top());
}

void checkPaddleBallCollision(Paddle& paddle, Ball& ball)
{
	if (!rectCollision(paddle, ball)) return;
	if (ball.bottom() >= paddle.top())
	{
		auto ballVelocity = ball.getVelocity();
		auto paddleVelocity = paddle.getVelocity();
		float ballMaxVelocity = ball.getMaxVelocity();
		float sumX = ballVelocity.x + paddleVelocity.x;
		float newXVelocity = (abs(sumX) <= ballMaxVelocity) ? sumX : ballMaxVelocity;
		newXVelocity = (abs(newXVelocity) >= 0.25f) ? newXVelocity : ((newXVelocity > 0) ? newXVelocity + 0.15f : newXVelocity - 0.15f);
		ball.setVelocity({ newXVelocity, ballVelocity.y * -1 });
	}
}

void checkBlockBallCollision(Block& block, Ball& ball)
{
	if (!rectCollision(block, ball))
		return;

	block.setRequiredHits(block.getRequiredHits() - 1);
	if (block.getRequiredHits() <= 0)
		block.destroy();

	float overlapLeft{ ball.right() - block.left() };
	float overlapRight{ block.right() - ball.left() };
	float overlapTop{ ball.bottom() - block.top() };
	float overlapBottom{ block.bottom() - ball.top() };

	bool ballFromLeft(abs(overlapLeft) < abs(overlapRight));
	bool ballFromTop(abs(overlapTop) < abs(overlapBottom));

	float minOverlapX{ ballFromLeft ? overlapLeft : overlapRight };
	float minOverlapY{ ballFromTop ? overlapTop : overlapBottom };

	if (abs(minOverlapX) < abs(minOverlapY))
		ball.setVelocity({ ballFromLeft ? -abs(ball.getVelocity().x) : abs(ball.getVelocity().x), ball.getVelocity().y });
	else
		ball.setVelocity({ ball.getVelocity().x, ballFromTop ? -abs(ball.getVelocity().y) : abs(ball.getVelocity().y) });
}