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

void GameManager::SwapThrowhand()
{
	if (backhand) {
		backhand = false;
	}
	else {
		backhand = true;
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
	nextThrowReady = true;
	inactiveJack = true;
	gameOver = false;
	announceWin = false;
	declaredWin = false;
	backhand = true;
	currentTeam = startingTeam;

	prepAccel = 0.0f;
	prepRot = 0.0f;

	//Preset Weather Effect
	srand(time(NULL));
	weatherEffect.x = rand() % 15 + -15;
	weatherEffect.z = rand() % 15 + -15;
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

		if (prepThrow) {
			prepAccel += 2.0f;
			prepRot += .5f;

		}
		else if (!prepThrow) {
			nextThrowReady = false;

			//Hard cap for balancing gameplay
			if (prepAccel >= 30.0f) {
				prepAccel = 30.0f;
			}
			if (prepRot >= 10.0f) {
				prepRot = 10.0f;
			}

			//Determine rotation angle
			if (backhand) {
				prepRot *= 1.0f;
			}
			else if (!backhand) {
				prepRot *= -1.0f;
			}

			jack->physObj->SetTrajectory(false, prepAccel, prepRot, true, weatherEffect);
			prepAccel = 0.0f;
			prepRot = 0.0f;
		}
	}
}

void GameManager::ThrowBall()
{
	if (nextThrowReady) {
		if (prepThrow) {
			prepAccel += 1.0f;
			prepRot += .25f;
		}

		else if (!prepThrow) {
			nextThrowReady = false;
			for (int i = 0; i < lawnBalls.size(); i++) {
				if (lawnBalls[i]->teamId == currentTeam && lawnBalls[i]->active) {

					//Hard cap for balancing gameplay
					if (prepAccel >= 30.0f) {
						prepAccel = 30.0f;
					}
					if (prepRot >= 7.5f) {
						prepRot = 7.5f;
					}

					//Determine rotation angle
					if (backhand) {
						prepRot *= 1.0f;
					}
					else if (!backhand) {
						prepRot *= -1.0f;
					}

					lawnBalls[i]->gameObject->physObj->SetTrajectory(true, prepAccel, prepRot, true, weatherEffect);
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
			prepRot = 0.0f;

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
		float shortestDist = teams[0]->score;
		for (int i = 0; i < teams.size(); i++) {
			std::cout << "Team: " << teams[i]->teamId << " Score: " << teams[i]->score << std::endl;
			if (teams[i]->score < shortestDist) {
				shortestDist = teams[i]->score;
				winnerId = teams[i]->teamId;
			}
		}

		std::cout << "Winner: Team " << winnerId << "! Combined distance:" << shortestDist << std::endl;
		declaredWin = true;
	}
}
