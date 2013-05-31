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
	srand ( (short)time(NULL) + seed);        /* initialize random seed: */
        int randomNumber = rand() % total;  //assign random key 0-16 or is it 1-16 or 0-15?
	return randomNumber;
}
