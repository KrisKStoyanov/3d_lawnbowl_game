#pragma once
#include "LawnBall.h"

class Team
{
public:
	Team(int teamId);
	~Team();
	int teamId;
	std::vector<LawnBall> lawnballs;
	float score;
	bool played;
};

