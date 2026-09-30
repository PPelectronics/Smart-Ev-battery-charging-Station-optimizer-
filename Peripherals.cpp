#include <Arduino.h>
#include <DHT.h>
#include "State.h"
#include "Peripherals.h"
#include "config.h"

DHT dht(DHT_PIN, DHT_TYPE);

float mapFloat(long x, long inMin, long inMax, float outMin, float outMax) {
    return (x - inMin) * (outMax - outMin) / (float)(inMax - inMin) + outMin;
}

void sample_sensor(void)
{
    int raw_current = analogRead(CURRENT_PIN);   // 0 to 4095 -> 0 to 32A
    int raw_voltage = analogRead(VOLTAGE_PIN);    // 0 to 4095 -> 0 to 250V

    voltage = mapFloat(raw_voltage, 0, 4095, 0, 250);

    if (bayStatus == "CHARGING")
    {
        current = mapFloat(raw_current, 0, 4095, 0, 32);
    }

    power = voltage * current;

    // Read temperature
    float t = dht.readTemperature();
    if (!isnan(t)) temperature = t;
}

float recentAvgCurrent(void)
{
    float sum = 0;
    for (int i = 0; i < 5; i++)
    {
        sum = sum + current;
    }
    return sum / 5;
}

bool plugin_flag_once = true;
bool plugout_flag_once = true;

void plug_status(void)
{
    bool pluginReading = digitalRead(BTN_PLUGIN);

    if (pluginReading == LOW && plugin_flag_once)
    {
        sessionStartMs = millis();
        plugin_flag_once = false;

        if (bayStatus == "FREE")
        {
            bayStatus = "CHARGING";
            Serial.println("Bay1 plugin detected, bay is charging");
            // Relay is now driven by applyRelayDutyCycle() in optimization.cpp
        }
    }

    if (pluginReading == HIGH)
    {
        plugin_flag_once = true;
    }

    bool plugoutReading = digitalRead(BTN_PLUGOUT);

    if (plugoutReading == LOW && plugout_flag_once)
    {
        plugout_flag_once = false;

        if (bayStatus == "CHARGING")
        {
            bayStatus = "FREE";
            Serial.println("Bay1 plugout detected, bay is free");
            // Relay is now driven by applyRelayDutyCycle() in optimization.cpp
        }
    }

    if (plugoutReading == HIGH)
    {
        plugout_flag_once = true;
    }
}