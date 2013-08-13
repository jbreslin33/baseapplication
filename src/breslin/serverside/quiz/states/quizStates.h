#ifndef QUIZSTATES_H
#define QUIZSTATES_H

#include "../../../fsm/state.h"

class Quiz;
struct Telegram;


/*******************************
*      GLOBAL_QUIZ
******************************/

class GLOBAL_QUIZ : public State<Quiz>
{
private:
  GLOBAL_QUIZ(){}
public:
  static GLOBAL_QUIZ* Instance();
  void enter  (Quiz* quiz);
  void execute(Quiz* quiz);
  void exit   (Quiz* quiz);
  bool onLetter(Quiz* quiz, Letter* letter);
};

/*******************************
*      Quiz
******************************/

class INIT_QUIZ : public State<Quiz>
{
private:
  INIT_QUIZ(){}
public:
  static INIT_QUIZ* Instance();
  void enter  (Quiz* quiz);
  void execute(Quiz* quiz);
  void exit   (Quiz* quiz);
  bool onLetter(Quiz* quiz, Letter* letter);
};

class NORMAL_QUIZ : public State<Quiz>
{
private:
  NORMAL_QUIZ(){}
public:
  static NORMAL_QUIZ* Instance();
  void enter  (Quiz* quiz);
  void execute(Quiz* quiz);
  void exit   (Quiz* quiz);
  bool onLetter(Quiz* quiz, Letter* letter);
};

class OVER_QUIZ : public State<Quiz>
{
private:
  OVER_QUIZ(){}
public:
  static OVER_QUIZ* Instance();
  void enter  (Quiz* quiz);
  void execute(Quiz* quiz);
  void exit   (Quiz* quiz);
  bool onLetter(Quiz* quiz, Letter* letter);
};

#endif
