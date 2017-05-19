#ifndef savecfg_h
#define savecfg_h

void initiateCfg();

byte cfgReadNodeID();
bool cfgUpdateNodeID(byte);

unsigned int cfgReadNodeTag();
bool cfgUpdateNodeTag(int);
byte cfgReadPatternID();
bool cfgUpdatePatternID(byte);

#endif
