#include <stdio.h>
#include "rctank.h"
#include "PreEvent.h"
#include "LEDTank_.h"

LEDTank_::LEDTank_(Position *position){
  this->state = _STATE_INITIAL;

  this->distance = 0;
  this->angle = 0;
  motorL = new DcMotor(5, 6);
  motorR = new DcMotor(13,19);
}

#ifndef EXPERIMENTAL_USE
void LEDTank_::execState(){
  switch(this->state){
  case STATE_FORWARD:
    position->getPosition(&distance, &angle);

    break;
  case STATE_STOP:
    
    break;
  case STATE_TURN:
    position->getPosition(&distance, &angle);
    break;
  default:
    break;
  }
}

void LEDTank_::doTransition(unsigned long event){
  this->beforeState = this->state;

  switch(this->state){
  case _STATE_INITIAL:
    this->state = STATE_STOP;

    //entry
    ChangeDriveMode(STOP, 5);
printf("STOP\n");

    break;  
  case STATE_FORWARD:
    if(((event & E_CHANGE_ANGLE) != 0) && (this->distance > 10)){
      // exit
      

      //action
      

      this->state = STATE_TURN;

      //entry
      ChangeDriveMode(CW, 5);
printf("CW\n");
    }
    break;
  case STATE_STOP:
    if(((event & E_UP) != 0) ){
      // exit
      

      //action
      

      this->state = STATE_FORWARD;

      //entry
      ChangeDriveMode(FORWARD, 5);
printf("FORWARD\n");
    }
    break;
  case STATE_TURN:
    if(((event & E_CHANGE_ANGLE) != 0) ){
      // exit
      

      //action
      

      this->state = STATE_FORWARD;

      //entry
      ChangeDriveMode(FORWARD, 5);
printf("FORWARD\n");
    }
    break;
  default:
    break;
  }
}
#endif

#ifdef EXPERIMENTAL_USE
void LEDTank::execState_for_experiment(){
    controller->getPosition(&distance, &angle);
    switch(this->_state){
    case STATE_FORWARD:
        break;
    case STATE_INIT:
        break;
    case STATE_STOP:
        break;
    case STATE_BACKWARD:
        break;
    case STATE_LEFT:
        break;
    case STATE_RIGHT:
        break;
    default:
        break;
    }
}

//実験用ステートマシン
void LEDTank::doTransition_for_experiment(unsigned long event){
    this->_beforeState = this->state;

    switch(this->state){
    case _STATE_INITIAL:
        this->state = STATE_STOP;

        //entry
        controller->changeDriveMode(STOP, 0);
        printf("STOP
");

        break;
    case STATE_FORWARD:
        if(((event & E_DOWN) != 0) ){
            this->state = STATE_STOP;
            controller->changeDriveMode(STOP, 40);
            printf("STOP
");
        }
        else if(((event & E_LEFT) != 0) ){
            this->state = STATE_LEFT;
            controller->changeDriveMode(CW, 40);
            printf("LEFT
");
        }
        else if(((event & E_RIGHT) != 0) ){
            this->state = STATE_RIGHT;
            controller->changeDriveMode(CCW, 40);
            printf("RIGHT
");
        }
        break;
    case STATE_BACKWARD:
        if(((event & E_RIGHT) != 0) ){
            this->state = STATE_RIGHT;
            controller->changeDriveMode(CCW, 40);
            printf("RIGHT
");
        }
        else if(((event & E_LEFT) != 0) ){
            this->state = STATE_LEFT;
            controller->changeDriveMode(CW, 40);
            printf("LEFT
");
        }
        else if(((event & E_UP) != 0) ){
            this->state = STATE_STOP;
            controller->changeDriveMode(STOP, 40);
            printf("STOP
");
        }
        break;
    case STATE_LEFT:
        if(((event & E_DOWN) != 0) ){
            this->state = STATE_BACKWARD;
            controller->changeDriveMode(BACKWARD, 40);
            printf("BACKWARD
");
        }
        else if(((event & E_RIGHT) != 0) ){
            this->state = STATE_STOP;
            controller->changeDriveMode(STOP, 40);
            printf("STOP
");
        }
        break;
    case STATE_RIGHT:
        if(((event & E_DOWN) != 0) ){
            this->state = STATE_BACKWARD;
            controller->changeDriveMode(BACKWARD, 40);
            printf("BACKWARD
");
        }
        else if(((event & E_LEFT) != 0) ){
            this->state = STATE_STOP;
            controller->changeDriveMode(STOP, 40);
            printf("STOP
");
        }
        break;
    case STATE_STOP:
        if(((event & E_UP) != 0) ){
            this->state = STATE_FORWARD;
            controller->changeDriveMode(FORWARD, 40);
            printf("FORWARD
");
        }
        else if(((event & E_DOWN) != 0) ){
            this->state = STATE_BACKWARD;
            controller->changeDriveMode(BACKWARD, 40);
            printf("BACKWARD
");
        }
        else if(((event & E_RIGHT) != 0) ){
            this->state = STATE_RIGHT;
            controller->changeDriveMode(CCW, 40);
            printf("RIGHT
");
        }
        else if(((event & E_LEFT) != 0) ){
            this->state = STATE_LEFT;
            controller->changeDriveMode(CW, 40);
            printf("LEFT
");
        }
        break;
    default:
        break;
    }
}
#ifdef EXPERIMENTAL_USE