#pragma once
#include "GameObject.h"
class LawnBall
{
public:
	LawnBall(GameObject* _gameObject, int _teamId);
	~LawnBall();
	int teamId;
	GameObject* gameObject;
	bool active;
	float distFromJack;
};

