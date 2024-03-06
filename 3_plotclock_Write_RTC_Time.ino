
#include <Wire.h> 
#include "RTClib.h" 
#include <Servo.h> 

/////////////////////////////////////////////////// - Define -////////////////////////////////////////
#define CALIBRATION      // enable calibration mode
//#define REALTIMECLOCK    // enable real time clock

// When in calibration mode, adjust the following factor until the servos move exactly 90 degrees
#define SERVOFAKTORLEFT 650
#define SERVOFAKTORRIGHT 645

// Zero-position of left and right servo
// When in calibration mode, adjust the NULL-values so that the servo arms are at all times parallel
// either to the X or Y axis
#define SERVOLEFTNULL 2250 //2250
#define SERVORIGHTNULL 610 //600

#define SERVOPINLIFT  3
#define SERVOPINLEFT  5
#define SERVOPINRIGHT 6

// lift positions of lifting servo
#define LIFT0 1440 // on drawing surface   
#define LIFT1 1250 //1250   // between numbers 
#define LIFT2 900 //900   // going towards sweeper 

// speed of liftimg arm, higher is slower
#define LIFTSPEED 1500
//
// length of arms
#define L1 35
#define L2 56.3 
#define L3 15 
#define L4 46 

// origin points of left and right servo
#define O1X 20//15
#define O1Y -22//-16
#define O2X 40//43
#define O2Y -21//-20

/////////////////////////////- Objects - /////////////////////////////////
Servo servo1;  //
Servo servo2;  //
Servo servo3;  //

RTC_DS1307 rtc;

////////////////////////////- Variables - /////////////////////////////////
volatile double lastX = 75;//75
volatile double lastY = 57.5; //47.5
int servoLift = 1500; //1500
int last_min = 0;

/////////////////////////// - void setup() - //////////////////////
void setup()
{
  Serial.begin(9600);
  if (! rtc.begin()) {//if rtc is not connect
    Serial.println("Couldn't find RTC");
    while (1);
  }
  if (! rtc.isrunning()) {// if rtc is not run
    Serial.println("RTC is NOT running!");
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }
  //  rtc.adjust(DateTime(2022, 9, 6, 15, 2, 0));
  drawTo(75.2, 47);
  lift(0);
  servo1.attach(SERVOPINLIFT);  //  lifting servo
  servo2.attach(SERVOPINLEFT);  //  left servo
  servo3.attach(SERVOPINRIGHT);  //  right servo
  delay(1000);
}

/////////////////////////// - void loop() - //////////////////////
void loop()
{
  DateTime now = rtc.now(); //Date time Now
  // Servohorns will have 90° between movements, parallel to x and y axis
  drawTo(-3, 29.2);
  delay(500);
  drawTo (75.2, 47);
  delay(500);

  int i = 0;
  //  Serial.print("minute:- ");  Serial.println(last_min);
  if (last_min != now.minute()) {
    //    Serial.print("minute:- ");  Serial.println(last_min);
    if (!servo1.attached()) servo1.attach(SERVOPINLIFT);
    if (!servo2.attached()) servo2.attach(SERVOPINLEFT);
    if (!servo3.attached()) servo3.attach(SERVOPINRIGHT);
    lift(0);
    now.hour();
    //    Serial.print("hour:- ");  Serial.print(now.hour());
    while ((i + 1) * 10 <= now.hour())
    {
      i++;
    }

    number(3, 5, 111, 1);
    number(7, 30, i, 0.9); //number(7, 32, i, 0.9);
    number(19, 30, (now.hour() - i * 10), 0.9); //(19, 28, (now.hour() - i * 10), 0.9);
    number(29, 30, 11, 0.9); //(29, 27, 11, 0.9);

    i = 0;
    while ((i + 1) * 10 <= now.minute())
    {
      i++;
    }
    number(36, 30, i, 0.9); //(36, 26, i, 0.9);
    number(51, 30, (now.minute() - i * 10), 0.9); //(51, 25, (now.minute() - i * 10), 0.9);
    lift(2);
    drawTo (76.1, 50);// drawTo (65.2, 36.5);///pen put on dustor
    delay(5);
    lift(1);
    last_min = now.minute();
    //    Serial.print(" LAST minute:- "); Serial.println(last_min);
    delay(580);
    servo1.detach();
    servo2.detach();
    servo3.detach();
  }
}

