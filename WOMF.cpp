#include "WOMF.h"

Wheel::Wheel():Game(1,players)
{
	
	
	names.push_back("Null");
	names.push_back("player1");
	names.push_back("player2");
	names.push_back("player3");
	names.push_back("player4");

	fullPhrases.push_back("MAY THE FORCE BE WITH YOU");
	fullPhrases.push_back("ARE YOU LOOKIN AT ME");
	fullPhrases.push_back("I MUST BREAK YOU");
	fullPhrases.push_back("WOLVERINES");//RED DAWN
	fullPhrases.push_back("THEY CALL IT A ROYALE WITH CHEESE");
	fullPhrases.push_back("FLY YOU FOOLS");
	fullPhrases.push_back("LIVE LONG AND PROSPER");
	fullPhrases.push_back("YO ADRIAN");
	fullPhrases.push_back("I CRAP BIGGER THAN YOU");//city slickers
	fullPhrases.push_back("HELLO CLARICE");
	fullPhrases.push_back("OH BEHAVE YEAH YEAH BABY");
	fullPhrases.push_back("YOU KNOW THE DIFFERENCE BETWEEN YOU AND ME IS I MAKE THIS LOOK GOOD");
	fullPhrases.push_back("I SEE DEAD PEOPLE");
	fullPhrases.push_back("THEY CALL IT A ROYALE WITH CHEESE");
	fullPhrases.push_back("SAY HELLO TO MY LITTLE FRIEND");
	fullPhrases.push_back("ARE YOU NOT ENTERTAINED");
	fullPhrases.push_back("JUST A FLESH WOUND");
	fullPhrases.push_back("SNAKES WHY DID IT HAVE TO BE SNAKES");
	fullPhrases.push_back("NOBODY MAKES ME BLEED MY OWN BLOOD");//dodgeball
	fullPhrases.push_back("I LOVE THE SMELL OF NAPALM IN THE MORNING");
	fullPhrases.push_back("THERE IS NO PLACE LIKE HOME");
	setTurn(1);
	const int lengthOfMenu = 64;

}
/*
	play game 

	sets up the game and starts the game
	once the game is completed then the user
	will be prompted if they wanted to play again
	along with showing the scores


*/
void Wheel::playGame(int nbrPlyers)
{
	
	char letter = 'A';//used to start the alphabet 
	/*
		preping the word bank to be displayed
	*/
	for(int i = 0; i <= 25; i++)
	{
		wBank[i][0] = 0;
		wBank[i][1] = (int)letter;
		letter += 1;
	}
	
	//used to reset the game
	int rounds = 0;
	const int MAXPLAYERS = 4;
	const int MAXROUNDS = 10;
	int puzzleNum = 0;
	
	
	setNumPlayers(nbrPlyers);
	playerScore = new int[nbrPlyers];
	clearScore();
	showBank();
	roundScores.push_back(-1);
	//reseting the total scores from previous game
	for(int i = 1; i <= nbrPlyers; i ++)
	{
		updateScore(i,0);
		S.GotoXY(i*15,15);
		cout<<names.at(i).c_str();
		S.GotoXY(i*15,16);
		
		roundScores.push_back(0);
		
	}
	clearRoundScores();
	
	
	
	//starting a new round
	do
	{
		R.setRange(19,0);
		puzzleNum = R.fnRand();
		showTotalScores();
		playRound(nbrPlayers,puzzleNum);
		
		rounds++;
	}while(rounds < MAXROUNDS);
	gameOver(nbrPlyers);
	
	
}
/*
	hide phrase
	makes the phrase into under scores ex; hello world
	will be come _ _ _ _ _  _ _ _ _ _
*/
void Wheel::hidePhrase(int pNum)
{
	char *temp;
	
	//replacing the A-Z as _
	for(int i = 0; i < strlen(fullPhrases.at(pNum)); i ++)
	{
		
		if(fullPhrases.at(pNum)[i] != ' ')
		{
			temp = "_";
			//alternating colors for readability
			if(i % 2 == 0)
			S.DrawString(temp,i+5,10,GOLD,BLACK);
			else
			S.DrawString(temp,i+5,10,OLIVE,BLACK);
		}
		else
		{
			temp = &fullPhrases.at(pNum)[i];
			
			S.DrawString(temp,i+5,10,BLUE,BLACK);
		}
		
	}
}
/*
	showsPhrase
	shows the entire phrase without _

*/
void Wheel::showPhrase(int pNum)
{
	char *temp;
	
	for(int i = 0; i < strlen(fullPhrases.at(pNum)); i ++)
	{
		
		
			temp = &fullPhrases.at(pNum)[i];
			
			S.DrawString(temp,i+5,10,BLUE,BLACK);
		
		
	}
}
/*
		playRound
		Does most of the work calling other helper functions 
		1)checks if the player wants to spin or guess
		->if they want to guess call the checkPhrase function and see if they are right
		->if the want to spin, generate the number then call spinWheel then
		prompt the user to what the letter they would like to guess
			*check if its a vowel and make sure they have money to guess it
			*call inPhrase then add or subtract points depending on letter and correctness
			*set the turn
		->check if its solved 
			*play another round if true
			*else go to the next turn


*/
void Wheel::playRound(int players,int puzzleNum)
{
	bool solved = false;
	int points = 1;
	R.setRange(9,-1);//setting the range of the random number generator
	bool spin;//does the player want to spin
	char *message = " lost Thier Turn";
	char choice[2];//choice of whether to spin or not
	char guess;
	bool vowels;//are vowels able to be guess
	bool vowelGuess;
	hidePhrase(puzzleNum);
	drawTurnPtr(turn);
	do
	{
		vowels = false;
		vowelGuess = false;
		points = -1;
		spin = true;
		S.DrawString("enter 0 - 9 to spin A-Z to guess the phrase" ,0,18);
		S.GetStr(65,18,choice,1,"~",true);
		clearMenu();
		//if they want to guess check the guess
		if(!isdigit(choice[0]))
		{
		spin = false;
		solved = checkPhrase(puzzleNum,getTurn());
			if(!solved)
			{
				Beep(750, 500); 
				Beep(750, 500); 
				Beep(750, 500); 
				clearTurnPtr(turn);
				setTurn((turn%getNumPlayers()+1 ));
			}
		}
		//get the number from the random # generator and spin the wheel
		else
		{
			
		
		points = R.fnRand();
		spinWheel(points);
			if(points < getRoundScore(turn))
			{
				vowels = true;
			}
		}
		//check if the player can guess
		if(points != 0 && spin)
		{
			
			guess = DrawMenu();
			//if they dont have the money for a vowel make them guess again
			while((guess == 'A'|| guess == 'E'|| guess == 'I'|| guess == 'O'|| guess == 'U'|| guess == 'Y') && !vowels)
			{
				Beep(500,500);
				S.GotoXY(0,19);
				cout<<"cannot buy vowel ";
				guess = DrawMenu();
				for(int i = 0; i < 20; i++)
				{
					S.ClearScreenPos(i,19);
				}
				

			}
			if((guess == 'A'|| guess == 'E'|| guess == 'I'|| guess == 'O'|| guess == 'U'|| guess == 'Y'))
			{
				vowelGuess = true;
			}
			//check if its there
			inPhrase(guess,puzzleNum,points,vowelGuess);
			S.Delay();
			clearMenu();
			
			
		}
		//player lost their turn switch the player and tell them they lost their turn
		else if(points == 0)
		{
			
			S.GotoXY(0,19);
			S.SetFgColor(turn+1);
			cout<<names.at(turn)<<" lost their turn";
			S.SetFgColor(WHITE);
			S.Delay();
			clearMessage();
			clearTurnPtr(turn);
			setTurn((turn%getNumPlayers()+1 ));//changes player
		}
		drawTurnPtr(turn);
	}
	while(!solved);
	//updates the score for the rounds to keep them update 
	updateScore(turn,getScore(turn)+100+getRoundScore(turn));
	//settting the next turn for the next round
	setPrevWinner(turn);
	showPhrase(puzzleNum);
	S.Delay();
	//all below is reseting the round
	resetBank();
	showBank();
	clearPhrase(puzzleNum);
	clearRoundScores();
}
/*
	inPhrase
	checks if the guess of the letter is in the phrase
	and adds or subtracts appriotely 



*/
void Wheel::inPhrase(char guess, int boardNum,int points,bool vowel)
{
	
	
	bool found = false;
	int count = 0;
	
	
		
			//goes through looking for the guess
			for(int i = 0; i < strlen(fullPhrases.at(boardNum)) && wBank[(int)guess - 65][0] != 1; i ++)
			{
			
				if(guess == fullPhrases.at(boardNum)[i])
				{
					found = true;
					changeBoard(i,boardNum);
					count++;
					
					
				}
				
			}
			if(!vowel && found)
			{
			addPoint(points,getTurn(),count); 
			}
			if(vowel && found)
					{
						subPoint(points,getTurn());
					}
		//if its not found subtract the score
		if(!found)
		{

				clearTurnPtr(turn);
				Beep(750, 500); 
				Beep(750, 500); 
				Beep(750, 500);
				subPoint(points,getTurn());
				setTurn((turn%getNumPlayers()+1 ));
		}
		//makes the bank know if the letter was used
		wBank[(int)guess - 65][0] = 1;
		showBank();
	
	
}
/*
	checkPhrase 
	checks if the user is correct or not

*/
bool Wheel::checkPhrase(int boardNum, int plyer)
{
	int length = strlen(fullPhrases.at(boardNum))+1;
	char guess[68];
	bool correct = true;
	
	char *guessPrompt = "Please enter your guess for the phrase";
	S.DrawString(guessPrompt,0,18);//prompt to get the guess
	S.GetStr(0,19,guess,length,"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@",true);//sets the size 
	//depening on the length of the board
	for(int i = 0; i < strlen(fullPhrases.at(boardNum)); i ++)
	{
			if(guess[i] != fullPhrases.at(boardNum)[i])
			{
				
				correct = false;
				break;
			}
	}
	for(int i = 0; i < length; i ++)
	{
		S.DrawString(" ",i,19);
	}
	
	
	return correct;
}
//draws the new board
void Wheel::changeBoard(int pos,int boardNum)
{
	
	char temp[2] = {fullPhrases.at(boardNum)[pos]};
	
	S.DrawString(temp,pos+5,10,WHITE,BLACK);
}
//clears the temporary rounds scores
void Wheel::clearRoundScores()
{
	for(int i = 1; i <= getNumPlayers(); i ++)
	{
		roundScores.at(i) = 0;
		for(int x = 1; x < 4; x ++) 
		{
			S.GotoXY(i*15+x,16);
			cout<<" ";
		}
		S.GotoXY(i*15,16);
		cout<<getRoundScore(i);
	}
}
int Wheel::getNumPlayers()
{
	return nbrPlayers;
}
void Wheel::setNumPlayers(int players)
{
	nbrPlayers = players;
}

