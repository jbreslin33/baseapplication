#ifndef ROTATIONSTATES_H
#define ROTATIONSTATES_H
#include "rotationState.h"

class Rotation;

class Normal_Rotation : public RotationState
{
private:
  Normal_Rotation(){}
public:
  static Normal_Rotation* Instance();
  void enter  (Rotation* rotation);
  void execute(Rotation* rotation);
  void exit   (Rotation* rotation);
};

class No_Rotation : public RotationState
{
private:
  No_Rotation(){}
public:
  static No_Rotation* Instance();
  void enter  (Rotation* rotation);
  void execute(Rotation* rotation);
  void exit   (Rotation* rotation);
};

class Accelerate_Rotation : public RotationState
{
private:
  Accelerate_Rotation(){}
public:
  static Accelerate_Rotation* Instance();
  void enter  (Rotation* rotation);
  void execute(Rotation* rotation);
  void exit   (Rotation* rotation);
};

class Decelerate_Rotation : public RotationState
{
private:
  Decelerate_Rotation(){}
public:
  static Decelerate_Rotation* Instance();
  void enter  (Rotation* rotation);
  void execute(Rotation* rotation);
  void exit   (Rotation* rotation);
};

#endif