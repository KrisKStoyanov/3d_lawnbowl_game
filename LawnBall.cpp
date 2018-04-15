#include "LawnBall.h"



LawnBall::LawnBall(GameObject* _gameObject, int _teamId)
{
	gameObject = _gameObject;
	teamId = _teamId;
	active = true;
}


LawnBall::~LawnBall()
{
}
