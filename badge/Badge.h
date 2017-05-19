#ifndef _Basic_Basic_h
#define _Basic_Basic_h

/* we need the SerialUI lib */
#include <SerialUI.h>

//#define DEBUG
#ifdef DEBUG
 #define DEBUG_PRINT(x)  Serial.print(x)
 #define DEBUG_PRINTLN(x)  Serial.println(x)
#else
 #define DEBUG_PRINT(x)
 #define DEBUG_PRINTLN(x)
#endif

/* MySUI
   Our SerialUI Instance, through which we can send/receive
   data from users.
*/
extern SUI::SerialUI MySUI;

/* custom global scope definitions: */

void doMaintenanceStuff();

/*
   The container for MyInputs, which
   holds all the variables for the various inputs.
*/
typedef struct MyInputsContainerStruct {

  long int Custom;
  // constructor to set sane startup vals
  MyInputsContainerStruct() :
    Custom(0)
  {}
} MyInputsContainerSt;

extern MyInputsContainerSt MyInputs;


/* MyTracked
   A structure to hold the tracked variables, which will
   automatically update the druid UI when modified by this
   program.
*/
typedef struct MyTrackedVarsContainerStruct {

  unsigned long LEDPattern;
  // constructor to set sane startup vals
  MyTrackedVarsContainerStruct() :
    LEDPattern(255)
  {}
} MyTrackedVarsContainerSt;

extern MyTrackedVarsContainerSt MyTracked;
void CustomHeartbeatCode();

/* ********* callbacks and validation functions ********* */

/* *** Main *** */
namespace Main {

/* *** Main -> Schedule *** */
namespace Schedule {

void printDay1();
void printDay2();
void printDay3();

} /* namespace Schedule */


} /* namespace Main */

/* ***** SetupSerialUI: where we'll be setting up menus and such **** */
bool SetupSerialUI();


#define DIE_HORRIBLY(msg)   for(;;){ MySUI.println(msg); delay(1000); }


#endif
