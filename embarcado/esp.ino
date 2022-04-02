#include <Arduino.h>
 
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_BMP280.h>
#include <PubSubClient.h>
#include <ESP8266WiFi.h>
 
const char* ssid = "seu ssid";
const char* password = "sua senhha wifi";
const char* mqtt_server = "mqtt_server";
const char* channel = "sensor";
 
WiFiClient espClient;
PubSubClient client(espClient);
Adafruit_BMP280 bmp; 
 
void setup() {
  Serial.begin(9600);
 if (!bmp.begin(0x76)) {
    Serial.println(F("Não foi possível encontrar um sensor BMP280 válido, verifique a fiação!"));
    while (1);
  }
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Wifi conectado");
  client.setServer(mqtt_server, 1883);
}
 
void reconnect() {
  // Faz loop até sermos reconectados
  while (!client.connected()) {
    Serial.print("Tentando conexão MQTT ...");
    // Crie um ID de cliente aleatório
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Tentativa de conexão
    if (client.connect(clientId.c_str())) {
      Serial.println("conectado");
    } else {
      Serial.print("falhou, rc=");
      Serial.print(client.state());
      Serial.println(" tente novamente em 5 segundos");
      // Aguarde 5 segundos antes de tentar novamente
      delay(5000);
    }
  }
}
 
void loop() {
 
  if (!client.connected()) {
    reconnect();
  }
 
  float temp = bmp.readTemperature();
  float press = bmp.readPressure();
  
  String v1 = ("temp,site=room1 value=" + String(temp));
  client.publish(channel, v1.c_str(), true);
 
  v1 = ("press,site=room1 value=" + String(press));
  client.publish(channel, v1.c_str(), true);
  
  delay(60000);
}