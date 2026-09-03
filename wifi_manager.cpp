#include "wifi_manager.h"

#include <WiFi.h>

#include "config.h"


bool connectToWiFi(
    const String& ssid,
    const String& password
) {

    Serial.println();
    Serial.println("---------------------------------");
    Serial.println("Connecting to Wi-Fi");
    Serial.println("---------------------------------");

    Serial.print("SSID: ");
    Serial.println(ssid);

    WiFi.mode(WIFI_STA);

    WiFi.begin(
        ssid.c_str(),
        password.c_str()
    );

    unsigned long startTime = millis();

    while (
        WiFi.status() != WL_CONNECTED &&
        millis() - startTime < WIFI_TIMEOUT
    ) {

        delay(500);

        Serial.print(".");
    }

    Serial.println();

    if (WiFi.status() == WL_CONNECTED) {

        Serial.println("Wi-Fi connected!");

        Serial.print("IP Address: ");
        Serial.println(WiFi.localIP());

        return true;
    }

    Serial.println("Wi-Fi connection failed.");

    WiFi.disconnect();

    return false;
}


bool startAccessPoint() {

    Serial.println();
    Serial.println("=================================");
    Serial.println("       WIFI SETUP MODE");
    Serial.println("=================================");

    WiFi.mode(WIFI_AP);

    bool result = WiFi.softAP(
        AP_SSID,
        AP_PASSWORD
    );

    if (!result) {

        Serial.println(
            "ERROR: Failed to start Access Point."
        );

        return false;
    }

    Serial.println("Access Point started.");

    Serial.print("Wi-Fi Name: ");
    Serial.println(AP_SSID);

    Serial.print("Wi-Fi Password: ");
    Serial.println(AP_PASSWORD);

    Serial.print("ESP32 IP Address: ");
    Serial.println(WiFi.softAPIP());

    return true;
}


void stopAccessPoint() {

    Serial.println("Stopping Access Point...");

    WiFi.softAPdisconnect(true);

    Serial.println("Access Point stopped.");
}