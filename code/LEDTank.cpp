#include <stdio.h>
#include "Event.h"
#include "LEDTank.h"

LEDTank::LEDTank(Controller *controller){
  this->state = _STATE_INITIAL;
  this->controller = controller;
  this->distance = 0;
  this->angle = 0;
}

#ifndef EXPERIMENTAL_USE
void LEDTank::execState(){
  switch(this->state){
  case STATE_FORWARD:
    controller->getPosition(&distance, &angle);

    break;
  case STATE_STOP:
    
    break;
  case STATE_TURN:
    controller->getPosition(&distance, &angle);
    break;
  default:
    break;
  }
}
void LEDTank::doTransition(unsigned long event){
  this->_beforeState = this->state;

  switch(this->state){
    case _STATE_INITIAL:
      this->state = STATE_STOP;
      controller->reset();

//     //entry
//     controller->changeDriveMode(STOP, 5);
// printf("STOP\n");

    break;
  }
//   case STATE_FORWARD:
//     if(((event & E_CHANGE_ANGLE) != 0) && (this->distance > 10)){
//       // exit
      

//       //action
      

//       this->state = STATE_TURN;

//       //entry
//       controller->changeDriveMode(CW, 5);
// printf("CW\n");
//     }
//     break;
//   case STATE_STOP:
//     if(((event & E_UP) != 0) ){
//       // exit
      

//       //action
      

//       this->state = STATE_FORWARD;

//       //entry
//       controller->changeDriveMode(FORWARD, 5);
// printf("FORWARD\n");
//     }
//     break;
//   case STATE_TURN:
//     if(((event & E_CHANGE_ANGLE) != 0) ){
//       // exit
      

//       //action
      

//       this->state = STATE_FORWARD;

//       //entry
//       controller->changeDriveMode(FORWARD, 5);
// printf("FORWARD\n");
//     }
//     break;
//   default:
//     break;
//   }
}
#endif
#ifdef EXPERIMENTAL_USE
void LEDTank::execState_for_experiment(){
    controller->getPosition(&distance, &angle);
    switch(this->state){
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
        controller->reset();
        controller->changeDriveMode(STOP, 0);

        printf("STOP\n");

        break;
    case STATE_FORWARD:
        if(((event & E_DOWN) != 0) ){
            this->state = STATE_STOP;
            controller->changeDriveMode(STOP, 40);
            printf("STOP\n");
        }
        else if(((event & E_LEFT) != 0) ){
            this->state = STATE_LEFT;
            controller->changeDriveMode(CW, 40);
            printf("LEFT\n");
        }
        else if(((event & E_RIGHT) != 0) ){
            this->state = STATE_RIGHT;
            controller->changeDriveMode(CCW, 40);
            printf("RIGHT\n");
        }
        break;
    case STATE_BACKWARD:
        if(((event & E_RIGHT) != 0) ){
            this->state = STATE_RIGHT;
            controller->changeDriveMode(CCW, 40);
            printf("RIGHT\n");
        }
        else if(((event & E_LEFT) != 0) ){
            this->state = STATE_LEFT;
            controller->changeDriveMode(CW, 40);
            printf("LEFT\n");
        }
        else if(((event & E_UP) != 0) ){
            this->state = STATE_STOP;
            controller->changeDriveMode(STOP, 40);
            printf("STOP\n");
        }
        break;
    case STATE_LEFT:
        if(((event & E_DOWN) != 0) ){
            this->state = STATE_BACKWARD;
            controller->changeDriveMode(BACKWARD, 40);
            printf("BACKWARD\n");
        }
        else if(((event & E_RIGHT) != 0) ){
            this->state = STATE_STOP;
            controller->changeDriveMode(STOP, 40);
            printf("STOP\n");
        }
        break;
    case STATE_RIGHT:
        if(((event & E_DOWN) != 0) ){
            this->state = STATE_BACKWARD;
            controller->changeDriveMode(BACKWARD, 40);
            printf("BACKWARD\n");
        }
        else if(((event & E_LEFT) != 0) ){
            this->state = STATE_STOP;
            controller->changeDriveMode(STOP, 40);
            printf("STOP\n");
        }
        break;
    case STATE_STOP:
        if(((event & E_UP) != 0) ){
            this->state = STATE_FORWARD;
            controller->changeDriveMode(FORWARD, 40);
            printf("FORWARD\n");
        }
        else if(((event & E_DOWN) != 0) ){
            this->state = STATE_BACKWARD;
            controller->changeDriveMode(BACKWARD, 40);
            printf("BACKWARD\n");
        }
        else if(((event & E_RIGHT) != 0) ){
            this->state = STATE_RIGHT;
            controller->changeDriveMode(CCW, 40);
            printf("RIGHT\n");
        }
        else if(((event & E_LEFT) != 0) ){
            this->state = STATE_LEFT;
            controller->changeDriveMode(CW, 40);
            printf("LEFT\n");
        }
        break;
    default:
        break;
    }
}
#endif
