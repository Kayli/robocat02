#include <Servo.h>
#include "utils.h"
#include "head.h"

Head* head;

void setup() 
{
  Serial.begin(9600);
  
  head = new Head();
  head->reset();
    
  //synchroniously moves servo as fast as possible
  //head->move(0.5, 0.3);
  
  
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
  
  /*
  head.move(0, 0);
  head.move(0, 50);
  delay(1000);
  head.move(20, 30);
  
  delay(1000);
  head.move(20, 50);
  delay(500);
  */
}


