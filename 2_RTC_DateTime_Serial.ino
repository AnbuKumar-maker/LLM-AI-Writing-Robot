
#include <Wire.h> 
#include "RTClib.h" 

/////////////////////////////- Objects - /////////////////////////////////
RTC_DS1307 rtc;

////////////////////////////- Variables - /////////////////////////////////
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

/////////////////////////// - void setup() - //////////////////////
void setup () {
  while (!Serial); // for Leonardo/Micro/Zero
  Serial.begin(9600);
  if (! rtc.begin()) { //if rtc is not connect
    Serial.println("Couldn't find RTC");
    while (1);
  }
  if (! rtc.isrunning()) { // if rtc is not run
    Serial.println("RTC is NOT running!");
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    //     This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
  }
   //                   (year, month, date, hour, minute, second)
  //   rtc.adjust(DateTime(2022, 8, 29, 15, 45, 0));
}

/////////////////////////// - void loop() - //////////////////////
void loop() {
  DateTime now = rtc.now(); // datetime now
  Serial.print(now.year(), DEC); //year - YY
  Serial.print('/'); //serial print
  Serial.print(now.month(), DEC); //month - MM
  Serial.print('/');
  Serial.print(now.day(), DEC);   // day - SUNDAY
  Serial.print(" (");
  Serial.print(daysOfTheWeek[now.dayOfTheWeek()]); //week -6
  Serial.print(") ");
  Serial.print(now.hour(), DEC); //hour - hh
  Serial.print(':');
  Serial.print(now.minute(), DEC); //minute - mm
  Serial.print(':');
  Serial.print(now.second(), DEC); // seconds - ss
  Serial.println();
  Serial.println();
  delay(3000);
}
