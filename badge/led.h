#ifndef led_h
#define led_h
#include <Arduino.h>

/* *** LED *** */
namespace LED {

void initiateLED();
void changePattern(byte tmpPattern);
void changeLED(unsigned long currMill);
void flashPattern();
void bulletPattern();
void radiatePattern();
void negradiatePattern();
void marchPattern();
void negmarchPattern();
void stackdotsPattern();
void sparklePattern();


} /* namespace LED */

#endif
