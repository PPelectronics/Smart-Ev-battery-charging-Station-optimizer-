#include <Arduino.h>
#include <WiFi.h>
#include "config.h"
#include "Peripherals.h"
#include "State.h"
#include "Network.h"
#include "Telemetry.h"
#include "optimization.h"
#include "model.h"
#include "edgeai.h"

unsigned long lastSensorRead = 0;
const unsigned long SENSOR_READ_INTERVAL_MS = 2000;

void setup()
{
    Serial.begin(115200);
    delay(500);

    // config peripheral pins
    pinMode(BTN_PLUGIN, INPUT_PULLUP);
    pinMode(BTN_PLUGOUT, INPUT_PULLUP);

    pinMode(RELAY_PIN, OUTPUT);
    pinMode(LED_GREEN, OUTPUT);
    pinMode(LED_YELLOW, OUTPUT);
    pinMode(LED_RED, OUTPUT);

    digitalWrite(RELAY_PIN, LOW);

    // initialize sensor
    dht.begin();

    // config esp32 with real time
    configTime(0, 0, "pool.ntp.org", "time.nist.gov");

    updateLeds();   // start in FREE state -> Green LED ON

    Serial.println("Smart EV Charging Bay - Ready");

    // connect board to wifi
    connectWiFi();

    // Configure MQTT server
    mqtt.setServer(MQTT_SERVER, MQTT_PORT);

    // connect board to the cloud
    connectMQTT();  // token, device id
}

void loop()
{
    plug_status();

    unsigned long now = millis();
    if (now - lastSensorRead >= SENSOR_READ_INTERVAL_MS)
    {
        lastSensorRead = now;

        // read data from sensor: voltage, current, temperature, power
        sample_sensor();

        // run AI to get prediction
        runEdgeAIInference();

        // decide ALLOW / THROTTLE / DEFER
        runOptimization();

        // publish the data
        publishTelemetry();
    }

    // relay duty-cycling & LEDs need to run every loop, not gated by the
    // 2s sensor interval, so throttling actually toggles the relay
    applyRelayDutyCycle();
    updateLeds();
}