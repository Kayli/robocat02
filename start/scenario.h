#pragma once;
#include <Arduino.h>
#include "queueList.h"
#include "head.h"

enum ActionType { Move, Delay };

enum ScenarioStatus { Started, Stopped };

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
  Head*             _head;
  QueueList<Action> _actionsQueue;
  ScenarioStatus    _status;
  int               _transitionTimeMsec;
  public:
    Scenario(Head* head, int transitionTimeMsec = 1000) : _head(head), _status(Stopped), _transitionTimeMsec(transitionTimeMsec)
    {
    }
    
    void start()
    {
      startNextAction();
    }
    
    ScenarioStatus getStatus()
    {
      return _status;
    }
    
    void startNextAction()
    {
      Action action = _actionsQueue.pop();
      _head->startMoving(action.pan, action.tilt, _transitionTimeMsec);
      _status = Started;
    }
    
    void update()
    {
      if (_status == Stopped) return;
      
      _head->update();
      
      boolean transitionFinished = _head->transitionFinished();
      if(transitionFinished && _actionsQueue.isNotEmpty()) 
      {
        startNextAction();
        transitionFinished = _head->transitionFinished();
      }
        
      if(transitionFinished && _actionsQueue.isEmpty())
        _status = Stopped; 
        
      log("_actionsQueue.count is %d. Transition finished: %d", _actionsQueue.count(), transitionFinished);
    }
    
    Scenario* toPosition(float pan, float tilt)
    {
      _actionsQueue.push(Action(Move, pan, tilt));
      return this;
    }
    
  private:
    
};




