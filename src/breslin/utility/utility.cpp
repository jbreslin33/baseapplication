#include "utility.h"
using namespace std;

#include <sstream>
#include <string> // this should be already included in <sstream>

//log
#include "../clientside/tdreamsock/dreamSockLog.h"

//random
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

//time
#include <sys/time.h>

Utility::Utility()
{
}

Utility::~Utility()
{
}

std::string Utility::intToString(int i)
{
        ostringstream ss;
        ss << i;
	std::string s = ss.str();
	return s;
}
int Utility::getRandomNumber(int total, int seed)
{
	if (seed)
	{
	}
	else
	{

		struct timeval tp;
        	struct timezone tzp;
        	static int basetime;

        	gettimeofday(&tp, &tzp);

        	if(!basetime)
        	{
                	basetime = tp.tv_sec;
                	seed = tp.tv_usec / 1000;
        	}
		else
		{

        		seed = (tp.tv_sec - basetime) * 1000 + tp.tv_usec / 1000;
		}
	}
	
	srand ( (short)time(NULL) + seed);        /* initialize random seed: */
        int randomNumber = rand() % total;  //assign random key 0-16 or is it 1-16 or 0-15?
	return randomNumber;
}
