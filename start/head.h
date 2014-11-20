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
      _panServo.move(0.5);
      _tiltServo.move(0.5);
      
      log("servos initialized");
    }
  
    void move(int pan, int tilt) 
    {
      if(pan < 0 || pan > 1) error("pan is out of range");
      if(tilt < 0 || tilt > 1) error("tilt is out of range");
      
      _panServo.move(pan);
      _tiltServo.move(tilt);
    }
    
    void reset()
    {
      _panServo.reset();
      _tiltServo.reset();
    }
    
    void update()
    {
      _panServo.update();
      _tiltServo.update();
    }
    /*
  private:
    void animateServo(Servo& servo, int value)
    {      
      int oldValue = servo.read();
      
      Animation<int> animation(oldValue, value, 700);
      animation.start();
      
      while(animation.inProgress())
      {
        int value = animation.getValue();
        log("new value is %d", value);
        servo.write(value);
      }
      
      int value2 = animation.getValue();
      log("new value is %d", value2);
      servo.write(animation.getValue());
    }
    
    */
};
