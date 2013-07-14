#ifndef CLIENTPARTIDOSTATES_H
#define CLIENTPARTIDOSTATES_H

#include "../../../../../fsm/state.h"

class ClientPartido;


/*******************************
*      GlobalClientPartido 
******************************/

class GlobalClientPartido : public State<ClientPartido>
{
private:
  GlobalClientPartido(){}
public:
  static GlobalClientPartido* Instance();
  void enter  (ClientPartido* clientPartido);
  void execute(ClientPartido* clientPartido);
  void exit   (ClientPartido* clientPartido);
  bool onLetter(ClientPartido* clientPartido, Letter* letter);
};

#endif
