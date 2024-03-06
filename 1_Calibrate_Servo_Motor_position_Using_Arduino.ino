
#include <Servo.h> 
#define SERVOPINLIFT  3
#define SERVOPINLEFT  5
#define SERVOPINRIGHT 6

/////////////////////////////- Objects - /////////////////////////////////
Servo servo1;  //
Servo servo2;  //
Servo servo3;  //

/////////////////////////// - void setup() - //////////////////////
void setup()
{
  // attaches the servo on pin 3 to the servo object
  servo1.attach(SERVOPINLIFT);  // servo-1which is on arduino Sensor shiled board
  for (int num = 0; num <= 180; num++) // check servo motor - 0 to 180 degree rotation
  {
    servo1.write(num);//back to 'num' degrees(0 to 180)
    delay(10);//control servo speed
  }
  for (int num = 180; num > 0; num--) // check servo motor - 0 to 180 degree rotation
  {
    servo1.write(num);//back to 'num' degrees(0 to 180)
    delay(10);//control servo speed
  }
  delay(50);

  // attaches the servo on pin 3 to the servo object
  servo2.attach(SERVOPINLEFT);  // servo-1which is on arduino Sensor shiled board
  for (int num = 0; num <= 180; num++) // check servo motor - 0 to 180 degree rotation
  {
    servo2.write(num);//back to 'num' degrees(0 to 180)
    delay(10);//control servo speed
  }
  for (int num = 180; num > 0; num--) // check servo motor - 0 to 180 degree rotation
  {
    servo2.write(num);//back to 'num' degrees(0 to 180)
    delay(10);//control servo speed
  }
  delay(50);
  // attaches the servo on pin 3 to the servo object
  servo3.attach(SERVOPINRIGHT);  // servo-1which is on arduino Sensor shiled board
  for (int num = 0; num <= 180; num++) // check servo motor - 0 to 180 degree rotation
  {
    servo3.write(num);//back to 'num' degrees(0 to 180)
    delay(10);//control servo speed
  }
  for (int num = 180; num > 0; num--) // check servo motor - 0 to 180 degree rotation
  {
    servo3.write(num);//back to 'num' degrees(0 to 180)
    delay(10);//control servo speed
  }
  delay(50);
}

/////////////////////////// - void loop() - ////////////////////////
void loop()
{
  servo1.write(90);//goes to 90 degrees then place SERVOPINLIFT bracket
  delay(1000);//wait for a one second
  servo2.write(90);//goes to 90 degrees then place SERVOPINLEFT bracket
  delay(1000);//wait for a one second
  servo3.write(90);//goes to 90 degrees then place SERVOPINRIGHT bracket
  delay(1000);//wait for a one second
}
