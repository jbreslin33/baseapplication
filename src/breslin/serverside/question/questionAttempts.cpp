#include "questionAttempts.h"

QuestionAttempts::QuestionAttempts()
{
	id = "";
	question_id = "";
	answer = "";
	answer_attempt_time = "";
	answer_time = "";
	user_id = "";
}

QuestionAttempts::QuestionAttempts(std::string i, std::string q, std::string a, std::string aat, std::string at, std::string uid)
{
	id = i;
	question_id = q;
	answer = a;
	answer_attempt_time = aat;
	answer_time = at;
	user_id = uid;
}

QuestionAttempts::~QuestionAttempts()
{
}

void QuestionAttempts::set(std::string i, std::string q, std::string a, std::string aat, std::string at, std::string uid)
{
	id = i;
	question_id = q;
	answer = a;
	answer_attempt_time = aat;
	answer_time = at;
	user_id = uid;
} 
