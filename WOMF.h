#include "Games.h"
#include <iostream>
#include <stdio.h>
#include <vector>
#include <string>
class Wheel:public Game
{
	
	

	CScreen S;
	private:
	int players;
	vector<string> names;
	vector<char*> fullPhrases;
	vector<int> roundScores;
	int wBank[26][2];
	int rounds;
	int turn;//used to go into the round scores and add to the appriate player
	int prevWinner;
	
	public:
		int getNumPlayers();
		void Wheel::setNumPlayers(int);
		Wheel();
		
		void resetBank();
		void Wheel::clearRoundScores();
		void playGame(int nbrPlyers);
		void playRound(int nbrPlyers,int);
		void endGame();
		void showBank();	
		void showPhrase(int);
		void hidePhrase(int);
		void inPhrase(char,int,int,bool);
		void changeBoard(int,int);
		void addPoint(int,int,int);
		void subPoint(int,int);
		int getTurn(){return turn;};
		void setTurn(int n){turn = n;};
		int getRoundScore(int p){return roundScores.at(p);};
		void setPrevWinner(int n){prevWinner = n;};
		int  getPreWinner(){return prevWinner;};
		void drawTurnPtr(int);
		void clearPhrase(int numBoard);
		char DrawMenu();
		void clearMenu();
		void clearMessage();
		void spinWheel(int);
		bool checkPhrase(int,int);
		void clearTurnPtr(int turn);
		void showTotalScores();
		void gameOver(int);
		void rankPlayers(int*,int);

};