void Wheel::endGame()
{
	S.Box(2,3,7,7,BLUE);
}
//resets the wordBank so all can be used
void Wheel::resetBank()
{
	for(int i = 0; i < 26; i ++)
	{
		
		wBank[i][0] = 0;//0 = not used
	}
}
void Wheel::showBank()
{
	int y = 0;//y is just to hold the y position
	int x = 0;
	bool  used = false;
	
	for(int i = 0; i < 26; i++)
	{
		S.GotoXY(0,0);
		
		if(wBank[i][0])
		{
			S.SetBkColor(RED);

		}
		else
		{
			S.SetBkColor(BLACK);
		}
			if(i <= 12)
			{
				S.GotoXY(i+15,1);
				cout<<(char)wBank[i][1];

			}
			else
			{
				S.GotoXY(i+2,2);
				cout<<(char)wBank[i][1];
			}
		
	}
	S.SetBkColor(BLACK);
}
//adds the points to the correct person
void Wheel::addPoint(int points,int playerTurn,int count)
{
	

	roundScores.at(playerTurn) += (points*count);
	//clearing the prev score
	for(int i = 1; i < 4; i ++)
	{
		S.GotoXY(playerTurn*15+i,16);
		cout<<" ";
	}
	S.GotoXY(playerTurn*15,16);
	cout<<roundScores.at(playerTurn);
	
}
//subtract from the correct person score
void Wheel::subPoint(int points,int playerTurn)
{
	roundScores.at(playerTurn) -= points;
	for(int i = 1; i < 4; i ++)
	{
		S.GotoXY(playerTurn*15+i,16);
		cout<<" ";
	}
	S.GotoXY(playerTurn*15,16);
	cout<<roundScores.at(playerTurn);
}
//clears the score
void Wheel::clearPhrase(int numBoard)
{
	for(int i = 0; i < strlen(fullPhrases.at(numBoard)); i ++)
	{
		
			S.DrawString(" ",i+5,10,BLUE,BLACK);
	}

}
char Wheel::DrawMenu()
{
	char *menuPrompt = "enter a character A-Z to guess";
	
	char choice[2];
	S.DrawString(menuPrompt,0,18);
	
	S.GetStr(65,18,choice,1,"@",true);


		return choice[0];
	
}
void Wheel::clearMenu()
{
	for(int i = 0; i < 66; i ++)
	{
		S.DrawString(" ",i,18,BLUE,BLACK);
	}

}
void Wheel::clearMessage()
{
	for(int i = 0; i < 30; i ++)
	{
		S.DrawString(" ",i,19);
	}
}
/*
	spinWheel
	displays what looks like to be a spinning wheel on the screen

*/
void Wheel::spinWheel(int num)
{
	
	int n = 0;
	int row = 1;
	int adder = 1;
	int times = 0;
	bool fast = true;//stays in the loop as long as the below are true
	bool medium = true;
	bool slow = true;
	
	while(fast && times < 30)
	{
		
		if(row > 3)	
		{
			row = 1;
		}
		if(n > 9)
		{
			n = 0;
			
		}
		S.SetFgColor(LTGREEN);
		S.GotoXY(45,row);
		cout<<"-----"<<n%10<<"-----"<<endl;
		row++;

		S.SetFgColor(BLUE);
		S.GotoXY(45,row);
		cout<<"---->"<<(n + 1)%10<<"<----"<<endl;
		row++;

		S.SetFgColor(FUSCIA);
		S.GotoXY(45,row);
		cout<<"-----"<<(n + 2)%10<<"-----"<<endl;
		row++;

		S.SetFgColor(LTGREEN);
		n++;
		Sleep(100);
		times ++;
	}
	times = 0;
	while(medium && times < 10)
	{
		
		if(row > 3)	
		{
			row = 1;
		}
		if(n > 9)
		{
			n = 0;
			
		}
		if((n+1)%10 == num && times < 3)
		{
			medium = false;
			
		}
		S.SetFgColor(LTGREEN);
		S.GotoXY(45,row);
		cout<<"-----"<<n%10<<"-----"<<endl;
		row++;
		S.SetFgColor(BLUE);
		S.GotoXY(45,row);
		cout<<"---->"<<(n + 1)%10<<"<----"<<endl;
		row++;

		S.SetFgColor(FUSCIA);
		S.GotoXY(45,row);
		cout<<"-----"<<(n + 2)%10<<"-----"<<endl;
		row++;

		S.SetFgColor(LTGREEN);
		n++;
		Sleep(500);
		times ++;
	}
	times = 0;
	while(slow)
	{
		
		if(row > 3)	
		{
			row = 1;
		}
		if(n > 9)
		{
			n = 0;
			
		}
		if((n+1)%10 == num)
		{
			slow = false;
			
		}
		S.SetFgColor(LTGREEN);
		S.GotoXY(45,row);
		cout<<"-----"<<n%10<<"-----"<<endl;
		row++;

		S.SetFgColor(BLUE);
		S.GotoXY(45,row);
		cout<<"---->"<<(n + 1)%10<<"<----"<<endl;
		row++;

		S.SetFgColor(FUSCIA);
		S.GotoXY(45,row);
		cout<<"-----"<<(n + 2)%10<<"-----"<<endl;
		row++;

		S.SetFgColor(LTGREEN);
		n++;
		Sleep(700);
		times ++;
	}
	times = 0;
	while(times < 10)
	{
		
		if(row > 3)	
		{
			row = 1;
		}
		if(n > 9)
		{
			n = 0;
			
		}
		
		S.SetFgColor(LTGREEN);
		S.GotoXY(45,row);
		cout<<"-----"<<n%10<<"-----"<<endl;
		row++;
		
		S.SetFgColor(BLUE);
		S.GotoXY(45,row);
		cout<<"---->"<<(n + 1)%10<<"<----"<<endl;
		row++;

		S.SetFgColor(FUSCIA);
		S.GotoXY(45,row);
		cout<<"-----"<<(n + 2)%10<<"-----"<<endl;
		row++;
		S.SetFgColor(LTGREEN);
		n++;
		times ++;
	}
		
		S.SetFgColor(WHITE);
	

}
/*
	showTotalScores
	draws the upTodate score
	during each round so the players know where they stand

*/
void Wheel::showTotalScores()
{
	S.GotoXY(59,0);
	cout<<"------totals-------";
	for(int i = 1; i <= getNumPlayers(); i++)
	{
		S.SetFgColor(i+1);
	S.GotoXY(57,i);
	cout<<"<>player "<<i<< "  $" <<getScore(i);
	}

	S.SetFgColor(WHITE);
}
/*
	drawTurnPtr
	takes in whos turn it is and points who it is

*/
void Wheel::drawTurnPtr(int turn)
{
	S.SetFgColor(turn+1);
	S.DrawString("--->",(15*turn)-5,15);
	S.SetFgColor(WHITE);
}
/*
	clearTurnPtr
	gets rid of the ---> from the last player


*/
void Wheel::clearTurnPtr(int turn)
{
	S.SetFgColor(turn+1);
	S.DrawString("    ",(15*turn)-5,15);
	S.SetFgColor(WHITE);
}
/*

	gameOver
	clears the screen and calls rankPlayers 
	then checks if the user wants to play again

*/
void Wheel::gameOver(int nbrPlayers)
{
	S.ClearScreen();
	S.GotoXY(40,10);
	int *aryPtr;
	int places [5];
	char playAgain[2];
	for(int i =1; i <= nbrPlayers; i ++)
	{
		places[i] = getScore(i);
	}
	aryPtr = places;
	rankPlayers(aryPtr,nbrPlayers);
	S.GotoXY(40,18);
	cout<<"Would you like to play again? y/n";
	S.GetStr(40,19,playAgain,1,"@",true);
	if(playAgain[0] == 'Y')
	{
		S.ClearScreen();
		playGame(nbrPlayers);
	}
	
}
/*
	rank uses bubble sort to show the rankings at the end of the game

*/
void Wheel::rankPlayers(int* ptr,int nbrPlayers)
{
	int *plyerPtr;
	int spot[5] = {-1,1,2,3,4};
	plyerPtr = spot;
	for(int i = 1; i <= nbrPlayers; i++)
    {
        for(int j = 1; j <= nbrPlayers-1; j++)
        {
            if(*(ptr+j) < *(ptr+j+1))
            {
                int temp = *(ptr+j);
                *(ptr+j) = *(ptr+j+1);
                *(ptr+j+1) = temp;
				temp = *(plyerPtr+j);
                *(plyerPtr+j) = *(plyerPtr+j+1);
                *(plyerPtr+j+1) = temp;
            }
        }
    } 

	for(int i = 1; i <= nbrPlayers; i++)
	{
		S.GotoXY(40,i+10);
		S.SetColor(i+1);
		cout <<"<"<<i<<"> ---->"<<*(plyerPtr+i)<<" "<<*(ptr+i) << endl;
		S.SetColor(WHITE);
		setPrevWinner(turn);
	}
	
}

	