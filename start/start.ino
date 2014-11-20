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
  
  head->reset();
  delay(2000);
  
  (scenario = new Scenario(head))
    ->toPosition(0.5, 0.8)
    ->toPosition(0.5, 0.7)
    ->toPosition(0.3, 0.7)
    ->toPosition(0.3, 0.4)
    ->toPosition(0.5, 0.5);
  
  scenario->start();
}

void loop() 
{ 
  scenario->update();
}


