// Circuitos disponiveis no https://github.com/Luan16p

#include <PubSubClient.h>
#include <WiFi.h>

#define pino1 4
#define pino2 1
#define pino3 2
#define TopicPublish1 "Luan/LedPotR"
#define TopicPublish2 "Luan/LedPotG"
#define TopicPublish3 "Luan/LedPotB"

#define ID_MQTT "esp32_mqtt_pot_LUAN" // id mqtt (para identificação de sessão)
const char *SSID = "Wokwi-GUEST";
const char *PASSWORD = ""; 

const char *BROKER_MQTT = "broker.hivemq.com";

int BROKER_PORT = 1883; 

static char databasePot1[10] = {0};
static char databasePot2[10] = {0};
static char databasePot3[10] = {0};

WiFiClient espClient;         
PubSubClient MQTT(espClient); 
void initWiFi(void);
void initMQTT(void);
void callbackMQTT(char *topic, byte *payload, unsigned int length);
void reconnectMQTT(void);
void reconnectWiFi(void);
void checkWiFIAndMQTT(void);


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
  MQTT.setServer(BROKER_MQTT, BROKER_PORT);    
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

void checkWiFIAndMQTT(void) {
  if (!MQTT.connected())
    reconnectMQTT(); // se não há conexão com o Broker, a conexão é refeita

  reconnectWiFi(); // se não há conexão com o WiFI, a conexão é refeita
}

void reconnectWiFi(void)
{
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


void setup()
{
  Serial.begin(115200);

  pinMode(pino1, INPUT);
  pinMode(pino2, INPUT);
  pinMode(pino3, INPUT);

  initWiFi();
  initMQTT();
}

void loop() {
  int ReadPotentiometer1 = analogRead(pino1); 
  int ReadPotentiometer2 = analogRead(pino2); 
  int ReadPotentiometer3 = analogRead(pino3); 

  sprintf(databasePot1, "%d", map(ReadPotentiometer1, 0, 8191, 0, 511));
  sprintf(databasePot2, "%d", map(ReadPotentiometer2, 0, 8191, 0, 511));
  sprintf(databasePot3, "%d", map(ReadPotentiometer3, 0, 8191, 0, 511));

  checkWiFIAndMQTT();

  MQTT.publish(TopicPublish1, databasePot1);
  delay(1000);
  MQTT.publish(TopicPublish2, databasePot2);
  delay(1000);
  MQTT.publish(TopicPublish3, databasePot3);

  MQTT.loop();

  delay(1500);

}
