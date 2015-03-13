#ifndef CHECKER_H
#define CHECKER_H

#include "Games.h"


class Checker
{ 
        int state;  // 0 - RED, 1-BLACK or 2- WHITE (empty)

    public:
		Checker(){state = 2;}
        void setState(int); 
		int getState();
        void draw( CScreen S, int x, int y); // draws itself
    };
#endif