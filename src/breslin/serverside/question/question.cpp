#include "question.h"

Question::Question()
{
	id = 0;
	question = "";
	answer = "";
	level_id = 0.0f;

}

Question::~Question()
{
}

void Question::set(int i, std::string q, std::string a, float l)
{
	id = i;
	question = q;
	answer = a;
	level_id = l;
} 
