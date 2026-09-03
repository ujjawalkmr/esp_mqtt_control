#include "web_server.h"

#include <WiFi.h>
#include <WebServer.h>

#include "config.h"
#include "wifi_manager.h"
#include "preferences_manager.h"

namespace {

WebServer server(WEB_SERVER_PORT);

void handleHomePage();
void handleSaveWiFi();

void handleHomePage() {
    Serial.println();
    Serial.println("==============================");
    Serial.println("HTTP REQUEST RECEIVED");
    Serial.println("==============================");

    const char* html = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <title>ESP32 Wi-Fi Setup</title>

    <style>
        body {
            font-family: Arial, sans-serif;
            background: #f4f4f4;
            padding: 20px;
        }

        .container {
            max-width: 400px;
            margin: 40px auto;
            background: white;
            padding: 25px;
            border-radius: 10px;
        }

        h2 {
            text-align: center;
        }

        label {
            font-weight: bold;
        }

        input {
            width: 100%;
            padding: 10px;
            margin-top: 5px;
            margin-bottom: 15px;
            box-sizing: border-box;
        }

        button {
            width: 100%;
            padding: 12px;
            background: #333;
            color: white;
            border: none;
            border-radius: 5px;
            cursor: pointer;
        }
    </style>
</head>

<body>

<div class="container">

    <h2>ESP32 Wi-Fi Setup</h2>

    <form action="/save" method="POST">

        <label>Wi-Fi Name</label>
        <input
            type="text"
            name="ssid"
            placeholder="Enter Wi-Fi name"
            required
        >

        <label>Wi-Fi Password</label>
        <input
            type="password"
            name="password"
            placeholder="Enter Wi-Fi password"
            required
        >

        <button type="submit">
            Connect
        </button>

    </form>

</div>

</body>
</html>
)rawliteral";

    server.send(200, "text/html", html);

    Serial.println("Web page sent to client.");
}


void handleSaveWiFi() {

    Serial.println();
    Serial.println("---------------------------------");
    Serial.println("Wi-Fi credentials received");
    Serial.println("---------------------------------");

    if (!server.hasArg("ssid") || !server.hasArg("password")) {

        server.send(
            400,
            "text/html",
            "<h2>SSID and password are required.</h2>"
        );

        return;
    }

    String ssid = server.arg("ssid");
    String password = server.arg("password");

    ssid.trim();

    Serial.print("SSID: ");
    Serial.println(ssid);

    Serial.println("Password received.");

    // Save credentials
    saveWiFiCredentials(ssid, password);

    Serial.println("Credentials saved.");

    // Send response BEFORE changing Wi-Fi mode
    server.send(
        200,
        "text/html",
        R"rawliteral(
<!DOCTYPE html>
<html>
<head>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <title>Connecting</title>
</head>

<body>

    <h2>Wi-Fi credentials saved.</h2>

    <p>
        ESP32 is connecting to your Wi-Fi...
    </p>

</body>
</html>
)rawliteral"
    );

    delay(500);

    // Try connecting to Wi-Fi
    bool connected = connectToWiFi(ssid, password);

    if (connected) {

        Serial.println();
        Serial.println("=================================");
        Serial.println("       SETUP COMPLETED");
        Serial.println("=================================");

        Serial.print("ESP32 IP: ");
        Serial.println(WiFi.localIP());

        stopAccessPoint();

    } else {

        Serial.println("Invalid Wi-Fi credentials.");

        clearWiFiCredentials();

        // Start AP again
        startAccessPoint();

        Serial.println("Setup mode restarted.");
        Serial.print("Open: http://");
        Serial.println(WiFi.softAPIP());
    }
}

} // END anonymous namespace


void startWebServer() {

    server.on("/", HTTP_GET, handleHomePage);

    server.on("/save", HTTP_POST, handleSaveWiFi);

    server.begin();

    Serial.println("Web Server started.");

    Serial.print("Open: http://");
    Serial.println(WiFi.softAPIP());
}


void handleWebServer() {

    server.handleClient();
}