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

  Controller *controller;
  Event *event;
  
  LEDTank *lEDTank;

  if( wiringPiSetupGpio() < 0){ //initialize failed
    return 1;
  }
  
#ifdef EXPERIMENTAL_USE
    printf("Experimental use mode; w:↑, a:←, s:↓, d:→\n");
#endif

  controller = Controller::getInstance();
  lEDTank = new LEDTank(controller);
  event = new Event(controller);
  gettimeofday(&now, NULL);
  gettimeofday(&old, NULL);

  while(true){
    while((now.tv_sec - old.tv_sec) + (now.tv_usec - old.tv_usec)*1.0E-6  < 0.05F){
      gettimeofday(&now, NULL);
    }
    old = now;
    if(event->updateEvent() < 0){
        printf("STOP\n");
        controller->changeDriveMode(STOP, 0);
        break;
     }
     


#ifdef EXPERIMENTAL_USE
    lEDTank->execState_for_experiment();
    lEDTank->doTransition_for_experiment(event->getEvent());

#else
    lEDTank->execState();
    lEDTank->doTransition(event->getEvent());

#endif
  }
  gettimeofday(&now, NULL);
  gettimeofday(&old, NULL);
  
  while((now.tv_sec - old.tv_sec) + (now.tv_usec - old.tv_usec)*1.0E-6  < 0.05F){
    gettimeofday(&now, NULL);
  }
  getch();
  delete lEDTank;
  delete event;
}
