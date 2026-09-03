#include "preferences_manager.h"
#include <Preferences.h>
#include "config.h"

namespace {

Preferences preferences;

}

void initPreferences() {

    preferences.begin(
        PREFERENCES_NAMESPACE,
        false
    );
}


String getSavedSSID() {

    return preferences.getString(
        PREFERENCES_SSID,
        ""
    );
}


String getSavedPassword() {

    return preferences.getString(
        PREFERENCES_PASSWORD,
        ""
    );
}


void saveWiFiCredentials(
    const String& ssid,
    const String& password
) {

    preferences.putString(
        PREFERENCES_SSID,
        ssid
    );

    preferences.putString(
        PREFERENCES_PASSWORD,
        password
    );
}


void clearWiFiCredentials() {

    preferences.clear();
}