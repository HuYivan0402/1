#include "TM1637.h"
#include "RTClib.h"

// Pins definitions for TM1637 and can be changed to other ports
#define CLK 10
#define DIO 9

TM1637 tm1637(CLK, DIO);

// Holds current clock time
RTC_DS1307 RTC;
DateTime theTime;

int8_t TimeDisp[] = {-1, -1, -1, -1}; // Use -1 instead of 0xff to avoid precision loss

// Group number
int groupNum = 1;

void setup() {
  Serial.begin(9600);

  if (!RTC.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }

  if (!RTC.isrunning()) {
    Serial.println("RTC is NOT running!");
    RTC.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }

  tm1637.init();
  tm1637.set(2); // TYPICAL = 2, DARKEST = 0, BRIGHTEST = 7;
  tm1637.display(0, 'G');
  tm1637.display(1, groupNum);
  tm1637.display(2, ':');
  tm1637.display(3, ' ');

  delay(3000);
}

int hour, minute, second;
unsigned char ClockPoint = 1;

void loop() {
  DateTime theTime = RTC.now();
  second = theTime.second(); // get seconds
  minute = theTime.minute(); // get minutes

  TimeDisp[0] = groupNum; // Display group number
  TimeDisp[1] = minute / 10;
  TimeDisp[2] = minute % 10;
  TimeDisp[3] = -1; // Display a blank on the last digit

  tm1637.display(TimeDisp);

  Serial.print("Group ");
  Serial.print(groupNum);
  Serial.print(": ");
  Serial.print(minute);
  Serial.println();

  ClockPoint = (~ClockPoint) & 0x01;
  if (ClockPoint) {
    tm1637.point(POINT_ON);
  } else {
    tm1637.point(POINT_OFF);
  }

  delay(1000);
}
