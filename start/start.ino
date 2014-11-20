#include <Servo.h>
#include "utils.h"
#include "head.h"
#include "scenario.h"

Head* head;

void setup() 
{
  //Serial.begin(9600);
  
  head = new Head();
  
  head->reset();
  delay(2000);
  
  Scenario scenario = 
    Scenario(head)
      .toPosition(0.5, 0.8)
      .toPosition(0.5, 0.8)
      .toPosition(0.5, 0.8)
      .toPosition(0.5, 0.8);
  
  scenario.start();
  
  
  /*
  //asynchroniously moves servo smoothly for 2 sec
  tiltServo.startMovingSmoothly(1, 2000); 
  update(2000); //runs update loop for 2 sec
  
  tiltServo.startMovingSmoothly({
    {0, 1000}, 
    {1, 500},
    {0.5, 1500}
  });
  
  tiltServo.startMovingSmoothly({ 0, 1, 0.5 });
*/
}

void loop() 
{ 
  head->update();
}


