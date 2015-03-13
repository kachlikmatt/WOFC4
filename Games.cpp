#include "Games.h"
void Game::updateScore(int numPlayer,int addScore)
{
	playerScore[numPlayer] += addScore;
}
int Game::getScore(int numPlayer)
{
	return playerScore[numPlayer];
}
void Game::clearScore()
{
	for(int i = 1; i <= nbrPlayers;i ++)
	playerScore[i] = 0;
}

