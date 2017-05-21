#include <avr/pgmspace.h> 
#include <SPIFlash.h>
#include "BadgeSettings.h"
#include "Badge.h"
#include "savecfg.h"
#include "led.h"
#include "radio.h"

#define SBUFFERSIZE  64  // Serial Input Buffer size

#define SERIAL_BAUD  115200

unsigned long currentMillis = 0;

void setup()
{
  if (!SetupSerialUI()) {
    DIE_HORRIBLY(F("Problem during setup"));
  }
  initiateCfg();
  int p = cfgReadPatternID();
  LED::initiateLED();
  LED::changePattern(p);
  Radio::initiateRadio();
}

void loop()
{
  if (MySUI.checkForUser(heartbeat_function_period_ms)) {

    /* Keep handling the serial user's
    ** requests until they exit or timeout.
    */
    while (MySUI.userPresent()) {
      // actually respond to requests
      MySUI.handleRequests();
    }
  } else {
      // when no one is connected, we do our 
      // maintenance 'manually'
      doMaintenanceStuff();
  }
}

