#ifndef __MAIN_H__
#define __MAIN_H__

#include <WiFi.h>
#include <PubSubClient.h>

const char* ssid = "ManhTri";
const char* password = "18092003";
// char* topic = "zigbee/control";
const char* ON = "ON";
const char* OFF = "OFF";

#define MQTT_SERVER "192.168.137.1"
#define MQTT_PORT 1883
#define MQTT_TOPIC "zigbee/control"
// #define MQTT_USER "manhtri15"
// #define MQTT_PASSWORD "1"
// #define MQTT_LDP_TOPIC "IoTtest"

void setup_wifi();
void connect_to_broker();
// call back function when MQTT message come
void callback(char* topic, byte* payload, unsigned int length);

#endif