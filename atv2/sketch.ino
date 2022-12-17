#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <PubSubClient.h>
#include <WiFi.h>
 
#define R 0
#define G 1
#define B 2
 
#define TopicPublish1 "Luan/LedPotR"
#define TopicPublish2 "Luan/LedPotG"
#define TopicPublish3 "Luan/LedPotB"
 
int potWifi;

/* Pegar valores individuais R(0-255) | G(0-255) | B(0-255) | */
 
#define ID_MQTT "esp32_mqtt_sem2_LUAN"
 
const char *SSID = "Wokwi-GUEST";
const char *PASSWORD = "";
 
const char *BROKER_MQTT = "broker.hivemq.com";
 
int BROKER_PORT = 1883;
 
WiFiClient espClient;         // Cria o objeto espClient
PubSubClient MQTT(espClient); // Instancia o Cliente MQTT passando o objeto espClient
 
void initWiFi(void);
void initMQTT(void);
void callbackMQTT(char *topic, byte *payload, unsigned int length);
void reconnectMQTT(void);
void reconnectWiFi(void);
void checkWiFIAndMQTT(void);
 
 
void initWiFi(void){
  delay(10);
  Serial.println("------Conexao WI-FI------");
  Serial.print("Conectando-se na rede: ");
  Serial.println(SSID);
  Serial.println("Aguarde");
 
  reconnectWiFi();
}
 
void initMQTT(void)
{
  MQTT.setServer(BROKER_MQTT, BROKER_PORT);
  MQTT.setCallback(callbackMQTT);      
}
 
void callbackMQTT(char *topic, byte *payload, unsigned int length) {

  char pinos[3] = {R, G, B};
 
  char messageBuffer[30];
  memcpy(messageBuffer, payload, length);
  messageBuffer[length] = '\0';
 
  if(String(topic) == "Luan/LedPotR") {
    potWifi = strtol(messageBuffer, NULL, 10);
    analogWrite(pinos[0], potWifi);
  }
  if(String(topic) == "Luan/LedPotG") {
    potWifi = strtol(messageBuffer, NULL, 10);
    analogWrite(pinos[1], potWifi);
  }
  if(String(topic) == "Luan/LedPotB") {
    potWifi = strtol(messageBuffer, NULL, 10);
    analogWrite(pinos[2], potWifi);
  }
  
  Serial.printf("\n %s", topic);
  Serial.printf(": %d", potWifi);
  Serial.println();
 
}
 
 
void reconnectMQTT(void)
{
  while (!MQTT.connected()) {
    Serial.print("* Tentando se conectar ao Broker MQTT: ");
    Serial.println(BROKER_MQTT);
    if (MQTT.connect(ID_MQTT)) {
      Serial.println("Conectado com sucesso ao broker MQTT!");
      MQTT.subscribe(TopicPublish1);
      MQTT.subscribe(TopicPublish2);
      MQTT.subscribe(TopicPublish3);
    } else {
      Serial.println("Falha ao reconectar no broker.");
      Serial.println("Nova tentativa de conexao em 2 segundos.");
      delay(2000);
    }
  }
}
 
void checkWiFIAndMQTT(void) {
  if (!MQTT.connected())
    reconnectMQTT();
 
  reconnectWiFi();
}
 
void reconnectWiFi(void) {
 
  if (WiFi.status() == WL_CONNECTED)
    return;
 
  WiFi.begin(SSID, PASSWORD); // Conecta na rede WI-FI
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print(".");
  }
 
  Serial.println();
  Serial.print("Conectado com sucesso na rede ");
  Serial.print(SSID);
  Serial.println("IP obtido: ");
  Serial.println(WiFi.localIP());
}
void setup()
{
  Serial.begin(115200);
 
  pinMode(R, OUTPUT);
  pinMode(G, OUTPUT);
  pinMode(B, OUTPUT);
 
  initWiFi();
 
  initMQTT();
}
void loop() {
 
  checkWiFIAndMQTT();

  MQTT.loop();
 
  delay(1500);
 
}
