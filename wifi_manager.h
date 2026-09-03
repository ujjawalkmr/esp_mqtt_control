#ifndef WIFI_MANAGER_H
#define WIFI_MANAGER_H

#include <Arduino.h>

bool connectToWiFi(
    const String& ssid,
    const String& password
);

bool startAccessPoint();

void stopAccessPoint();

#endif