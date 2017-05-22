#include <avr/pgmspace.h>
#include "led.h"
#include "savecfg.h"

/* *** LED *** */
namespace LED {

int latchPin = 9;
int clockPin = 5;
int dataPin = 8;
int fadepin = 3;

const byte flash[] PROGMEM = {
  B00000000, B11111111
};
const byte bullet[] PROGMEM = {
  B00010001, B00100010, B01000100, B10001000
};
const byte radiate[] PROGMEM = {
  B00011000, B00100100, B01000010, B10000001, B00000000,
  B00000000
};
const byte negradiate[] PROGMEM = {
  B10000001, B01000010, B00100100, B00011000, B00000000,
  B00000000
};
const byte march[] PROGMEM = {
  B00000001, B00000010, B00000100, B00001000, B00010000,
  B00100000, B01000000, B10000000, B01000000, B00100000,
  B00010000, B00001000, B00000100, B00000010, B00000001
};
const byte negmarch[] PROGMEM = {
  B11111111, B11111110, B11111101, B11111011, B11110111,
  B11101111, B11011111, B10111111, B01111111, B11111111,
  B01111111, B10111111, B11011111, B11101111, B11110111,
  B11111011, B11111101, B11111110
};
const byte stackdots[] PROGMEM = {
  B00000000, B10000000, B01000000, B00100000, B00010000,
  B00001000, B00000100, B00000010, B00000001, B10000001,
  B01000001, B00100001, B00010001, B00001001, B00000101,
  B00000011, B10000011, B01000011, B00100011, B00010011,
  B00001011, B00000111, B10000111, B01000111, B00100111,
  B00010111, B00001111, B10001111, B01001111, B00101111,
  B00011111, B10011111, B01011111, B00111111, B10111111,
  B01111111, B11111111
};
const byte sparkle[] PROGMEM = {
  B00000001, B10000000, B00000010, B01000000, B00000100,
  B00100000, B00001000, B00010000
};
const int patternTimes[] = {20, 30, 50, 40, 20, 30, 20, 5};
const int patternLengths[] = {2, 4, 6, 6, 15, 18, 37, 8};

unsigned int patternTime;
unsigned long previousPatternMillis = 0;
byte patternLength = 0;
byte currPattern = 255;
byte patternState = 0;
char PatternBuf[40];

void initiateLED()
{
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(fadepin, OUTPUT);
}

void changePattern(byte tmpPattern)
{
  if (tmpPattern != currPattern) {
    currPattern = tmpPattern;
    patternLength = patternLengths[currPattern];
    patternTime = patternTimes[currPattern];
    patternState = 0;
    if (currPattern == 0) {
      memcpy_P( PatternBuf, flash, patternLength );
    } else if (currPattern == 1) {
      memcpy_P( PatternBuf, bullet, patternLength );
    } else if (currPattern == 2) {
      memcpy_P( PatternBuf, radiate, patternLength );
    } else if (currPattern == 3) {
      memcpy_P( PatternBuf, negradiate, patternLength );
    } else if (currPattern == 4) {
      memcpy_P( PatternBuf, march, patternLength );
    } else if (currPattern == 5) {
      memcpy_P( PatternBuf, negmarch, patternLength );
    } else if (currPattern == 6) {
      memcpy_P( PatternBuf, stackdots, patternLength );
    } else if (currPattern == 7) {
      memcpy_P( PatternBuf, sparkle, patternLength );
    }
  }
}

void changeLED(unsigned long currMill)
{
  if (patternState >= patternLength) {
    patternState = 0;
  }
  if(currMill - previousPatternMillis >= patternTime)
  {
    previousPatternMillis = currMill;  // Remember the time
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, MSBFIRST, PatternBuf[patternState]);
    digitalWrite(latchPin, HIGH);
    patternState++;
  }
}

void flashPattern()
{
  byte x = 0;
  changePattern(x);
  cfgUpdatePatternID(x);
}

void bulletPattern()
{
  byte x = 1;
  changePattern(x);
  cfgUpdatePatternID(x);
}

void radiatePattern()
{
  byte x = 2;
  changePattern(x);
  cfgUpdatePatternID(x);
}

void negradiatePattern()
{
  byte x = 3;
  changePattern(x);
  cfgUpdatePatternID(x);
}

void marchPattern()
{
  byte x = 4;
  changePattern(x);
  cfgUpdatePatternID(x);
}

void negmarchPattern()
{
  byte x = 5;
  changePattern(x);
  cfgUpdatePatternID(x);
}

void stackdotsPattern()
{
  byte x = 6;
  changePattern(x);
  cfgUpdatePatternID(x);
}

void sparklePattern()
{
  byte x = 7;
  changePattern(x);
  cfgUpdatePatternID(x);
}

} /* namespace LED */
