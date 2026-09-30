#include "State.h"

String bayStatus = "FREE";
float voltage = 0.0, current = 0.0, power = 0.0, energyWh = 0.0, temperature = 0.0;
unsigned long sessionStartMs = 0;

// edge ai variables
float predictedArrivalProb = 0.0;
int   predictedDurationMin = 0;
int   lastHourOfDay = 12;

// optimization variables — SRS 8.7
bool   overloadActive = false;
String loadDecision   = "ALLOW";
int    throttleLevel  = 100;