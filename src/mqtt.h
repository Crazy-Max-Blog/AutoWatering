#pragma once

#include <PubSubClient.h>

#include "sensor/sensor.h"

namespace mqtt
{
    WiFiClient espClient;
    PubSubClient client(espClient);

    void reconnect()
    {
        if (db::db[kk::mqtt_en])
        {
            // while (!client.connected())
            //{
            Serial.println("Connecting to MQTT Broker...");
            if (client.connect("ESP32Client", db::db[kk::mqtt_user].c_str(), db::db[kk::mqtt_pass].c_str()))
            {
                Serial.println("Connected to MQTT Broker!");
                client.subscribe("autowater/water_1");
            }
            else
            {
                Serial.print("Failed, rc=");
                Serial.print(client.state());
                Serial.println(" Retrying in 5s...");
                // delay(5000);
            }
            //}
        }
    }

    void callback(char *topic, byte *payload, unsigned int length)
    {
        Serial.print("Message arrived [");
        Serial.print(topic);
        Serial.print("]: ");

        String message;
        for (int i = 0; i < length; i++)
        {
            message += (char)payload[i];
        }
        Serial.println(message);

        if (strcmp(topic, "autowater/water_1") == 0 && message == "1")
        {
            Serial.println("123");
            sensor::water(0);
            client.publish("autowater/water_1", "0");
        }
    }

    void init()
    {
        if (db::db[kk::mqtt_en])
        {
            client.setServer(db::db[kk::mqtt_host].c_str(), db::db[kk::mqtt_port].toInt16());
            // client.setServer("m4.wqtt.ru", 10084);
            client.setCallback(callback);
            reconnect();
        }
    }

    void tick()
    {
        if (db::db[kk::mqtt_en])
        {
            static long timer = 0;
            long mil = millis();
            if (mil - timer >= 5000)
            {
                timer = mil;
                if (!client.connected())
                    reconnect();
                else
                {
                    client.loop();

                    // Publish a test message every 5 seconds
                    client.publish("esp32/temperature", "25°C"); // Replace with real sensor data
                }
            }
        }
    }
}