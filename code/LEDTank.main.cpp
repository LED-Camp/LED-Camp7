#include <iostream>
#include <sys/time.h>
#include <time.h>
#include "wiringPi.h"
#include "Event.h"
#include "Controller.h"

#include "LEDTank.h"


int main(void){
  struct timeval now;
  struct timeval old;

  char c;

  Controller *controller;
  Event *event;
  LEDTank *lEDTank;


  if( wiringPiSetupGpio() < 0){ //initialize failed
    return 1;

  }

  controller = Controller::getInstance();

  lEDTank = new LEDTank(controller);

  event = new Event(controller);

  gettimeofday(&now, NULL);
  gettimeofday(&old, NULL);

  while(1){
    while((now.tv_sec - old.tv_sec) + (now.tv_usec - old.tv_usec)*1.0E-6  < 0.05F){
      gettimeofday(&now, NULL);
    }
    old = now;

    if(event->updateEvent() < 0){
        controller->changeDriveMode(STOP, 0);
        break;
    }

    lEDTank->execState();
    lEDTank->doTransition(event->getEvent());
  }

  gettimeofday(&now, NULL);
  gettimeofday(&old, NULL);

  while((now.tv_sec - old.tv_sec) + (now.tv_usec - old.tv_usec)*1.0E-6  < 0.05F){
    gettimeofday(&now, NULL);
  }

  delete lEDTank;
  delete event;
}
