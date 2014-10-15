#pragma once

#include "Paddle.h"
#include "Ball.h"
#include "Block.h"

template<class T1, class T2> bool isIntersecting(const T1& a, const T2& b)
{
	return a.right() > b.left()
		&& a.left() < b.right()
		&& a.bottom() > b.top()
		&& a.top() < b.bottom();
}

void checkPaddleBallCollision(Paddle& paddle, Ball& ball)
{
	if (!isIntersecting(paddle, ball)) return;
	if (ball.bottom() >= paddle.top())
	{
		ball.setVelocity({ ball.getVelocity().x, ball.getVelocity().y * -1 });
		if (ball.x() < paddle.x())
			ball.setVelocity({ ball.getVelocity().x * -1, ball.getVelocity().y });
	}
}

void checkBlockBallCollision(Block& block, Ball& ball)
{
	if (!isIntersecting(block, ball))
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