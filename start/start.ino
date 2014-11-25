#include <Servo.h>
#include "utils.h"
#include "head.h"
#include "scenario.h"

Head* head;
Scenario* scenario;

void setup() 
{
  //Serial.begin(9600);
  
  head = new Head();
  
  delay(2000);
  
  startRandomScenario();
}

void loop() 
{ 
  scenario->update();
  
  if(scenario->getStatus() == Stopped)
  {
    startRandomScenario();
  }
}

Scenario* startRandomScenario()
{
  delete scenario;
  (scenario = new Scenario(head, random(300, 2000)))
    ->toPosition(0.5, 0.8)
    ->toPosition(0.5, 0.4)
    ->toPosition(0.3, 0.7)
    ->toPosition(0.8, 0.4)
    ->toPosition(0.5, 0.5);
  
  scenario->start();
}

float randomFloat(float min, float max)
{
  return ((float)random(min * 100, max * 100)) / 100;
}


