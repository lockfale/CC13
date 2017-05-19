#include <avr/pgmspace.h>
#include <SerialUI.h>
#include "BadgeSettings.h"

/* our project specific types and functions are here */
#include "Badge.h"
#include "led.h"
#include "radio.h"

char progMemBuffer[80];

void doMaintenanceStuff()
{
  LED::changeLED(millis());
  Radio::receiveRadio();
  Radio::ping();
}

// "heartbeat" function, called periodically while connected
void CustomHeartbeatCode () {

  // will be called when a user is present.
  doMaintenanceStuff();

}


/* ********* callbacks and validation functions ********* */

/* *** Main *** */
namespace Main {


/* *** Main -> Schedule *** */
namespace Schedule 
{

const char day1_0[] PROGMEM = "FRIDAY[2017/05/19]";
const char day1_1[] PROGMEM = "  17:00 Registration Begins";
const char day1_2[] PROGMEM = "  18:30 Opening Remarks";
const char day1_3[] PROGMEM = "  18:45 Intro to the Badge";
const char day1_4[] PROGMEM = "  19:15 Phishing, Whaling: Beyond Technology Social Eng...";
const char day1_5[] PROGMEM = "  20:15 RFID is dead; long live RFID!";
const char day1_6[] PROGMEM = "  21:15 A Pentester's Intro to Attacking ICS/SCAD";
const char day1_7[] PROGMEM = "  21:15 DMARC for Fun and Threat Intel";
const char* const day1[] PROGMEM = { day1_0, day1_1, day1_2, day1_3, day1_4, day1_5, day1_6, day1_7 };

const char day2_0[] PROGMEM = "SATURDAY[2017/05/20]";
const char day2_1[] PROGMEM = "  09:00 Registration Opens";
const char day2_2[] PROGMEM = "  09:45 Daily Remarks and Announcements";
const char day2_3[] PROGMEM = "  10:00 CTFs - Not Just for Halo";
const char day2_4[] PROGMEM = "  11:00 So you want to learn Machine Learning";
const char day2_5[] PROGMEM = "  12:00 ** Lunch Break - Meals not Provided **";
const char day2_6[] PROGMEM = "  13:00 Testing Phone Systems";
const char day2_7[] PROGMEM = "  14:00 Hillbilly Storytime: Pentest Fails";
const char day2_8[] PROGMEM = "  15:00 How to buy illegal stuff online";
const char day2_9[] PROGMEM = "  16:00 OpSec for InfoSec";
const char day2_10[] PROGMEM = "  17:00 ** Dinner Break - Meals not Provided **";
const char day2_11[] PROGMEM = "  19:00 Hacking The Invasion of Things";
const char day2_12[] PROGMEM = "  20:00 Hacker Trivia";
const char* const day2[] PROGMEM = { day2_0, day2_1, day2_2, day2_3, day2_4, day2_5, day2_6, day2_7, day2_8, day2_9, day2_10, day2_11, day2_12 };

const char day3_0[] PROGMEM = "SUNDAY[2017/05/21]";
const char day3_1[] PROGMEM = "  9:30 Registration Begins";
const char day3_2[] PROGMEM = "  10:00 Daily Remarks and Announcements";
const char day3_3[] PROGMEM = "  10:00 A ROP Primer";
const char day3_4[] PROGMEM = "  11:00 Getting Started with PowerShell or One Tool to Hack them all";
const char day3_5[] PROGMEM = "  12:00 ** Lunch Break - Meals not Provided **";
const char day3_6[] PROGMEM = "  13:00 Forgotten History of Cyberwar";
const char day3_7[] PROGMEM = "  14:00 How to Patch Stupid - A modern approach to remediating user risk";
const char day3_8[] PROGMEM = "  15:00 HoneyPy & HoneyDB";
const char day3_9[] PROGMEM = "  16:30 The Unofficial Security Enthusiast's Meme Filled Guide";
const char day3_10[] PROGMEM = "  17:00 Annoucement of Contest Winners and Closing Remarks";
const char* const day3[] PROGMEM = { day3_0, day3_1, day3_2, day3_3, day3_4, day3_5, day3_6, day3_7, day3_8, day3_9, day3_10 };

void printDay1()
{
  byte dayLength = 8;
  for (int item=0; item<dayLength; item++){
    strcpy_P(progMemBuffer, (char*)pgm_read_word(&(day1[item])));
    MySUI.println(progMemBuffer);
  }
}

void printDay2()
{
  byte dayLength = 13;
  for (int item=0; item<dayLength; item++){
    strcpy_P(progMemBuffer, (char*)pgm_read_word(&(day2[item])));
    MySUI.println(progMemBuffer);
  }
}

void printDay3()
{
  byte dayLength = 11;
  for (int item=0; item<dayLength; item++){
    strcpy_P(progMemBuffer, (char*)pgm_read_word(&(day3[item])));
    MySUI.println(progMemBuffer);
  }
}

} /* namespace Schedule */

} /* namespace Main */

