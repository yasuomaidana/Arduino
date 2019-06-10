#include <Arduino.h>
#include <MqttConnector.h>
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
#include <WiFiConnector.h>
#include <DHT.h>

#define DHTPIN 12
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
DHT dht(DHTPIN, DHTTYPE);

MqttConnector *mqtt;

#define MQTT_HOST         "mqtt.espert.io"
#define MQTT_PORT         1883
#define MQTT_USERNAME     ""
#define MQTT_PASSWORD     ""
#define MQTT_CLIENT_ID    ""
#define MQTT_PREFIX       "/CMMC"
#define PUBLISH_EVERY     (5*1000)// every 5 seconds

/* DEVICE DATA & FREQUENCY */
#define DEVICE_NAME       "CNX-CMMC-001"
/* WIFI INFO */
#ifndef WIFI_SSID
  #define WIFI_SSID        ""
  #define WIFI_PASSWORD    ""
#endif



WiFiConnector wifi(WIFI_SSID, WIFI_PASSWORD);

#include "_publish.h"
#include "_receive.h"
#include "init_mqtt.h"

void init_hardware()
{
  pinMode(DHTPIN, INPUT_PULLUP);
  Serial.begin(115200);
  delay(10);
  dht.begin();
  Serial.println();
  Serial.println("BEGIN");
}

void init_wifi() {
  wifi.init();

  wifi.on_connected([&](const void* message)
  {
    Serial.print("WIFI CONNECTED WITH IP: ");
    Serial.println(WiFi.localIP());
  });

  wifi.on_connecting([&](const void* message)
  {
    Serial.print("Connecting to ");
    Serial.println(wifi.get("ssid") + ", " + wifi.get("password"));
    delay(200);
  });

  wifi.on_disconnected([&](const void* message) {
    // if (mqtt != NULL) {
    //   delete mqtt;
    //   mqtt = NULL;
    // }
  });
}


void setup()
{
  init_hardware();
  init_mqtt();
  init_wifi();
  wifi.connect();
  mqtt->connect();
}

void loop()
{
  wifi.loop();
  if (wifi.connected()) {
    mqtt->loop();     
  }
}
