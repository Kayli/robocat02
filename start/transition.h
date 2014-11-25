#pragma once;
#include <utils.h>
#include <Arduino.h>
#include <string.h>

template <class T>
class Transition
{
  private:
    T _start;
    T _finish;
    int _durationMsec;
    unsigned long _startTime;
    unsigned long _endTime;
    
    boolean _isFinished;
    
  public:
    Transition(T start, T finish, int durationMsec = 1000) :
      _start(start),
      _finish(finish),
      _durationMsec(durationMsec),
      _isFinished(false)
    {
        
    }
  
    void start()
    {
      //log("Transition::start");
      _startTime = millis(); 
      _endTime = _startTime + _durationMsec;
      
      //log("_startTime=%d", _startTime);
      //log("_endTime=%d", _endTime);
    }
    
    T getValue()
    {
      if(_isFinished) return _finish;
      if(_start == _finish) return _finish;
      
      int timeFromStartMsec = getTimeFromStart();  
      //log("timeFromStartMsec=%d", timeFromStartMsec);   
      
      T amountOfChange = _finish - _start;
      T value = easeInOut(timeFromStartMsec, _start, amountOfChange);
      
      if(timeFromStartMsec > _durationMsec) 
      {
        _isFinished = true;
        return _finish;
      }
      
      return value;
    }
    
    boolean isFinished()
    {
      if(getTimeFromStart() > _durationMsec) _isFinished = true;
      if(_start == _finish) _isFinished = true;
      return _isFinished;
    }
    
    boolean inProgress()
    {
      return !isFinished();
    }
    
    void trace()
    {
      log("_stat=%f", _start);
      log("_finish=%f", _finish);
    }
  
   private:
    T easeInOut(int timeFromStartMsec, T initialValue, T amountOfChange) 
    {
      float t = (float)timeFromStartMsec / (_durationMsec / 2);
     
      if (t < 1) return (amountOfChange / 2.0) * t * t  + initialValue;
      return (-amountOfChange / 2.0) * ((--t) * (t-2)  - 1) + initialValue;
    }
    
    int getTimeFromStart()
    {
      unsigned long now = millis();
      return now - _startTime;
    }
};
