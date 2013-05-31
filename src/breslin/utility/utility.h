#ifndef UTILITY_H
#define UTILITY_H

#include <string>

class Utility 
{

public:
Utility();
~Utility();

std::string intToString(int i);
int getRandomNumber(int total, int seed);
};
#endif
