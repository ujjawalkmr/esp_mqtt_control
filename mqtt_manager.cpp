#include "mqtt_manager.h"
#include "config.h"

#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>


WiFiClientSecure secureClient;
PubSubClient mqttClient(secureClient);


void publishDiscovery()
{
    String message = "{";

    message += "\"deviceId\":\"";
    message += DEVICE_ID;
    message += "\",";

    message += "\"deviceName\":\"Living Room ESP\",";

    message += "\"deviceType\":\"ESP32\",";

    message += "\"status\":\"online\"";

    message += "}";

    bool result = mqttClient.publish(
        MQTT_DEVICE_DISCOVERY,
        message.c_str(),
        true
    );

    if (result)
    {
        Serial.println("Discovery message published!");

        Serial.print("Topic: ");
        Serial.println(MQTT_DEVICE_DISCOVERY);

        Serial.print("Message: ");
        Serial.println(message);
    }
    else
    {
        Serial.println("Discovery publish failed!");
    }
}
// ========================================
// MQTT MESSAGE RECEIVED
// ========================================

void mqttCallback(
    char* topic,
    byte* payload,
    unsigned int length
)
{
    Serial.println();
    Serial.println("========== MQTT MESSAGE ==========");

    Serial.print("Topic: ");
    Serial.println(topic);

    Serial.print("Message: ");

    for (unsigned int i = 0; i < length; i++)
    {
        Serial.print((char)payload[i]);
    }

    Serial.println();

    Serial.println("==================================");
}


// ========================================
// MQTT SETUP
// ========================================

void setupMQTT()
{
    /*
       For testing only.

       This tells ESP32 to accept the
       HiveMQ TLS certificate without
       certificate verification.
    */
    secureClient.setInsecure();

    mqttClient.setServer(
        MQTT_SERVER,
        MQTT_PORT
    );

    mqttClient.setCallback(
        mqttCallback
    );

    mqttClient.setKeepAlive(60);
}


// ========================================
// MQTT RECONNECT
// ========================================

void reconnectMQTT()
{
    while (!mqttClient.connected())
    {
        Serial.println();
        Serial.println("Connecting to HiveMQ...");

        String clientId = DEVICE_ID;

        clientId += "_";
        clientId += String(
            random(0xffff),
            HEX
        );

        bool connected = mqttClient.connect(
            clientId.c_str()
        );

        if (connected)
        {
            Serial.println(
                "MQTT Connected to HiveMQ!"
            );

            // Subscribe
            bool subscribed = mqttClient.subscribe(
                MQTT_DEVICE_COMMAND
            );

            if (subscribed)
            {
                Serial.print(
                    "Subscribed: "
                );

                Serial.println(
                    MQTT_DEVICE_COMMAND
                );
            }
             publishDiscovery();
        }
        else
        {
            Serial.print(
                "MQTT connection failed. Error: "
            );

            Serial.println(
                mqttClient.state()
            );

            delay(5000);
        }
    }
}


// ========================================
// MQTT LOOP
// ========================================

void mqttLoop()
{
    if (!mqttClient.connected())
    {
        reconnectMQTT();
    }

    mqttClient.loop();
}


// ========================================
// PUBLISH ESP32 DATA
// ========================================

void publishDeviceData()
{
    String message = "{";

    message += "\"deviceId\":\"";
    message += DEVICE_ID;
    message += "\",";

    message += "\"temperature\":28.5,";

    message += "\"status\":\"ON\"";

    message += "}";


    Serial.println();
    Serial.println("Publishing...");

    Serial.print("Topic: ");
    Serial.println(
        MQTT_DEVICE_DATA
    );

    Serial.print("Message: ");
    Serial.println(message);


    bool result = mqttClient.publish(
        MQTT_DEVICE_DATA,
        message.c_str()
    );


    if (result)
    {
        Serial.println(
            "Message Published Successfully!"
        );
    }
    else
    {
        Serial.println(
            "Message Publish Failed!"
        );
    }
}