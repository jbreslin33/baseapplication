#include "questionAttempts.h"
#include "../tdreamsock/dreamSockLog.h"
#include "../../utility/utility.h"

//postgresql
#include <stdio.h>
#include <postgresql/libpq-fe.h>

QuestionAttempts::QuestionAttempts()
{
	id = 0;
	question_id = 0;
	answer = "";
	answer_attempt_time = 0.0;
	answer_time = 0;
	user_id = 0;
	mUtility = new Utility();
}

QuestionAttempts::QuestionAttempts(int i, int q, std::string a, double aat, int at, int uid)
{
	id = i;
	question_id = q;
	answer = a;
	answer_attempt_time = aat;
	answer_time = at;
	user_id = uid;

	//lets try a db insert...
	dbInsert();
}

QuestionAttempts::~QuestionAttempts()
{
}

void QuestionAttempts::dbInsert()
{
 	PGconn          *conn;
        PGresult        *res;
        int             rec_count;
        int             row;
        int             col;
        conn = PQconnectdb("dbname=abcandyou host=localhost user=postgres password=mibesfat");

       	//std::string query = "select * from users WHERE username != 'root' ORDER BY id LIMIT 3";
	std::string query = "insert into questions_attempts (question_id, answer, answer_time, user_id) values ("; 
	query.append(mUtility->intToString(question_id));
	query.append(",'");
	query.append(answer);
	query.append("',");
	query.append(mUtility->intToString(answer_time));
	query.append(",");
	query.append(mUtility->intToString(user_id));
	query.append(")");

        //query.append(mUtility->intToString(mNumberOfClients));
        const char * q = query.c_str();
	LogString("q:%s",q);
        res = PQexec(conn,q);

        //res = PQexec(conn,"select * from users WHERE username != 'root' ORDER BY id LIMIT 4");
        if (PQresultStatus(res) != PGRES_TUPLES_OK)
        {
                puts("We did not get any data!");
        }
        rec_count = PQntuples(res);
        printf("We received %d records from user table.\n", rec_count);

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
