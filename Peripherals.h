#ifndef PERIPHERALS_H
#define PERIPHERALS_H
#include <DHT.h>

extern DHT dht;

void sample_sensor(void);
void plug_status(void);
float recentAvgCurrent(void);

#endif