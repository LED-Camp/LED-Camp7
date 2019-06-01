#include <iostream>
#include <sys/time.h>
#include <time.h>
#include "wiringPi.h"
#include "Event.h"
#include "Controller.h"

#include "LEDTank_.h"


int main(void){
  struct timeval now;
  struct timeval old;

  char c;

  Controller *controller;
  Event *event;
  
  LEDTank_ *lEDTank_;

  if( wiringPiSetupGpio() < 0){ //initialize failed
    return 1;
  }
  
#ifdef EXPERIMENTAL_USE
    printf("Experimental use mode; w:↑, a:←, s:↓, d:→
");
#endif


  lEDTank_ = new LEDTank_;
  controller = Controller::getInstance();
  event = new Event(controller);
  gettimeofday(&now, NULL);
  gettimeofday(&old, NULL);

  while(true){
    while((now.tv_sec - old.tv_sec) + (now.tv_usec - old.tv_usec)*1.0E-6  < 0.05F){
      gettimeofday(&now, NULL);
    }
    old = now;

    preEvent->updatePreEvent();
#ifndef EXPERIMENTAL_USE
    lEDTank_->execState();
    lEDTank_->doTransition(event->getEvent());
#else
    lEDTank_->execState_for_experiment();
    lEDTank_->doTransition_for_experiment(event->getEvent());
#endif
  }
  gettimeofday(&now, NULL);
  gettimeofday(&old, NULL);
  
  while((now.tv_sec - old.tv_sec) + (now.tv_usec - old.tv_usec)*1.0E-6  < 0.05F){
    gettimeofday(&now, NULL);
  }
  getch();
  delete lEDTank_;
  delete event;
}
