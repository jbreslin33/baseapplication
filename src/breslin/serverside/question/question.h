#ifndef QUESTION_H
#define QUESTION_H

#include <string>

class Question 
{
public:
	
Question();
virtual ~Question();

int id;
std::string question;
std::string answer; 
float level_id; 

};

#endif
