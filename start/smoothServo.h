#pragma once;
#include <Servo.h>
#include <utils.h>
#include <Arduino.h> 
#include <string.h>
#include "transition.h"

class SmoothServo 
{
  private:
    Servo               _servo;
    float               _position;
    Transition<float>*  _transition;
      
    const int    _signalMin; 
    const int    _signalMax; 
    
  public:
    SmoothServo(int pin, int signalMin = 500, int signalMax = 1500) :
      _signalMin(signalMin),
      _signalMax(signalMax),
      _transition(NULL)
    {
      _servo.attach(pin);
    }
    
    ~SmoothServo()
    {
      if(_transition) delete _transition;
    }
    
    void move(float position)
    {
      setPosition(position);
    }
    
    void startMoving(float position)
    {
      if(position < 0 || position > 1) 
      {
        error("position is out of range. It should be between 0 and 1");
        return;
      }
      if(_transition->inProgress())
      {
        error("previous transition is still in progress");
        return;
      }
      
      if(!_transition) 
      {
        _transition = new Transition<float>(_position, position); //transitioning from old position to new position
        _transition->start();
        update();
      }
    }
    
    //updates servo position if required at the current moment in time
    void update()
    {
      if(!_transition) return; 
      if(_transition->isFinished()) 
      {
        log("transition finished!");
        delete _transition;
        _transition = NULL;
        return;
      }
      log("update works!");
      float value = _transition->getValue();
      setPosition(value);
    }
    
    void reset()
    {
      setPosition(0.5);
    }
    
  private:
    void setPosition(float position)
    {
      log("position is %f", position);
      int signal = ((_signalMax - _signalMin) * position) + _signalMin;
      log("signal is %d", signal);
      _servo.writeMicroseconds(signal);
      _position = position;
    }
};
