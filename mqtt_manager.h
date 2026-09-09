#ifndef MQTT_MANAGER_H
#define MQTT_MANAGER_H

void setupMQTT();
void reconnectMQTT();
void mqttLoop();
void publishDeviceData();
void publishDiscovery();

#endif