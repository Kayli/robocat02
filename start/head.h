#pragma once;
#include <Servo.h>
#include <utils.h>
#include <Arduino.h> 
#include <string.h>
#include "smoothServo.h"

class Head 
{
  private:
    SmoothServo     _panServo;    
    SmoothServo     _tiltServo;
    
  public:
    Head() :
      _panServo(11),  
      _tiltServo(10)
    {
      reset();
      
      log("servos initialized");
    }
  
    void move(float pan, float tilt) 
    {
      if(pan < 0 || pan > 1) error("pan is out of range");
      if(tilt < 0 || tilt > 1) error("tilt is out of range");
      
      _panServo.move(pan);
      _tiltServo.move(tilt);
    }
    
    void startMoving(float pan, float tilt, int durationMsec = 1000) 
    {
      if(pan < 0 || pan > 1) error("pan is out of range");
      if(tilt < 0 || tilt > 1) error("tilt is out of range");
      
      _panServo.startMoving(pan, durationMsec);
      _tiltServo.startMoving(tilt, durationMsec);
    }
    
    void moveLeftRight(int pan)
    {
      _panServo.move(pan);
    }
    
    void reset()
    {
      _panServo.reset();
      _tiltServo.reset();
    }
    
    boolean transitionFinished()
    {
      boolean transitionInProgress = _panServo.transitionInProgress() || _tiltServo.transitionInProgress();
      return !transitionInProgress;
    }
    
    void update()
    {
      _panServo.update();
      _tiltServo.update();
    }
};


