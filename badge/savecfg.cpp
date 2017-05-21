#include <EEPROMex.h>
#include "savecfg.h"
#include "Badge.h"

int versionLength = 7;
byte badgeVersion[] = {1, 1, 2, 4 , 8 , 16 , 32 };

int cfgVersion;
int cfgNodeID;
int cfgNodeTag;
int cfgPatternID;

// Generate a seed based on analog pins 0-5
// This should create enough randomness for self addressing
long generateSeed()
{
  int r[6];
  int t;
  for (int i=0; i<6; i++){
    t = analogRead(i);
    if (t == 0) {
      r[i] = 1;
    } else {
      r[i] = t;
    }
  }
  return r[0] * r[1] * r[2] - r[3] * r[4] + r[5];
}

void initiateCfg()
{
  byte localVersion[versionLength];
  long seed;
  long r;

  cfgVersion = EEPROM.getAddress(sizeof(byte)*versionLength);
  cfgNodeID = EEPROM.getAddress(sizeof(byte));
  cfgNodeTag = EEPROM.getAddress(sizeof(int));
  cfgPatternID = EEPROM.getAddress(sizeof(byte));

  EEPROM.readBlock<byte>(cfgVersion, localVersion, versionLength);
  if (memcmp(localVersion, badgeVersion, versionLength) != 0) {
    Serial.println("[+] New Badge.");
    EEPROM.updateBlock<byte>(cfgVersion, badgeVersion, versionLength);

    Serial.println("[+] Configuring wireless address");

    // Generate NodeID
    seed = generateSeed();
    DEBUG_PRINT("[+] Seed:");
    DEBUG_PRINTLN(seed);
    randomSeed(seed);
    r = random(3,250);
    DEBUG_PRINT("[+] r:");
    DEBUG_PRINTLN(r);
    cfgUpdateNodeID(r);

    delayMicroseconds(200);

    // Generate NodeTag
    seed = generateSeed();
    DEBUG_PRINT("[+] Seed:");
    DEBUG_PRINTLN(seed);
    randomSeed(seed);
    r = random(3,999999);
    DEBUG_PRINT("[+] r:");
    DEBUG_PRINTLN(r);
    cfgUpdateNodeTag(r);
    cfgUpdatePatternID(0);
  }
}

byte cfgReadNodeID()
{
  return EEPROM.read(cfgNodeID);
}

bool cfgUpdateNodeID(byte id)
{
  return EEPROM.updateByte(cfgNodeID, id);
}

unsigned int cfgReadNodeTag()
{
  return EEPROM.readInt(cfgNodeTag);
}

bool cfgUpdateNodeTag(int id)
{
  return EEPROM.updateInt(cfgNodeTag, id);
}

byte cfgReadPatternID()
{
  return EEPROM.read(cfgNodeID);
}

bool cfgUpdatePatternID(byte id)
{
  return EEPROM.updateByte(cfgNodeID, id);
}

