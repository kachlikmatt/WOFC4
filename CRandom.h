#include<ctime>
#include<cstdlib>
 
class CRandom
{   int iLb, iUb;      // upper/lower bound -default 0, 32000
     int iLastVal;     // last random # generated
 
  public:                                                 // all inline functions
     CRandom(int iLo=0, int iHi=3200):iLb(iLo), iUb(iHi), iLastVal(-1) 
         {srand(time(NULL));}
 
     int fnRand() // return a random int #
        {return iLastVal=(rand() % (iUb - iLb)) + iLb+1;} 
       
     int fnGetLast()    // return the last # generated
       { return iLastVal;} 
 
     void setRange( int iHi, int iLo) // set upper/lower bound
       {iLb = iLo; iUb = iHi;} 
};