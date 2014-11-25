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
    int _pin;
      
    const int    _signalMin; 
    const int    _signalMax; 
    
  public:
    SmoothServo(int pin, int signalMin = 500, int signalMax = 2400) :
      _signalMin(signalMin),
      _signalMax(signalMax),
      _transition(NULL),
      _pin(pin)
    {
      _servo.attach(pin);
      reset();
    }
    
    ~SmoothServo()
    {
      if(_transition) delete _transition;
    }
    
    void move(float position)
    {
      setPosition(position);
    }
    
    void startMoving(float position, int durationMsec = 1000)
    {
      if(position < 0 || position > 1) 
      {
        log("position is out of range. It should be between 0 and 1");
        return;
      }
      if(_transition->inProgress())
      {
        log("previous transition is still in progress");
        return;
      }
      
      if(_transition) 
      {
        delete _transition;
        _transition = NULL;
      }
      
      if(!_transition) 
      {
        log("creating transition for pin %d, from %f to %f", _pin, _position, position);
        _transition = new Transition<float>(_position, position, durationMsec); //transitioning from old position to new position
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
      //log("update works!");
      float value = _transition->getValue();
      setPosition(value);
    }
    
    void reset()
    {
      setPosition(0.5);
    }
    
    boolean transitionInProgress()
    {
      if(_transition == NULL) return false;
      return _transition->inProgress();
    }
    
  private:
    void setPosition(float position)
    {
      log("servo on pin %d position is %f", _pin, position);
      //if(_transition) _transition->trace();
      
      int signal = ((_signalMax - _signalMin) * position) + _signalMin;
      //log("signal is %d", signal);
      _servo.writeMicroseconds(signal);
      _position = position;
    }
};
