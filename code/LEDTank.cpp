#include <stdio.h>
#include "Event.h"
#include "LEDTank.h"

LEDTank::LEDTank(Controller *controller){
  this->_state = _STATE_INITIAL;

  this->controller = controller;

}

void LEDTank::execState(){
  switch(this->_state){
  case STATE_FORWARD:
    controller->getPosition(&distance, &angle);
    break;
  case STATE_INIT:
    
    break;
  case STATE_STOP:
    
    break;
  default:
    break;
  }
}

void LEDTank::doTransition(unsigned long event){
  this->_beforeState = this->_state;

  switch(this->_state){
  case _STATE_INITIAL:
    this->_state = STATE_INIT;

    //entry
    angle = 0.0;
distance = 0.0;

    break;
  case STATE_FORWARD:

    if(((event & E_CHANGE_DISTANCE) != 0) && (distance > 100.0)){

      // exit
      

      //action
      

      this->_state = STATE_STOP;

      //entry
      printf("[STOP]\n");
controller->changeDriveMode(STOP, 0);
    }
    break;
  case STATE_INIT:

    if(TRUE ){

      // exit
      

      //action
      

      this->_state = STATE_FORWARD;

      //entry
      printf("[FORWARD]\n");
state = STATE_FORWARD;
controller->reset();
controller->changeDriveMode(FORWARD, 40);
cnt++;
    }
    break;
  case STATE_STOP:
    break;
  default:
    break;
  }
}
