#include "utility.h"
using namespace std;

#include <sstream>
#include <string> // this should be already included in <sstream>

//log
#include "../clientside/tdreamsock/dreamSockLog.h"


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
