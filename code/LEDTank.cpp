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
  case STATE_SEARCH:
    
    break;
  case STATE_INIT:
    
    break;
  case STATE_WAIT:
    time++;
controller->changeDriveMode(STOP, 0);
    break;
  case STATE_TURN:
    controller->getPosition(&distance, &angle);
    break;
  case STATE_BACK:
    
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
    cnt = 0;
angle = 0.0;
distance = 0.0;
trycount=0;
ranging=0.0;

    break;
  case STATE_FORWARD:

    if(((event & E_CHANGE_DISTANCE) != 0) && (distance > 80)){

      // exit
      state = STATE_SEARCH;

      //action
      

      this->_state = STATE_WAIT;

      //entry
      printf("[WAIT]\n");
time = 0;
    }
    else

    if(((event & E_REACH) != 0) ){

      // exit
      state = STATE_SEARCH;

      //action
      

      this->_state = STATE_TURN;

      //entry
      printf("[TURN]\n");
controller->reset();
controller->changeDriveMode(CW, 100);
    }
    break;
  case STATE_SEARCH:

    if(((event & TRUE
) != 0) ){

      // exit
      trycount++;
state = STATE_FORWARD;

      //action
      

      this->_state = STATE_WAIT;

      //entry
      printf("[WAIT]\n");
time = 0;
    }
    break;
  case STATE_INIT:

    if(TRUE ){

      // exit
      

      //action
      

      this->_state = STATE_BACK;

      //entry
      printf("[BACK]\n");
controller->changeDriveMode(BACKWARD,80);
    }
    break;
  case STATE_WAIT:

    if(TRUE && ((state == STATE_FORWARD)
&& (time >=10))){

      // exit
      

      //action
      

      this->_state = STATE_FORWARD;

      //entry
      printf("[FORWARD]\n");
controller->reset();
controller->changeDriveMode(FORWARD, 80);
    }
    else

    if(TRUE && ((state == STATE_SEARCH)
&&(time >= 10))){

      // exit
      

      //action
      

      this->_state = STATE_SEARCH;

      //entry
      printf("[TEMP]\n");
    }
    break;
  case STATE_TURN:

    if(((event & E_CHANGE_ANGLE) != 0) && (angle > 180.0)){

      // exit
      

      //action
      

      this->_state = STATE_FORWARD;

      //entry
      printf("[FORWARD]\n");
controller->reset();
controller->changeDriveMode(FORWARD, 80);
    }
    break;
  case STATE_BACK:

    if(((event & E_REACH) != 0) ){

      // exit
      state = STATE_FORWARD;

      //action
      

      this->_state = STATE_WAIT;

      //entry
      printf("[WAIT]\n");
time = 0;
    }
    break;
  default:
    break;
  }
}
