#ifndef PREFERENCES_MANAGER_H
#define PREFERENCES_MANAGER_H

#include <Arduino.h>

void initPreferences();

String getSavedSSID();

String getSavedPassword();

void saveWiFiCredentials(
    const String& ssid,
    const String& password
);

void clearWiFiCredentials();

#endif