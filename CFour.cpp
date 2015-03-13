#include "CFour.h"
#include "Checker.h"
#include <iostream>
#include <conio.h>

using namespace std;

CFour::CFour(int type, int players) : Game(type, players)
{
	CScreen S;
	
	int p1Wins, p2Wins = 0;
	resetP1();
	resetP2();

}


void CFour :: printBoard()
{
	clearBoard();

		S.GotoXY(66,15);
		cout << p2Wins;
		S.GotoXY(66,6);
		cout << p1Wins;
		currentPlayer++;
	S.Box(60,4,75,10,GREEN);
	S.Box(60,12,75,18,AQUA);
	S.DrawString("Player 1",64,4, BLACK, GREEN);
	S.DrawString("Player 2",64,12, BLACK, AQUA);
	S.Box(0,0,36,20, RED);
	S.DrawString("   1    2    3    4    5    6    7",0,0, BLACK, RED);

	for(int i = 0;  i < 7; i++)
	{
		for(int j = 0; j < 6; j++)
		{
			board[i][j].draw(S,i,j); 
		}
	}
	
}

void CFour :: clearBoard()
{
	for(int i = 0;  i < 7; i++)
	{
		for(int j = 0; j < 6; j++)
		{
			board[i][j].setState(2); 
			board[i][j].draw(S,i,j);
		}
	}
}

char CFour :: drop(int slot)
{
	if(board[slot][0].getState() != 2)
	{
		return 'a';
	}
	for(int i = 0; i< 6; i++)
	{
		if(board[slot][i].getState() == 2)
		{
			if(currentPlayer == 1)
			{
				board[slot][i].setState(1);
				

			}
			else
			{
				board[slot][i].setState(0);
				
			}
			board[slot][i].draw(S,slot, i);
			Sleep(100);
			
			if( i < 5 && board[slot][i+1].getState() == 2)
			{

				board[slot][i].setState(2);
				board[slot][i].draw(S,slot, i);
				Sleep(100);
				continue;
			}
			else
			{
				ySlot = i;
				return i;
			}
			
		}

	}
	
	
}


void CFour:: playGame(int players)	
{
	
	char row;
	printBoard();
	char slot;
	currentPlayer = 0;
	
	if(players == -1)
	{
		return;

	}
	do 
	{
		S.GotoXY(66,15);
		cout << p2Wins;
		S.GotoXY(66,6);
		cout << p1Wins;
		currentPlayer++;
		slot = _getch();
		slot -= 49;
		while(slot < 0 || slot > 6)
		{
			slot = _getch();
			slot -= 49;
		}
		S.GotoXY(25,23);
		cout << "                            ";
		row = drop(slot);
		if(row == 'a')
		{
			S.GotoXY(25,23);
			cout << "Please input proper choice";
			currentPlayer --;
			continue;
		}
		currentPlayer = currentPlayer%2;
	
	}while(!check4Win(row,slot));
	S.GotoXY(40,1);
	if(currentPlayer == 0)
	{
		
		S.GotoXY(66,6);
		cout << p1Wins;
		S.Delay();
		
	}
	else
	{
		
		S.GotoXY(66,15);
		cout << p2Wins;
		S.Delay();
		
	}
	
		endGame();
	
}

bool CFour:: check4Win(int x, int y)
{

	bool horizontal = false;
	bool vertical = false;
	bool diagnol1 = false;
	bool diagnol2 = false;
	if(IsHorizontalMatch(x, y) == true)
	{
		horizontal = true;
	}
	if(IsVerticalMatch(x, y) == true)
	{
		 vertical = true;
	}
	if(IsDiagnol1Match(x, y) == true)
	{
		diagnol1 = true;
	}
	if(IsDiagnol2Match(x, y) == true)
	{
		diagnol2 = true;
	}
	if(horizontal == false && vertical == false && diagnol1 == false && diagnol2 == false)
	{
		S.GotoXY(40,15);
		cout<<"no win";
		return false;
	}
	else
	{
		S.GotoXY(40,15);
		cout<<"chicken Dinner";
		return true;
	}
}
void CFour:: endGame()
{
	
	S.GotoXY(25, 23);
	cout << "Would you like to play again? 1 = yes, 2 = no";
	char res;
		res = _getch();
		
		S.GotoXY(25, 23);
		cout << "                                              ";
		S.GotoXY(25, 24);
		if(res != '2')
		{
			
			playGame(2);
		}
		else
		{
			playGame(-1);
		}
}

bool CFour::IsHorizontalMatch(int y, int x) 
{
    /* Get the value of the start position. */
	int col = x;
	int winScore = 0;
    /* Confirm the two values after it match. */
    while(col < 7 && board[col][y].getState() ==  board[x][y].getState())
	{

		col ++;
		winScore ++;
		
	}
	col = x;
	 while(col-- >= 0 && board[col][y].getState() ==  board[x][y].getState())
	{
		winScore ++;
		
	}
	
    /* If we got here, then they all match! */
    if(winScore > 3)
	{
		if(currentPlayer == 0)
		{
			setP1(winScore);
		}
		else
			setP2(winScore);
		return true;
	}
	return false;
}
bool CFour :: IsVerticalMatch(int y, int x)
{
	/* Get the value of the start position. */
	int row = y;
	int winScore = 0;

	/* Confirm the two values after it match. */
	while(row >= 0 && board[x][row].getState() ==  board[x][y].getState())
	{
		
		row ++;
		winScore ++;
	}
	/* If we got here, then they all match! */
    if(winScore > 3)
	{
		if(currentPlayer == 0)
		{
			setP1(winScore);
		}
		else
			setP2(winScore);
		return true;
	}
	return false;

}
 bool CFour :: IsDiagnol1Match(int y, int x) // (/)
 {
	 	/* Get the value of the start position. */
	int col = x;
	int row = y;
	int winScore = 0;

	/* Confirm the two values after it match. */
	while(row < 6 && col >= 0 && board[col][row].getState() ==  board[x][y].getState())
	{
		col --;
		row ++;
		winScore ++;
		
	}
	col = x;
	row = y;
	
	while(row-- >= 0 && col++ < 7 && board[col][row].getState() ==  board[x][y].getState())
	{
		winScore ++;
		
	}
	/* If we got here, then they all match! */
    if(winScore > 3)
	{
		if(currentPlayer == 0)
		{
			setP1(winScore);
		}
		else
			setP2(winScore);
		return true;
	}
	return false;

 }
  bool CFour :: IsDiagnol2Match(int y, int x) // (\)
 {
	 	/* Get the value of the start position. */
	int col = x;
	int row = y;
	int winScore = 0;


	/* Confirm the two values after it match. */
	while(row < 6 && col < 7 && board[col][row].getState() ==  board[x][y].getState())
	{
		col ++;
		row ++;
		winScore ++;	
	}
	col = x;
	row = y;
	while(row-- >= 0 && col-- > 0 && board[col][row].getState() ==  board[x][y].getState())
	{
		winScore ++;
		S.GotoXY(40,3);	
	}

	/* If we got here, then they all match! */
    if(winScore > 3)
	{
		if(currentPlayer == 0)
		{
			setP1(winScore);
		}
		else
			setP2(winScore);
		return true;
	}
	return false;

 }
 CFour:: ~CFour()
 {


 }