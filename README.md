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