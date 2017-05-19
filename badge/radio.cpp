#include <RFM69.h>
#include <RFM69_ATC.h>
#include <SPI.h>
#include "radio.h"
#include "Badge.h"
#include "savecfg.h"

#define NETWORKID     0
#define GATEWAYID     1

#define FREQUENCY     RF69_915MHZ

// AES encryption (or not):

//#define ENCRYPT
//#define ENCRYPTKEY    "NOTASECRETPASSWD" // Use the same 16-byte key on all nodes

//Auto Transmission Control - dials down transmit power to save battery
#define ENABLE_ATC
#define ATC_RSSI -80

// Use ACKnowledge when sending messages (or not):

#define USEACK        false // Request ACKs or not

/* *** Radio *** */
namespace Radio {

#ifdef ENABLE_ATC
  RFM69_ATC radio;
#else
  RFM69 radio;
#endif

int TRANSMITPERIOD = 5000;
char buff[61];
byte sendSize=0;
long lastPeriod = 0;
unsigned int counter = 0;

void initiateRadio()
{
  byte myNodeID = cfgReadNodeID();

  // Initialize the RFM69HCW:
  radio.initialize(FREQUENCY, myNodeID, NETWORKID);
  radio.setPowerLevel(31);

  // Turn on encryption if desired:
  //if (ENCRYPT)
#ifdef ENCRYPT
  radio.encrypt(ENCRYPTKEY);
#endif

#ifdef ENABLE_ATC
  radio.enableAutoPower(ATC_RSSI);
#endif

  sprintf(buff, "\nTransmitting at %d Mhz...", FREQUENCY==RF69_433MHZ ? 433 : FREQUENCY==RF69_868MHZ ? 868 : 915);
  Serial.println(buff);

#ifdef ENABLE_ATC
  Serial.println("RFM69_ATC Enabled (Auto Transmission Control)\n");
#endif

}

void receiveRadio()
{
  if (radio.receiveDone())
  {
    Serial.print('[');Serial.print(radio.SENDERID, DEC);Serial.print("] ");
    for (byte i = 0; i < radio.DATALEN; i++)
      Serial.print((char)radio.DATA[i]);
    Serial.print("   [RX_RSSI:");Serial.print(radio.RSSI);Serial.print("]");

    if (radio.ACKRequested()) {
      radio.sendACK();
      Serial.print(" - ACK sent");
    }
    Serial.println();
  }
}

void ping()
{
  int currPeriod = millis()/TRANSMITPERIOD;

  if (currPeriod != lastPeriod) {
    lastPeriod=currPeriod;

    sprintf(buff, "0|%.2X|%.4X|%.4X", cfgReadNodeID(), cfgReadNodeTag(), counter);
    byte buffLen=strlen(buff);
    radio.sendWithRetry(GATEWAYID, buff, buffLen);
    counter++;
  }
}

void printRadioRegs()
{
  radio.readAllRegs();
}

void printTemperature()
{
  byte temperature = radio.readTemperature(-1);
  byte fTemp = 1.8 * temperature + 32;
  // converting to F loses some resolution, obvious when C is on
  // edge between 2 values (ie 26C=78F, 27C=80F)
  Serial.print( "Radio Temp is ");
  Serial.print(fTemp);
  Serial.println('F');
}

} /* namespace Radio */
