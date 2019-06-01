#ifndef __LEDTank___
#define __LEDTank___

#include "Controller.h"

#ifdef EXPERIMENTAL_USE
#define _STATE_INITIAL 0x00000000
#define STATE_FORWARD ((unsigned long)1)
#define STATE_INIT ((unsigned long)2)
#define STATE_STOP ((unsigned long)3)
#define STATE_LEFT ((unsigned long)4)
#define STATE_RIGHT ((unsigned long)5)
#define STATE_BACKWARD ((unsigned long)6)
#endif
#ifndef EXPERIMENTAL_USE
#define _STATE_INITIAL 0x00000000
#define STATE_FORWARD ((unsigned long)1)
#define STATE_STOP ((unsigned long)2)
#define STATE_TURN ((unsigned long)3)
#endif
class Controller;

class LEDTank_{
 public:
  LEDTank_(Controller *controller);
#ifndef EXPERIMENTAL_USE
  void execState();
  void doTransition(unsigned long event);
#endif
#ifdef EXPERIMENTAL_USE
  void execState_for_experiment();
  void doTransition_for_experiment(unsigned long event);
#endif
  unsigned long _state;

 private:
   Controller *controller;
   unsigned long _beforeState;
#ifndef EXPERIMENTAL_USE
  float distance;
  float angle;
#endif
#ifdef EXPERIMENTAL_USE
  float distance;
  float angle;
  int cnt;
  int time;
  int state;
#endif

};

#endif