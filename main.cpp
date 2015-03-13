#include <iostream>
#include <stdio.h>
#include "CScreen.h"
#include "Games.h"
#include "CFour.h"
#include "WOMF.h"
//Matthew Kachlik
void main()
{
	CScreen S;
	Wheel w;
	int nbrPlayers;
	
	char game[2] = {'4'};
	char playAgain[2];
	bool play = true;
		do
		{
			game[0] = '7';
		while(game[0] != '1' && game[0] != '2')
		{
			S.DrawString("1)Conncect4",0,0);
			S.DrawString("2)Wheel of Fortune",0,1);
			S.DrawString("3)Exit",0,2);
			S.DrawString("Please enter the game you would like to play",0,3);
			S.GetStr(0,4,game,1,"#",true);
			if(game[0] == '3')
			{

				exit(0);
			}
		}
		S.ClearScreen();
		if(game[0] == '1')
		{
		
				CFour CF(1, 2);
		
				CF.playGame(2);
		

		}
		if(game[0] == '2')
		{
			do
			{
			S.GotoXY(0,0);
			cout<<"How many players?";
			nbrPlayers = S.GetVal(0,1);
			S.ClearScreen();
			}
			while(nbrPlayers < 2 || nbrPlayers > 4);
			w.playGame(nbrPlayers);
		}
		S.ClearScreen();
		}while(play);
	

}