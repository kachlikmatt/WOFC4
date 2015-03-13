#ifndef CFOUR_H
#define CFOUR_H

#include "Games.h"
#include "Checker.h"
#include "CScreen.h"

using namespace std;

class CFour : public Game
{ 
     int row, col; // row col of the piece - not really needed here
     int score[2]; // one point for each checker in a row on a winning move
	 int currentPlayer;
	 int ySlot;
	 int p1Wins, p2Wins;
	 

   Checker board[7][6];

   bool check4Win(int col, int row);  // true if 4 in a row
   void printBoard(); 
   void clearBoard();  // set board to EMPTY
   char drop(int slot);
  

   bool IsHorizontalMatch(int x, int y);
   bool IsVerticalMatch(int y, int x);
   bool IsDiagnol1Match(int y, int x); // (/)
   bool IsDiagnol2Match(int y, int x); // (\)
   void CFour::setP1(int winScore){p1Wins+=winScore;};
   void CFour::setP2(int winScore){p2Wins+=winScore;};
   void CFour::resetP1(){p1Wins = 0;};
   void CFour::resetP2(){p2Wins = 0;};

public:
  CFour(int type, int players); // constructor - call clearBoard();
  void playGame(int); // play a game w/ option to play again
  void endGame(); 
  ~CFour();
};
#endif