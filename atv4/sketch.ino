#include <PubSubClient.h>
#include <WiFi.h>

#include <DHTesp.h>

#define pinTemp 2

#define topicValueTemp "Luan/Temperatura"

#define ID_MQTT "esp32_mqtt_LUAN"

DHTesp dht;

const char *SSID = "Wokwi-GUEST";
const char *PASSWORD = "";      

const char *BROKER_MQTT = "broker.hivemq.com";

int BROKER_PORT = 1883; 

static char tempA[10] = {0};

WiFiClient espClient;        
PubSubClient MQTT(espClient); 

float getTemperature(void);

void initWiFi(void);
void initMQTT(void);
void callbackMQTT(char *topic, byte *payload, unsigned int length);
void reconnectMQTT(void);
void reconnectWiFi(void);
void checkWiFIAndMQTT(void);

float getTemperature(void)
{
  TempAndHumidity data = dht.getTempAndHumidity();

  if (!(isnan(data.temperature)))
    return data.temperature;
  else
    return -99.99;
}

void initWiFi(void)
{
  delay(10);
  Serial.println("------Conexao WI-FI------");
  Serial.print("Conectando-se na rede: ");
  Serial.println(SSID);
  Serial.println("Aguarde");

  reconnectWiFi();
}
void initMQTT(void) {
  MQTT.setServer(BROKER_MQTT, BROKER_PORT); // Informa qual broker e porta deve ser conectado
  MQTT.setCallback(callbackMQTT);           // Atribui função de callback (função chamada quando qualquer informação de um dos tópicos subescritos chega)
}
void callbackMQTT(char *topic, byte *payload, unsigned int length) {
  
}

void reconnectMQTT(void)
{
  while (!MQTT.connected()) {
    Serial.print("* Tentando se conectar ao Broker MQTT: ");
    Serial.println(BROKER_MQTT);
    if (MQTT.connect(ID_MQTT)) {
      Serial.println("Conectado com sucesso ao broker MQTT!");
    } else {
      Serial.println("Falha ao reconectar no broker.");
      Serial.println("Nova tentativa de conexao em 2 segundos.");
      delay(2000);
    }
  }
}
void checkWiFIAndMQTT(void)
{
  if (!MQTT.connected())
    reconnectMQTT(); 

  reconnectWiFi();
}
void reconnectWiFi(void) {
  if (WiFi.status() == WL_CONNECTED)
    return;

  WiFi.begin(SSID, PASSWORD); 

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

void setup() {
  Serial.begin(115200);

  dht.setup(pinTemp, DHTesp::DHT22);

  initWiFi();

  initMQTT();
  
}
void loop() {
  checkWiFIAndMQTT();
  sprintf(tempA, "%.2f", getTemperature());

  MQTT.publish(topicValueTemp, tempA);

  Serial.printf("\n[ Broker ] - Temperatura: %s", tempA);

  MQTT.loop();

  delay(2001);
}

