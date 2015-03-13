#include "Games.h"
#include "Checker.h"
#include "CFour.h"
#include <iostream>


void Checker:: setState(int newState)
{
	state = newState; 
}
int Checker:: getState()
{
	return  state;
}
void Checker:: draw(CScreen S, int x, int y )
{
	switch (state) 
	{
	case 0 : S.Box((x*5)+1, (y*3)+2, (x*5)+5, (y*3)+4, GREEN);
	break;
	case 1 : S.Box((x*5)+1, (y*3)+2, (x*5)+5, (y*3)+4, AQUA);
	break;
	case 2 : S.Box((x*5)+1, (y*3)+2, (x*5)+5, (y*3)+4, WHITE);
	break;
	}
}
