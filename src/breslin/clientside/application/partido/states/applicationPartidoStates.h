#ifndef APPLICATIONPARTIDOSTATES_H
#define APPLICATIONPARTIDOSTATES_H

#include "../../../../fsm/state.h"

class Application;
/******************************************************
	         GLOBAL_APPLICATION
********************************************************/
/*
class GLOBAL_APPLICATION : public State<ApplicationBreslin>
{
private:
  GLOBAL_APPLICATION(){}
public:
  static GLOBAL_APPLICATION* Instance();
  void enter  (ApplicationBreslin* applicationBreslin);
  void execute(ApplicationBreslin* applicationBreslin);
  void exit   (ApplicationBreslin* applicationBreslin);
};


/******************************************************
*				NORMAL
********************************************************/
class INIT_APPLICATION : public State<ApplicationBreslin>
{
private:
  INIT_APPLICATION(){}
public:
  static INIT_APPLICATION* Instance();
  void enter  (ApplicationBreslin* applicationBreslin);
  void execute(ApplicationBreslin* applicationBreslin);
  void exit   (ApplicationBreslin* applicationBreslin);
};

/******************************************************
*				NORMAL
********************************************************/
class LOGIN_APPLICATION : public State<ApplicationBreslin>
{
private:
  LOGIN_APPLICATION(){}
public:
  static LOGIN_APPLICATION* Instance();
  void enter  (ApplicationBreslin* applicationBreslin);
  void execute(ApplicationBreslin* applicationBreslin);
  void exit   (ApplicationBreslin* applicationBreslin);
};

/******************************************************
*			MAIN_APPLICATION	
********************************************************/
class MAIN_APPLICATION : public State<ApplicationBreslin>
{
private:
  MAIN_APPLICATION(){}
public:
  static MAIN_APPLICATION* Instance();
  void enter  (ApplicationBreslin* applicationBreslin);
  void execute(ApplicationBreslin* applicationBreslin);
  void exit   (ApplicationBreslin* applicationBreslin);
};

/******************************************************
*                       PLAY_APPLICATION
********************************************************/
class PLAY_APPLICATION : public State<ApplicationBreslin>
{
private:
  PLAY_APPLICATION(){}
public:
  static PLAY_APPLICATION* Instance();
  void enter  (ApplicationBreslin* applicationBreslin);
  void execute(ApplicationBreslin* applicationBreslin);
  void exit   (ApplicationBreslin* applicationBreslin);
};
*/
#endif
