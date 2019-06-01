#ifndef __LEDTank__
#define __LEDTank__

#include "Controller.h"

#define _STATE_INITIAL 0x00000000
#define STATE_FORWARD ((unsigned long)1)
#define STATE_INIT ((unsigned long)2)
#define STATE_STOP ((unsigned long)3)
#define STATE_LEFT ((unsigned long)4)
#define STATE_RIGHT ((unsigned long)5)
#define STATE_BACKWARD ((unsigned long)6)


class Controller;

class LEDTank{
 public:
  LEDTank(Controller *controller);
  void execState();
  void execState_for_experiment();
  void doTransition(unsigned long event);
  void doTransition_for_experiment(unsigned long event);
  unsigned long _state;

 private:
  Controller *controller;

  unsigned long _beforeState;
  float distance;
  float angle;
  int cnt;
  int time;
  int state;
};

#endif
