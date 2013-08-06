#ifndef QUESTIONATTEMPTS_H
#define QUESTIONATTEMPTS_H

#include <string>

class QuestionAttempts 
{
public:
	
QuestionAttempts();
QuestionAttempts(std::string i, std::string q, std::string a, std::string aat, std::string at, std::string uid);
virtual ~QuestionAttempts();

std::string id;
std::string question_id;
std::string answer; 
std::string answer_attempt_time; 
std::string answer_time; 
std::string user_id; 

void set(std::string i, std::string q, std::string a, std::string aat, std::string at, std::string uid);

};

#endif
