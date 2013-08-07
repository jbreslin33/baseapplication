#include "questionAttempts.h"
#include "../tdreamsock/dreamSockLog.h"

QuestionAttempts::QuestionAttempts()
{
	id = 0;
	question_id = 0;
	answer = "";
	answer_attempt_time = 0.0;
	answer_time = 0;
	user_id = 0;
}

QuestionAttempts::QuestionAttempts(int i, int q, std::string a, double aat, int at, int uid)
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

void QuestionAttempts::set(int i, int q, std::string a, double aat, int at, int uid)
{
	id = i;
	question_id = q;
	answer = a;
	answer_attempt_time = aat;
	answer_time = at;
	user_id = uid;
} 
