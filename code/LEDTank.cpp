#include <stdio.h>
#include "Event.h"
#include "LEDTank.h"
#include <unistd.h>

LEDTank::LEDTank(Controller *controller){
  this->state = _STATE_INITIAL;
  this->controller = controller;

#ifdef EXPERIMENTAL_USE
  this->distance = 0;
  this->angle = 0;
#else

  this->distance = 0;
  this->angle = 0;
  this->rangingDistance = 0;
  this->lineL = 0;
  this->lineC = 0;
  this->lineR = 0;
#endif
}
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

#define OUTPUT_ 80
void LEDTank::doTransition_for_experiment(unsigned long event){
    this->_beforeState = this->state;

    switch(this->state){
    case _STATE_INITIAL:
        this->state = STATE_STOP;

        //entry
        controller->positionReset();
        controller->changeDriveMode(STOP, 0);

        printf("STOP\n");

        break;
    case STATE_FORWARD:
        if(((event & E_DOWN) != 0) ){
            this->state = STATE_STOP;
            controller->changeDriveMode(STOP, OUTPUT_);
            printf("STOP\n");
        }
        else if(((event & E_LEFT) != 0) ){
            this->state = STATE_LEFT;
            controller->changeDriveMode(CW, OUTPUT_);
            printf("LEFT\n");
        }
        else if(((event & E_RIGHT) != 0) ){
            this->state = STATE_RIGHT;
            controller->changeDriveMode(CCW, OUTPUT_);
            printf("RIGHT\n");
        }
        break;
    case STATE_BACKWARD:
        if(((event & E_RIGHT) != 0) ){
            this->state = STATE_RIGHT;
            controller->changeDriveMode(CCW, OUTPUT_);
            printf("RIGHT\n");
        }
        else if(((event & E_LEFT) != 0) ){
            this->state = STATE_LEFT;
            controller->changeDriveMode(CW, OUTPUT_);
            printf("LEFT\n");
        }
        else if(((event & E_UP) != 0) ){
            this->state = STATE_STOP;
            controller->changeDriveMode(STOP, OUTPUT_);
            printf("STOP\n");
        }
        break;
    case STATE_LEFT:
        if(((event & E_DOWN) != 0) ){
            this->state = STATE_BACKWARD;
            controller->changeDriveMode(BACKWARD, OUTPUT_);
            printf("BACKWARD\n");
        }
        else if(((event & E_RIGHT) != 0) ){
            this->state = STATE_STOP;
            controller->changeDriveMode(STOP, OUTPUT_);
            printf("STOP\n");
        }
        break;
    case STATE_RIGHT:
        if(((event & E_DOWN) != 0) ){
            this->state = STATE_BACKWARD;
            controller->changeDriveMode(BACKWARD, OUTPUT_);
            printf("BACKWARD\n");
        }
        else if(((event & E_LEFT) != 0) ){
            this->state = STATE_STOP;
            controller->changeDriveMode(STOP, OUTPUT_);
            printf("STOP\n");
        }
        break;
    case STATE_STOP:
        if(((event & E_UP) != 0) ){
            this->state = STATE_FORWARD;
            controller->changeDriveMode(FORWARD, OUTPUT_);
            printf("FORWARD\n");
        }
        else if(((event & E_DOWN) != 0) ){
            this->state = STATE_BACKWARD;
            controller->changeDriveMode(BACKWARD, OUTPUT_);
            printf("BACKWARD\n");
        }
        else if(((event & E_RIGHT) != 0) ){
            this->state = STATE_RIGHT;
            controller->changeDriveMode(CCW, OUTPUT_);
            printf("RIGHT\n");
        }
        else if(((event & E_LEFT) != 0) ){
            this->state = STATE_LEFT;
            controller->changeDriveMode(CW, OUTPUT_);
            printf("LEFT\n");
        }
        break;
    default:
        break;
    }
}

#else
void LEDTank::execState(){
  switch(this->state){
  case STATE_SEARCH:
    controller->getPosition(&distance, &angle);
rangingDistance=controller->getRanging();
    break;
  case STATE_STOP:
    rangingDistance=controller->getRanging();


    break;
  case STATE_CLOSE:
    controller->getPosition(&distance, &angle);
rangingDistance=controller->getRanging();

    break;
  case STATE_HOLD:
    controller->getPosition(&distance, &angle);
    break;
  case STATE_PUSH:
    controller->detectBlack(&lineL,&lineC,&lineR);
controller->getPosition(&distance, &angle);
    break;
  case STATE_PLACE:
    controller->getPosition(&distance, &angle);
    break;
  case STATE_RETURN:
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

    //entry
    controller->changeDriveMode(STOP, 0);
printf("STOP\n");
controller->positionReset();

    break;  
  case STATE_SEARCH:
    if(((event & E_CHANGE_RANGING) != 0) && (this->rangingDistance < 30.0)){
      // exit
      

      //action
      

      this->state = STATE_CLOSE;

      //entry
      controller->changeDriveMode(FORWARD, 70);
printf("CLOSE\n");
controller->positionReset();
    }
    break;
  case STATE_STOP:
    if(((event & E_UP) != 0) ){
      // exit
      

      //action
      

      this->state = STATE_SEARCH;

      //entry
      controller->changeDriveMode(CW, 45);
printf("SEARCH\n");
    }
    break;
  case STATE_CLOSE:
    if(((event & E_CHANGE_RANGING) != 0) && (this->rangingDistance < 4.0)){
      // exit
      

      //action
      

      this->state = STATE_HOLD;

      //entry
      controller->changeDriveMode(STOP, 80);
printf("HOLD\n");
    }
    break;
  case STATE_HOLD:
    if(((event & E_TRUE) != 0) ){
      // exit
      sleep(1);

      //action
      

      this->state = STATE_PUSH;

      //entry
      controller->changeDriveMode(FORWARD, 70);
printf("PUSH\n");
    }
    break;
  case STATE_PUSH:
    if(((event & E_CHANGE_AREA
) != 0) && (
this->lineC == 1 && 
this->lineL == 1 && 
this->lineR == 1)){
      // exit
      

      //action
      

      this->state = STATE_PLACE;

      //entry
      controller->changeDriveMode(STOP, 80);
printf("PLACE\n");
    }
    break;
  case STATE_PLACE:
    if(((event & E_TRUE) != 0) ){
      // exit
      sleep(1);

      //action
      

      this->state = STATE_RETURN;

      //entry
      controller->changeDriveMode(BACKWARD, 80);
printf("RETURN\n");
    }
    break;
  case STATE_RETURN:
    if(((event & E_CHANGE_DISTANCE) != 0) && (this->distance < 0)){
      // exit
      

      //action
      

      this->state = STATE_STOP;

      //entry
      controller->changeDriveMode(STOP, 0);
printf("STOP\n");
controller->positionReset();
    }
    break;
  default:
    break;
  }
}
#endif
