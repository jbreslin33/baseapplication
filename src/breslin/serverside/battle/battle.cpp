#include "battle.h"

//client
#include "../client/clientPartido.h"

//log
#include "../tdreamsock/dreamSockLog.h"

//shape
#include "../shape/shape.h"

Battle::Battle(Game* game, std::vector<Shape*> shapeVector)
{
	mOver = false;
  
	//add shapes to battle shapeVector
        for (unsigned int i = 0; i < shapeVector.size(); i++)
        {
                mShapeVector.push_back(shapeVector.at(i));
        }

        for (unsigned int i = 0; i < shapeVector.size(); i++)
	{
		if (mShapeVector.at(i)->mClient)
		{
			LogString("id:%d",mShapeVector.at(i)->mClient->mClientID);
		}
	}
}

Battle::~Battle()
{
}

void Battle::processUpdate()
{
	//this is where you should send questions....
	//select * from questions_attempts limit 10;
}
//for inserting when you send question to human client 
//insert into questions_attempts (question_attempt_time_start, question_attempt_time_end, question_id, answer, user_id) values (CURRENT_TIMESTAMP,CURRENT_TIMESTAMP,1,'1',1);


//for when they answer
//update questions_attempts set question_attempt_time_end = CURRENT_TIMESTAMP, answer='13' where id = 1;

//for grabbing questions_attempts joined with questions. for comparing answers....and times...
//select questions.id, questions.question, questions_attempts.answer, questions_attempts.user_id from questions_attempts inner join questions on questions_attempts.question_id=questions.id;

//how bout for just question.id = 1..this is for evaluating each question in order....
 select questions.id, questions.question, questions_attempts.answer, questions_attempts.user_id from questions_attempts inner join questions on questions_attempts.question_id=questions.id where questions.id = 1;

//here you can do a subtraction of endtime and start time and name the field
select question_attempt_time_end - question_attempt_time_start as mspp from questions_attempts;

//to find level: did you get any wrong in the last 100 of level 1, if so you are level 1.
//if none wrong in last 100 of level 1 where any of your times or the avg above 2secs? if so you are level 1.

//if not you may be level 2. proceed to level 2 check which is same as level 1 check.


//this is for question 1 id and does a diff on the times
select questions.id, questions.question, questions_attempts.answer, questions_attempts.question_attempt_time_end - questions_attempts.question_attempt_time_start as ms_per_problem, questions_attempts.user_id from questions_attempts inner join questions on questions_attempts.question_id=questions.id where questions.id = 1;

//a sum of total time on problems
 select sum(question_attempt_time_end - question_attempt_time_start) from questions_attempts;

//here is seconds per problem
select (sum(question_attempt_time_end - question_attempt_time_start))/2 as seconds_per_problem from questions_attempts;


// select questions.id, questions.question, questions_attempts.answer, questions_attempts.user_id from questions_attempts inner join questions on questions_attempts.question_id=questions.id where questions.id=1 order by questions_attempts.question_attempt_time_start;


//this gets you question_attempts from a particular questions and particular user_id
select questions.id, questions.question, questions_attempts.answer, questions_attempts.user_id from questions_attempts inner join questions on questions_attempts.question_id=questions.id where questions.id=1 and questions_attempts.user_id = 2 order by questions_attempts.question_attempt_time_start;