// Writing numeral with bx by being the bottom left originpoint. Scale 1 equals a 20 mm high font.
// The structure follows this principle: move to first startpoint of the numeral, lift down, draw numeral, lift up
void number(float bx, float by, int num, float scale) {

  switch (num) {

    case 0:
      drawTo(bx + 12 * scale, by + 6 * scale);
      lift(0);
      bogenGZS(bx + 7 * scale, by + 10 * scale, 10 * scale, -0.8, 6.7, 0.5);
      lift(1);
      break;
    case 1:
      drawTo(bx + 4 * scale, by + 15 * scale);//(bx + 3 * scale, by + 15 * scale);
      lift(0);
      drawTo(bx + 10 * scale, by + 20 * scale);
      drawTo(bx + 10 * scale, by + 0 * scale);
      lift(1);
      break;
    case 2:
      drawTo(bx + 2 * scale, by + 12 * scale);
      lift(0);
      bogenUZS(bx + 8 * scale, by + 14 * scale, 6 * scale, 3, -0.8, 1);
      drawTo(bx + 1 * scale, by + 0 * scale);
      drawTo(bx + 12 * scale, by + 0 * scale);
      lift(1);
      break;
    case 3:
      drawTo(bx + 2 * scale, by + 17 * scale);
      lift(0);
      bogenUZS(bx + 5 * scale, by + 15 * scale, 5 * scale, 3, -2, 1);
      bogenUZS(bx + 5 * scale, by + 5 * scale, 5 * scale, 1.57, -3, 1);
      lift(1);
      break;
    case 4:
      drawTo(bx + 10 * scale, by + 0 * scale);
      lift(0);
      drawTo(bx + 10 * scale, by + 20 * scale);
      drawTo(bx + 2 * scale, by + 6 * scale);
      drawTo(bx + 12 * scale, by + 6 * scale);
      lift(1);
      break;
    case 5:
      drawTo(bx + 2 * scale, by + 5 * scale);
      lift(0);
      bogenGZS(bx + 5 * scale, by + 6 * scale, 6 * scale, -2.5, 2, 1);
      drawTo(bx + 5 * scale, by + 20 * scale);
      drawTo(bx + 12 * scale, by + 20 * scale);
      lift(1);
      break;
    case 6:
      drawTo(bx + 2 * scale, by + 10 * scale);
      lift(0);
      bogenUZS(bx + 7 * scale, by + 6 * scale, 6 * scale, 2, -4.4, 1);
      drawTo(bx + 11 * scale, by + 20 * scale);
      lift(1);
      break;
    case 7:
      drawTo(bx + 2 * scale, by + 20 * scale);
      lift(0);
      drawTo(bx + 12 * scale, by + 20 * scale);
      drawTo(bx + 2 * scale, by + 0);
      lift(1);
      break;
    case 8:
      drawTo(bx + 5 * scale, by + 10 * scale);
      lift(0);
      bogenUZS(bx + 5 * scale, by + 15 * scale, 5 * scale, 4.7, -1.6, 1);
      bogenGZS(bx + 5 * scale, by + 5 * scale, 5 * scale, -4.7, 2, 1);
      lift(1);
      break;

    case 9:
      drawTo(bx + 9 * scale, by + 11 * scale);
      lift(0);
      bogenUZS(bx + 7 * scale, by + 15 * scale, 5 * scale, 4, -0.5, 1);
      drawTo(bx + 5 * scale, by + 0);
      lift(1);
      break;

    case 111: //erase time
      drawTo(75.2, 47); //drawTo(60, 47);
      lift(0);

      drawTo(65, 49);
      drawTo(5, 49);
      drawTo(5, 46);
      drawTo(65, 45);
      drawTo(65, 40);

      drawTo(3, 47);
      drawTo(3, 44);
      drawTo(65, 46);
      drawTo(65, 42);

      drawTo(5, 40);
      drawTo(5, 35);
      drawTo(65, 35);
      drawTo(65, 30);

      drawTo(3, 39);
      drawTo(3, 34);
      drawTo(65, 38);
      drawTo(65, 32);

      drawTo(5, 30);
      drawTo(5, 25);
      drawTo(65, 25);
      drawTo(65, 20);

      drawTo(3, 29);
      drawTo(3, 22);
      drawTo(65, 28);
      drawTo(65, 22);

      drawTo(5, 20);
      drawTo(60, 44);

      drawTo(75.2, 47);
      lift(2);
      break;

    case 11:
      drawTo(bx + 5 * scale, by + 15 * scale);
      lift(0);
      bogenGZS(bx + 5 * scale, by + 15 * scale, 0.1 * scale, 1, -1, 1);
      lift(1);
      drawTo(bx + 5 * scale, by + 5 * scale);
      lift(0);
      bogenGZS(bx + 5 * scale, by + 5 * scale, 0.1 * scale, 1, -1, 1);
      lift(1);
      break;

  }
}

