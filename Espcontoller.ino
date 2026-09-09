#include "config.h"

#include "wifi_manager.h"
#include "web_server.h"
#include "preferences_manager.h"
#include "mqtt_manager.h"
#include <WiFi.h>


void setup() {

    Serial.begin(115200);

    delay(1000);


    Serial.println();
    Serial.println("=================================");
    Serial.println("          ESP32 STARTING");
    Serial.println("=================================");


    // ---------------------------------------------
    // Initialize Preferences
    // ---------------------------------------------

    initPreferences();


    // ---------------------------------------------
    // Read saved credentials
    // ---------------------------------------------

    // String savedSSID =
    //     getSavedSSID();

    // String savedPassword =
    //     getSavedPassword();
 String savedSSID =
       WIFI_SSID;

    String savedPassword =
        WIFI_PASSWORD;


    // ---------------------------------------------
    // Try saved Wi-Fi
    // ---------------------------------------------

    if (
        savedSSID.length() > 0 &&
        savedPassword.length() > 0
    ) {

        Serial.println(
            "Saved Wi-Fi credentials found."
        );

        Serial.print("SSID: ");
        Serial.println(savedSSID);


        bool connected =
            connectToWiFi(
                savedSSID,
                savedPassword
            );


        if (connected) {

            Serial.println(
                "Wi-Fi connected successfully."
            );

            Serial.print(
                "ESP32 IP Address: "
            );

            Serial.println(
                WiFi.localIP()
            );
            // Setup MQTT
    setupMQTT();

    // Connect MQTT
    reconnectMQTT();

            return;
        }


        // -----------------------------------------
        // Saved credentials are invalid
        // -----------------------------------------

        Serial.println(
            "Saved Wi-Fi connection failed."
        );

        Serial.println(
            "Removing old credentials..."
        );

        clearWiFiCredentials();
    }


    // ---------------------------------------------
    // Start setup mode
    // ---------------------------------------------

    Serial.println(
        "Starting Wi-Fi setup mode..."
    );


    if (startAccessPoint()) {

        startWebServer();
    }
}


void loop() {

   // handleWebServer();
     // Keep MQTT connection alive

    mqttLoop();


    // Publish every 5 seconds

    static unsigned long lastPublish = 0;


    if (millis() - lastPublish >= 60000)
    {
        lastPublish = millis();

        publishDeviceData();
    }
}