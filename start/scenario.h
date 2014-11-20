#pragma once;
#include <Arduino.h>
#include "queueList.h"
#include "head.h"

enum ActionType { Move, Delay };

struct Action 
{
  Action(ActionType ptype, float ppan, float ptilt) 
    : type(ptype), pan(ppan), tilt(ptilt)
  {}
  
 
  Action() {}
  
  ActionType  type;
  float       pan;
  float       tilt;
};

class Scenario 
{
  Head*   _head;
  QueueList<Action> _actionsQueue;
  
  public:
    Scenario(Head* head) : _head(head)
    {
    }
    
    void start()
    {
            
      
    }
    
    Scenario& toPosition(float pan, float tilt)
    {
      _actionsQueue.push(Action(Move, pan, tilt));
      return *this;
    }
    
  private:
    
};