void lift(char lift) {
  switch (lift) {
    // room to optimize  !

    case 0: //850
      if (servoLift >= LIFT0) {
        while (servoLift >= LIFT0)
        {
          servoLift--;
          servo1.writeMicroseconds(servoLift);
          delayMicroseconds(LIFTSPEED);
        }
      }
      else {
        while (servoLift <= LIFT0) {
          servoLift++;
          servo1.writeMicroseconds(servoLift);
          delayMicroseconds(LIFTSPEED);
        }
      }
      break;

    case 1: //150
      if (servoLift >= LIFT1) {
        while (servoLift >= LIFT1) {
          servoLift--;
          servo1.writeMicroseconds(servoLift);
          delayMicroseconds(LIFTSPEED);
        }
      }
      else {
        while (servoLift <= LIFT1) {
          servoLift++;
          servo1.writeMicroseconds(servoLift);
          delayMicroseconds(LIFTSPEED);
        }
      }
      break;

    case 2:
      if (servoLift >= LIFT2) {
        while (servoLift >= LIFT2) {
          servoLift--;
          servo1.writeMicroseconds(servoLift);
          delayMicroseconds(LIFTSPEED);
        }
      }
      else {
        while (servoLift <= LIFT2) {
          servoLift++;
          servo1.writeMicroseconds(servoLift);
          delayMicroseconds(LIFTSPEED);
        }
      }
      break;
  }
}


void bogenUZS(float bx, float by, float radius, int start, int ende, float sqee) {
  float inkr = -0.05;
  float count = 0;

  do {
    drawTo(sqee * radius * cos(start + count) + bx, radius * sin(start + count) + by);
    count += inkr;
  }
  while ((start + count) > ende);
}

void bogenGZS(float bx, float by, float radius, int start, int ende, float sqee) {
  float inkr = 0.05;
  float count = 0;

  do {
    drawTo(sqee * radius * cos(start + count) + bx, radius * sin(start + count) + by);
    count += inkr;
  }
  while ((start + count) <= ende);
}


void drawTo(double pX, double pY) {
  double dx, dy, c;
  int i;

  // dx dy of new point
  dx = pX - lastX;
  dy = pY - lastY;
  //path lenght in mm, times 4 equals 4 steps per mm
  c = floor(4 * sqrt(dx * dx + dy * dy));

  if (c < 1) c = 1;

  for (i = 0; i <= c; i++) {
    // draw line point by point
    set_XY(lastX + (i * dx / c), lastY + (i * dy / c));
  }
  lastX = pX;
  lastY = pY;
}

double return_angle(double a, double b, double c) {
  // cosine rule for angle between c and a
  return acos((a * a + c * c - b * b) / (2 * a * c));
}

void set_XY(double Tx, double Ty)
{
  delay(1);
  double dx, dy, c, a1, a2, Hx, Hy;

  // calculate triangle between pen, servoLeft and arm joint
  // cartesian dx/dy
  dx = Tx - O1X;
  dy = Ty - O1Y;

  // polar lemgth (c) and angle (a1)
  c = sqrt(dx * dx + dy * dy); //
  a1 = atan2(dy, dx); //
  a2 = return_angle(L1, L2, c);


  servo2.writeMicroseconds(floor(((a2 + a1 - M_PI) * SERVOFAKTORLEFT) + SERVOLEFTNULL));

  // calculate joinr arm point for triangle of the right servo arm
  a2 = return_angle(L2, L1, c);
  Hx = Tx + L3 * cos((a1 - a2 + 0.621) + M_PI); //36,5°
  Hy = Ty + L3 * sin((a1 - a2 + 0.621) + M_PI);

  // calculate triangle between pen joint, servoRight and arm joint
  dx = Hx - O2X;
  dy = Hy - O2Y;

  c = sqrt(dx * dx + dy * dy);
  a1 = atan2(dy, dx);
  a2 = return_angle(L1, L4, c); // a2 = return_angle(L1, (L2 - L3), c);

  servo3.writeMicroseconds(floor(((a1 - a2) * SERVOFAKTORRIGHT) + SERVORIGHTNULL));
}
