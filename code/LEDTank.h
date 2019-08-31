#ifndef __LEDTank__
#define __LEDTank__

#include "Controller.h"

#define _STATE_INITIAL 0x00000000
#ifdef EXPERIMENTAL_USE
#define STATE_FORWARD ((unsigned long)1)
#define STATE_INIT ((unsigned long)2)
#define STATE_STOP ((unsigned long)3)
#define STATE_LEFT ((unsigned long)4)
#define STATE_RIGHT ((unsigned long)5)
#define STATE_BACKWARD ((unsigned long)6)

#else
#define _STATE_INITIAL 0x00000000
#define STATE_SEARCH ((unsigned long)1)
#define STATE_STOP ((unsigned long)2)
#define STATE_CLOSE ((unsigned long)3)
#define STATE_HOLD ((unsigned long)4)
#define STATE_PUSH ((unsigned long)5)
#define STATE_PLACE ((unsigned long)6)
#define STATE_RETURN ((unsigned long)7)
#endif
class PreController;

class LEDTank{
 public:
  LEDTank(Controller *controller);
#ifdef EXPERIMENTAL_USE
  void execState_for_experiment();
  void doTransition_for_experiment(unsigned long event);
#else
  void execState();
  void doTransition(unsigned long event);
#endif
  unsigned long _state;

 private:
   Controller *controller;
   unsigned long _beforeState;
   unsigned long state;
#ifdef EXPERIMENTAL_USE
  float distance;
  float angle;
  int cnt;
  int time;

#else
  float distance;
  float angle;
  float rangingDistance;
  bool lineL;
  bool lineC;
  bool lineR;
#endif

};

#endif