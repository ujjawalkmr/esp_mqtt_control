#ifndef CONFIG_H
#define CONFIG_H


// =====================================================
// ESP32 Setup Wi-Fi
// =====================================================

#define AP_SSID "ESP32_Setup"

#define AP_PASSWORD "12345678"
#define WIFI_SSID "A 313"
#define WIFI_PASSWORD "313rent313"


// =====================================================
// Web Server
// =====================================================

#define WEB_SERVER_PORT 80


// =====================================================
// Wi-Fi Connection
// =====================================================

#define WIFI_TIMEOUT 15000


// =====================================================
// Preferences
// =====================================================

#define PREFERENCES_NAMESPACE "wifi"

#define PREFERENCES_SSID "ssid"

#define PREFERENCES_PASSWORD "password"




// MQTT Broker
#define MQTT_SERVER     "broker.hivemq.com"
#define MQTT_PORT       8883
// #define MQTT_SERVER     "192.168.1.100"
// #define MQTT_PORT       1883

// MQTT topics
#define DEVICE_ID "ESP32_001"

#define MQTT_DEVICE_DATA      "esp/ESP32_001/data"
#define MQTT_DEVICE_COMMAND   "esp/ESP32_001/command"
#define MQTT_DEVICE_DISCOVERY  "esp/discovery/ESP32_001"


#endif  
  
  
  
  
  
  
                 FIRST TIME ONLY
                      │
                      ▼
              ┌──────────────┐
              │    ESP32     │
              │ Wi-Fi AP Mode│
              └──────┬───────┘
                     │
              creates its own Wi-Fi
                     │
                     ▼
             📱 / 💻 User connects
                     │
                     ▼
          http://192.168.4.1
                     │
                     ▼
          ┌─────────────────────┐
          │ Wi-Fi Configuration │
          │                     │
          │ SSID:     ________  │
          │ Password: ________  │
          │                     │
          │      [ Connect ]    │
          └──────────┬──────────┘
                     │
                     ▼
                  ESP32
                     │
              saves credentials
                     │
                     ▼
              Flash / NVS
                     │
                     ▼
             Connects to router
                     │
                     ▼
                  Internet


                  User enters:

SSID     = MyHomeWiFi
Password = myPassword123

             ↓

ESP32 receives them

             ↓

NVS stores:

SSID     → "MyHomeWiFi"
Password → "myPassword123"

             ↓

ESP32 connects to Wi-Fi


# Then, when you power off and power on the ESP32:
ESP32 starts
     ↓
Read SSID/password from NVS
     ↓
Credentials found?
     ↓
YES
     ↓
Connect automatically===================================

ESP32
  ↓
Check Preferences
  ↓
Wi-Fi credentials exist?
  ├── YES → connect automatically
  │
  └── NO → start ESP32 Wi-Fi
              ↓
          Web server
              ↓
       Wi-Fi name + password
              ↓
          Save in Preferences
              ↓
        Connect to Wi-Fi