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
  /* We checkForUser() periodically, to see
  ** if anyone is attempting to send us some
  ** data through SerialUI.

  ** Called without parameters, or with 0, checkForUser
  ** won't delay the program, as it won't block at all.
  ** Using a parameter > 0:
  **    checkForUser(MAX_MS);
  ** will wait for up to MAX_MS milliseconds for a user,
  ** so is equivalent to having a delay(MAX_MS) in the loop,
  ** when no user is present.
  */
  if (MySUI.checkForUser(heartbeat_function_period_ms)) {

    /* Now we keep handling the serial user's
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

