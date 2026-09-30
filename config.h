#ifndef CONFIG_H
#define CONFIG_H

// ---------------------------------------------------------------------
// Pin configuration — SRS Section 8.1
// ---------------------------------------------------------------------
#define VOLTAGE_PIN   34
#define CURRENT_PIN   35
#define DHT_PIN       15
#define RELAY_PIN     26
#define BTN_PLUGIN    32
#define BTN_PLUGOUT   33
#define LED_GREEN     18
#define LED_YELLOW    19
#define LED_RED       21

#define DHT_TYPE DHT22

// ---------------- WiFi Details ----------------
constexpr char* WIFI_SSID = "Wokwi-GUEST";
constexpr char* WIFI_PASS = "";

// ---------------- ThingsBoard Details ----------------
constexpr char* MQTT_SERVER = "mqtt.thingsboard.cloud";
const int MQTT_PORT = 1883;

// ThingsBoard Device Access Token
constexpr char* TB_TOKEN = "2fczbkHcrjGKxIqS3P5T";
constexpr char* BAY_ID = "BAY1";

// ---------------- Optimization thresholds — SRS 8.7 ----------------
constexpr int peakTariffStartHr              = 18;     // peak tariff window start (24h)
constexpr int peakTariffEndHr                = 21;     // peak tariff window end (24h)
constexpr float predictionThreshold          = 0.5f;   // min arrival probability -> STANDBY_EXPECTING
constexpr float overloadCurrentA             = 28.0f;  // per-bay overcurrent limit (A)
constexpr float maxStationLoadW              = 6000.0f;// station-wide power cap (W)
constexpr unsigned long DUTY_CYCLE_WINDOW_MS = 2000;   // relay duty-cycle window (ms)

#endif