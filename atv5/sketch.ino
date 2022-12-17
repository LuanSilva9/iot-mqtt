#include <PubSubClient.h>
#include <WiFi.h>

#define pinInterruptor 10
#define pinSound 12

#define topico "Luan/Temperatura"

#define ID_MQTT "esp32_mqtt_sem2_LUAN"
 
const char *SSID = "Wokwi-GUEST";
const char *PASSWORD = "";
 
const char *BROKER_MQTT = "broker.hivemq.com";

int LeituraInterruptor;

int BROKER_PORT = 1883;

WiFiClient espClient;  
PubSubClient MQTT(espClient);

void initWiFi(void);
void initMQTT(void);
void callbackMQTT(char *topic, byte *payload, unsigned int length);
void reconnectMQTT(void);
void reconnectWiFi(void);
void checkWiFIAndMQTT(void);

void activeBuzzer(void);

void activeBuzzer(void) {
  return tone(pinSound, 500, 500);
}

void initWiFi(void) {
  delay(10);
  Serial.println("------Conexao WI-FI------");
  Serial.print("Conectando-se na rede: ");
  Serial.println(SSID);
  Serial.println("Aguarde");
 
  reconnectWiFi();
}
 
void initMQTT(void) {
  MQTT.setServer(BROKER_MQTT, BROKER_PORT);
  MQTT.setCallback(callbackMQTT);      
}

void callbackMQTT(char *topic, byte *payload, unsigned int length) {
  char tempA[30];
  memcpy(tempA, payload, length);

  tempA[length] = '\0';


  if(strtol(tempA, NULL, 10) > 70.00) {
    if(LeituraInterruptor == 1) {
      return activeBuzzer();
    }
    else {
      Serial.println("* Você precisa ativar o Interruptor para o Sensor de Temperatura!");
    }
  }
  else {
    Serial.println(tempA);
  }
}
 
 
void reconnectMQTT(void)
{
  while (!MQTT.connected()) {
    Serial.print("* Tentando se conectar ao Broker MQTT: ");
    Serial.println(BROKER_MQTT);
    if (MQTT.connect(ID_MQTT)) {
      MQTT.subscribe(topico);
      Serial.println("Conectado com sucesso ao broker MQTT!");
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
  pinMode(pinInterruptor, INPUT_PULLUP);
 
  
  pinMode(pinSound, OUTPUT);

  initWiFi();
  initMQTT();
}
void loop() {
  checkWiFIAndMQTT();

  if(digitalRead((10)) == 1) {
    LeituraInterruptor = 1;
  } 
  else if (digitalRead((10)) == 0) {
    LeituraInterruptor = 0;
  }
  else {
    Serial.println("Ai você quebrou a quarta parede");
  }

  MQTT.loop();
 
  delay(1500);
 
}


// Maquinas Podem Pensar? 