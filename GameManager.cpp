#include "GameManager.h"



GameManager::GameManager()
{
}


GameManager::~GameManager()
{
}

void GameManager::LocateCurrentBall()
{
	for (int i = 0; i < lawnBalls.size(); i++) {
		if (lawnBalls[i]->teamId == currentTeam && lawnBalls[i]->active) {
			currentBall = lawnBalls[i]->gameObject;
			lawnBalls[i]->gameObject->physObj->position = throwingPos;
			break;
		}
	}
}

void GameManager::Setup(int _numOfTeams, int _startingTeam, int _ballsPerTeam, glm::vec3 _throwingPos)
{
	numOfTeams = _numOfTeams;
	startingTeam = _startingTeam;
	ballsPerTeam = _ballsPerTeam;
	throwingPos = _throwingPos;
	for (int i = 0; i < numOfTeams; i++) {
		teams.push_back(new Team(i));
	}
	//for (int i = 1; i < teams; i++) {
	//	teamIds.push_back(i);
	//}
	//for (int i = 0; i < teams; i++) {
	//	teamScores.push_back(0);
	//}
	nextThrowReady = true;
	inactiveJack = true;
	gameOver = false;
	announceWin = false;
	declaredWin = false;
	currentTeam = startingTeam;
}

void GameManager::AddLawnBall(GameObject * _lawnBall, int teamId)
{
	LawnBall* lawnBall = new LawnBall(_lawnBall, teamId);
	lawnBalls.push_back(lawnBall);
}

void GameManager::GetJack(GameObject * _jack)
{
	jack = _jack;
	jack->physObj->position = throwingPos;
	currentBall = jack;
}

void GameManager::ThrowJack()
{
	if (nextThrowReady) {
		if (prepareThrow) {
			prepAccel += 1.0f;
			//std::cout << "prepping to throw jack" << std::endl;
			//std::cout << prepAccel << std::endl;
		}
		else if (!prepareThrow) {
			nextThrowReady = false;
			jack->physObj->acceleration = prepAccel;
			prepAccel = 0.0f;
			//std::cout << "jack thrown" << std::endl;
		}
	}
}

void GameManager::ThrowBall()
{
	if (nextThrowReady) {
		if (prepareThrow) {
			prepAccel += 1.0f;
			//std::cout << "prepping to throw bowl" << std::endl;
			//std::cout << prepAccel << std::endl;
		}

		else if (!prepareThrow) {
			nextThrowReady = false;
			for (int i = 0; i < lawnBalls.size(); i++) {
				if (lawnBalls[i]->teamId == currentTeam && lawnBalls[i]->active) {
					lawnBalls[i]->gameObject->physObj->acceleration = prepAccel;
					lawnBalls[i]->active = false;

					for (int j = 0; j < teams.size(); j++) {
						if (teams[j]->teamId == currentTeam) {
							teams[j]->played = true;
						}
					}
					break;
				}
			}
			prepAccel = 0.0f;

			//Check next team to throw
			bool allTeamsPlayed = true;
			for (int i = 0; i < teams.size(); i++) {
				if (!teams[i]->played) {
					currentTeam = teams[i]->teamId;
					allTeamsPlayed = false;
					break;
				}
			}

			//Each team throws again
			if (allTeamsPlayed) {
				currentTeam = teams[0]->teamId;
				for (int i = 0; i < teams.size(); i++) {
					teams[i]->played = false;
				}
			}

			for (int i = 0; i < lawnBalls.size(); i++) {
				if (lawnBalls[i]->active) {
					gameOver = false;
					break;
				}
				else {
					gameOver = true;
				}
			}
		}
	}
}

void GameManager::SettleGame()
{
	for (int i = 0; i < lawnBalls.size(); i++) {
		if (lawnBalls[i]->gameObject->physObj->velocity!= glm::vec3(0.0,0.0,0.0)) {
			announceWin = false;
			break;
		}
		else {
			announceWin = true;
		}
	}

	//calculate distance to jack for each ball
	if (gameOver && announceWin && !declaredWin) {
		for (int i = 0; i < lawnBalls.size(); i++) {
			lawnBalls[i]->distFromJack = glm::length(lawnBalls[i]->gameObject->physObj->position - jack->physObj->position);
			for (int j = 0; j < teams.size(); j++) {
				if (lawnBalls[i]->teamId == teams[j]->teamId) {
					teams[j]->score += lawnBalls[i]->distFromJack;
				}
			}
		}
		int winnerId;
		float shortestDist = 10000;
		for (int i = 0; i < teams.size(); i++) {
			std::cout << teams[i]->score << std::endl;
			if (teams[i]->score < shortestDist) {
				shortestDist = teams[i]->score;
				winnerId = teams[i]->teamId;
			}
		}

		std::cout << "Winner: Team " << winnerId << "! Combined distance:" << shortestDist << std::endl;
		declaredWin = true;
	}
}
