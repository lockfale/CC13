
/* we need the SerialUI lib */
#include <SerialUI.h>

/* our project specific types and functions are here */
#include "BadgeSettings.h"
#include "Badge.h"
#include "radio.h"
#include "led.h"

/* MySUI
   Our SerialUI Instance, through which we can send/receive
   data from users. Actually instantiated here, for global use.

*/
SUI::SerialUI MySUI;


/*
   The container for MyInputs, which
   holds all the variables for the various inputs.
   Actually instantiated here, for global use.
*/
MyInputsContainerSt MyInputs;


/* MyTracked
   A structure to hold the tracked variables, which will
   automatically update the druid UI when modified by this
   program.
   Actually instantiated here, for global use.
*/
MyTrackedVarsContainerSt MyTracked;


bool SetupSerialUI() {

  MySUI.setGreeting(F(serial_ui_greeting_str));
  // SerialUI acts just like (is actually a facade for)
  // Serial.  Use _it_, rather than Serial, throughout the
  // program.
  // basic setup of SerialUI:
  MySUI.begin(serial_baud_rate); // serial line open/setup
  MySUI.setTimeout(serial_readtimeout_ms);   // timeout for reads (in ms), same as for Serial.
  MySUI.setMaxIdleMs(serial_maxidle_ms);    // timeout for user (in ms)
  // how we are marking the "end-of-line" (\n, by default):
  MySUI.setReadTerminator(serial_input_terminator);

  // have a "heartbeat" function to hook-up
  MySUI.setUserPresenceHeartbeat(CustomHeartbeatCode);
  // heartbeat_function_period_ms set in main settings header
  MySUI.setUserPresenceHeartbeatPeriod(heartbeat_function_period_ms);


  // Add variable state tracking

  MySUI.trackState(
    SUI_STR("LEDPattern"),
    &(MyTracked.LEDPattern));



  // a few error messages we hopefully won't need

  SUI_FLASHSTRING CouldntCreateMenuErr = F("Could not create menu?");
  SUI_FLASHSTRING CouldntAddItemErr = F("Could not add item?");

  // get top level menu, to start adding items
  SUI::Menu * topMenu = MySUI.topLevelMenu();
  if (! topMenu ) {
    // well, that can't be good...
    MySUI.returnError(F("Very badness in sEriALui!1"));
    return false;
  }



  /* *** Main *** */


  //if ( ! topMenu->addCommand(
  //       SUI_STR("details"),
  //       Main::doDetails,
  //       SUI_STR("Program deets"))) {
  //  MySUI.returnError(CouldntAddItemErr);
  //  return false;
  //}

  SUI::Menu * submen1 = topMenu->subMenu(
                          SUI_STR("schedule"),
                          SUI_STR("Print the schedule"));
  if (! submen1 ) {
    DIE_HORRIBLY(CouldntCreateMenuErr);
  }

  SUI::Menu * submen2 = topMenu->subMenu(
                          SUI_STR("flashy"),
                          SUI_STR("Flashy flashy"));
  if (! submen1 ) {
    DIE_HORRIBLY(CouldntCreateMenuErr);
  }

  SUI::Menu * submen3 = topMenu->subMenu(
                          SUI_STR("radio"),
                          SUI_STR("Radio Properties"));
  if (! submen2 ) {
    DIE_HORRIBLY(CouldntCreateMenuErr);
  }


  /* *** Main -> Schedule *** */

  if ( ! submen1->addCommand(
         SUI_STR("friday"),
         Main::Schedule::printDay1,
         SUI_STR("Print Friday Schedule"))) {
    MySUI.returnError(CouldntAddItemErr);
    return false;
  }

  if ( ! submen1->addCommand(
         SUI_STR("saturday"),
         Main::Schedule::printDay2,
         SUI_STR("Print Saturday Schedule"))) {
    MySUI.returnError(CouldntAddItemErr);
    return false;
  }

  if ( ! submen1->addCommand(
         SUI_STR("sunday"),
         Main::Schedule::printDay3,
         SUI_STR("Print Sunday Schedule"))) {
    MySUI.returnError(CouldntAddItemErr);
    return false;
  }

  /* *** Main -> LED *** */
  if ( ! submen2->addCommand(
         SUI_STR("flash"),
         LED::flashPattern,
         SUI_STR("Blinky"))) {
    MySUI.returnError(CouldntAddItemErr);
    return false;
  }

  if ( ! submen2->addCommand(
         SUI_STR("bullet"),
         LED::bulletPattern,
         SUI_STR("Its so fast!"))) {
    MySUI.returnError(CouldntAddItemErr);
    return false;
  }

  if ( ! submen2->addCommand(
         SUI_STR("radiate"),
         LED::radiatePattern,
         SUI_STR("Radiating from the center"))) {
    MySUI.returnError(CouldntAddItemErr);
    return false;
  }

  if ( ! submen2->addCommand(
         SUI_STR("radiate2"),
         LED::radiate2Pattern,
         SUI_STR("Inverse radiating from the center"))) {
    MySUI.returnError(CouldntAddItemErr);
    return false;
  }

  if ( ! submen2->addCommand(
         SUI_STR("march"),
         LED::marchPattern,
         SUI_STR("March March March March"))) {
    MySUI.returnError(CouldntAddItemErr);
    return false;
  }

  if ( ! submen2->addCommand(
         SUI_STR("negmarch"),
         LED::negmarchPattern,
         SUI_STR("Marching backwards"))) {
    MySUI.returnError(CouldntAddItemErr);
    return false;
  }

  if ( ! submen2->addCommand(
         SUI_STR("stackdots"),
         LED::stackdotsPattern,
         SUI_STR("We are stacking blocks"))) {
    MySUI.returnError(CouldntAddItemErr);
    return false;
  }

  if ( ! submen2->addCommand(
         SUI_STR("sparkle"),
         LED::sparklePattern,
         SUI_STR("We are getting fabulous"))) {
    MySUI.returnError(CouldntAddItemErr);
    return false;
  }

  /* *** Main -> Radio *** */

  if ( ! submen3->addCommand(
         SUI_STR("temp"),
         Radio::printTemperature,
         SUI_STR("Print Radio Temperature"))) {
    MySUI.returnError(CouldntAddItemErr);
    return false;
  }

  return true;

}
