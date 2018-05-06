#pragma once
#include <iostream>
#include "LawnBall.h"
#include "Team.h"

#include "glm/gtx/rotate_vector.hpp"
#include <time.h>
class GameManager
{
public:
	GameManager();
	~GameManager();
	int numOfTeams;
	bool inactiveJack;
	int startingTeam;
	int ballsPerTeam;

	int currentTeam;

	bool nextThrowReady;
	bool prepThrow;
	bool backhand;

	float prepAccel;
	float prepRot;

	bool declaredWin;
	bool announceWin;
	bool gameOver;

	glm::vec3 throwingPos;

	//Dynamic condition for rotation angle setting
	glm::vec3 weatherEffect;

	void LocateCurrentBall();
	void SwapThrowhand();
	void Setup(int _numOfTeams, int _startingTeam, int _ballsPerTeam, glm::vec3 _throwingPos);
	void AddLawnBall(GameObject* _lawnBall, int teamId);
	void GetJack(GameObject* _jack);
	GameObject* currentBall;
	void ThrowJack();
	void ThrowBall();
	std::vector<Team*> teams;
	std::vector<LawnBall*> lawnBalls;
	GameObject* jack;
	void SettleGame();
};

