#ifndef _Game
#define _Game

#include "CRandom.h"
#include "CScreen.h"
using namespace std;

#define WHEEL 0
class Game // abstract base class for games
{

   protected:
     CScreen S;      // screen handler
     CRandom R;    //random # generator
     int gameType; // identifies the game
     int *playerScore; // array of player scores - dynamically created
     int nbrPlayers; // # of players in the game

   public:
	   Game(int type, int players){nbrPlayers = players;};
	   Game();
	   ~Game(){delete []playerScore;}
     int getScore(int playerNbr); // return the score for a player
     void updateScore(int playerNbr, int amt); // adds or subtracts amt form a player's score
	 void clearScore();
    // abstract methods - must be overridden
    virtual void playGame(int players) = 0; // start playing the game
    virtual void endGame() = 0; // end the game
	

    // other methods as needed

};


#endif