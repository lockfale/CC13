#ifndef radio_h
#define radio_h
#include <Arduino.h>

/* *** Radio *** */
namespace Radio {

void initiateRadio();
void receiveRadio();
void ping();
void printRadioRegs();
void printTemperature();

} /* namespace Radio */
#endif
