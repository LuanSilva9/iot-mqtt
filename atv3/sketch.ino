#include <DHTesp.h>
#include <PubSubClient.h>
#include <WiFi.h>
  
#define ID_MQTT "esp32_mqtt_pot_LUAN"

#define TOPIC_1 "Luan/LedPotR" 
#define TOPIC_2 "Luan/LedPotG"
#define TOPIC_3 "Luan/LedPotB"

#define pin1 0
#define pin2 1
#define pin3 2
#define pin4 3
#define pin5 4
#define pin6 5
#define pin7 6
#define pin8 7
#define pin9 10
#define pin10 11

static char dataPin[10] = {pin1, pin2, pin3, pin4, pin5, pin6, pin7, pin8, pin9, pin10};

/* 
  Mar de variaveis a Seguir: 
*/

int potR, potG, potB;

int potX = 511;

int pot10 = potX*10/100;
int pot20 = potX*20/100;
int pot30 = potX*30/100;
int pot40 = potX*40/100;
int pot50 = potX*50/100;
int pot60 = potX*60/100;
int pot70 = potX*70/100;
int pot80 = potX*80/100;
int pot90 = potX*90/100;
int pot100 = potX;


const char *SSID = "Wokwi-GUEST";
const char *PASSWORD = "";
 
const char *BROKER_MQTT = "broker.hivemq.com";
 
int BROKER_PORT = 1883;
 
WiFiClient espClient;       
PubSubClient MQTT(espClient); 
 
void initWiFi(void);
void initMQTT(void);
void callbackMQTT(char *topic, byte *payload, unsigned int length);
void reconnectMQTT(void);
void reconnectWiFi(void);
void checkWiFIAndMQTT(void);

void maiorForR(void);
void maiorForG(void);
void maiorForB(void);

void maiorForR(void) {

  // Serial.printf("\n Potenciometro R: %i", potR);

    if(potR < pot10) {
      analogWrite(pin1, LOW);
      analogWrite(pin2, LOW);
      analogWrite(pin3, LOW);
      analogWrite(pin4, LOW);
      analogWrite(pin5, LOW);
      analogWrite(pin6, LOW);
      analogWrite(pin7, LOW);
      analogWrite(pin8, LOW);
      analogWrite(pin9, LOW);
      analogWrite(pin10, LOW);
    }

    if(potR >= pot10 && potR < pot20) {
      analogWrite(pin1, HIGH);
      analogWrite(pin2, LOW);
      analogWrite(pin3, LOW);
      analogWrite(pin4, LOW);
      analogWrite(pin5, LOW);
      analogWrite(pin6, LOW);
      analogWrite(pin7, LOW);
      analogWrite(pin8, LOW);
      analogWrite(pin9, LOW);
      analogWrite(pin10, LOW);
    }

    if(potR >= pot20 && potR < pot30) {
      analogWrite(pin1, HIGH);
      analogWrite(pin2, HIGH);
      analogWrite(pin3, LOW);
      analogWrite(pin4, LOW);
      analogWrite(pin5, LOW);
      analogWrite(pin6, LOW);
      analogWrite(pin7, LOW);
      analogWrite(pin8, LOW);
      analogWrite(pin9, LOW);
      analogWrite(pin10, LOW);
    
    }

    if(potR >= pot30 && potR < pot40) {
      analogWrite(pin1, HIGH);
      analogWrite(pin2, HIGH);
      analogWrite(pin3, HIGH);
      analogWrite(pin4, LOW);
      analogWrite(pin5, LOW);
      analogWrite(pin6, LOW);
      analogWrite(pin7, LOW);
      analogWrite(pin8, LOW);
      analogWrite(pin9, LOW);
      analogWrite(pin10, LOW);
    }

    if(potR >= pot40 && potR < pot50) {
      analogWrite(pin1, HIGH);
      analogWrite(pin2, HIGH);
      analogWrite(pin3, HIGH);
      analogWrite(pin4, HIGH);
      analogWrite(pin5, LOW);
      analogWrite(pin6, LOW);
      analogWrite(pin7, LOW);
      analogWrite(pin8, LOW);
      analogWrite(pin9, LOW);
      analogWrite(pin10, LOW);
    }

    if(potR >= pot50 && potR < pot60) {
      analogWrite(pin1, HIGH);
      analogWrite(pin2, HIGH);
      analogWrite(pin3, HIGH);
      analogWrite(pin4, HIGH);
      analogWrite(pin5, HIGH);
      analogWrite(pin6, LOW);
      analogWrite(pin7, LOW);
      analogWrite(pin8, LOW);
      analogWrite(pin9, LOW);
      analogWrite(pin10, LOW);
    }

    if(potR >= pot60 && potR < pot70) {
      analogWrite(pin1, HIGH);
      analogWrite(pin2, HIGH);
      analogWrite(pin3, HIGH);
      analogWrite(pin4, HIGH);
      analogWrite(pin5, HIGH);
      analogWrite(pin6, HIGH);
      analogWrite(pin7, LOW);
      analogWrite(pin8, LOW);
      analogWrite(pin9, LOW);
      analogWrite(pin10, LOW);
    }

    if(potR >= pot70 && potR < pot80) {
      analogWrite(pin1, HIGH);
      analogWrite(pin1, HIGH);
      analogWrite(pin2, HIGH);
      analogWrite(pin3, HIGH);
      analogWrite(pin4, HIGH);
      analogWrite(pin5, HIGH);
      analogWrite(pin6, HIGH);
      analogWrite(pin7, HIGH);
      analogWrite(pin8, LOW);
      analogWrite(pin9, LOW);
      analogWrite(pin10, LOW);
    }

    if(potR >= pot80 && potR < pot90) {
      analogWrite(pin1, HIGH);
      analogWrite(pin2, HIGH);
      analogWrite(pin3, HIGH);
      analogWrite(pin4, HIGH);
      analogWrite(pin5, HIGH);
      analogWrite(pin6, HIGH);
      analogWrite(pin7, HIGH);
      analogWrite(pin8, HIGH);
      analogWrite(pin9, LOW);
      analogWrite(pin10, LOW);
    }

    if(potR >= pot90 && potR < pot100) {
      analogWrite(pin1, HIGH);
      analogWrite(pin2, HIGH);
      analogWrite(pin3, HIGH);
      analogWrite(pin4, HIGH);
      analogWrite(pin5, HIGH);
      analogWrite(pin6, HIGH);
      analogWrite(pin7, HIGH);
      analogWrite(pin8, HIGH);
      analogWrite(pin9, HIGH);
      analogWrite(pin10, LOW);
    }

    if(potR == pot100) {
      analogWrite(pin1, HIGH);
      analogWrite(pin2, HIGH);
      analogWrite(pin3, HIGH);
      analogWrite(pin4, HIGH);
      analogWrite(pin5, HIGH);
      analogWrite(pin6, HIGH);
      analogWrite(pin7, HIGH);
      analogWrite(pin8, HIGH);
      analogWrite(pin9, HIGH);
      analogWrite(pin10, HIGH);
    }
  

}

void maiorForG(void) {
  // Serial.printf("\n Potenciometro G: %i", potG);
  
  if(potG < pot10) {
      analogWrite(pin1, LOW);
      analogWrite(pin2, LOW);
      analogWrite(pin3, LOW);
      analogWrite(pin4, LOW);
      analogWrite(pin5, LOW);
      analogWrite(pin6, LOW);
      analogWrite(pin7, LOW);
      analogWrite(pin8, LOW);
      analogWrite(pin9, LOW);
      analogWrite(pin10, LOW);
    }

    if(potG >= pot10 && potG < pot20) {
      analogWrite(pin1, HIGH);
      analogWrite(pin2, LOW);
      analogWrite(pin3, LOW);
      analogWrite(pin4, LOW);
      analogWrite(pin5, LOW);
      analogWrite(pin6, LOW);
      analogWrite(pin7, LOW);
      analogWrite(pin8, LOW);
      analogWrite(pin9, LOW);
      analogWrite(pin10, LOW);
    }

    if(potG >= pot20 && potG < pot30) {
      analogWrite(pin1, HIGH);
      analogWrite(pin2, HIGH);
      analogWrite(pin3, LOW);
      analogWrite(pin4, LOW);
      analogWrite(pin5, LOW);
      analogWrite(pin6, LOW);
      analogWrite(pin7, LOW);
      analogWrite(pin8, LOW);
      analogWrite(pin9, LOW);
      analogWrite(pin10, LOW);
    
    }

    if(potG >= pot30 && potG < pot40) {
      analogWrite(pin1, HIGH);
      analogWrite(pin2, HIGH);
      analogWrite(pin3, HIGH);
      analogWrite(pin4, LOW);
      analogWrite(pin5, LOW);
      analogWrite(pin6, LOW);
      analogWrite(pin7, LOW);
      analogWrite(pin8, LOW);
      analogWrite(pin9, LOW);
      analogWrite(pin10, LOW);
    }

    if(potG >= pot40 && potG < pot50) {
      analogWrite(pin1, HIGH);
      analogWrite(pin2, HIGH);
      analogWrite(pin3, HIGH);
      analogWrite(pin4, HIGH);
      analogWrite(pin5, LOW);
      analogWrite(pin6, LOW);
      analogWrite(pin7, LOW);
      analogWrite(pin8, LOW);
      analogWrite(pin9, LOW);
      analogWrite(pin10, LOW);
    }

    if(potG >= pot50 && potG < pot60) {
      analogWrite(pin1, HIGH);
      analogWrite(pin2, HIGH);
      analogWrite(pin3, HIGH);
      analogWrite(pin4, HIGH);
      analogWrite(pin5, HIGH);
      analogWrite(pin6, LOW);
      analogWrite(pin7, LOW);
      analogWrite(pin8, LOW);
      analogWrite(pin9, LOW);
      analogWrite(pin10, LOW);
    }

    if(potG >= pot60 && potG < pot70) {
      analogWrite(pin1, HIGH);
      analogWrite(pin2, HIGH);
      analogWrite(pin3, HIGH);
      analogWrite(pin4, HIGH);
      analogWrite(pin5, HIGH);
      analogWrite(pin6, HIGH);
      analogWrite(pin7, LOW);
      analogWrite(pin8, LOW);
      analogWrite(pin9, LOW);
      analogWrite(pin10, LOW);
    }

    if(potG >= pot70 && potG < pot80) {
      analogWrite(pin1, HIGH);
      analogWrite(pin1, HIGH);
      analogWrite(pin2, HIGH);
      analogWrite(pin3, HIGH);
      analogWrite(pin4, HIGH);
      analogWrite(pin5, HIGH);
      analogWrite(pin6, HIGH);
      analogWrite(pin7, HIGH);
      analogWrite(pin8, LOW);
      analogWrite(pin9, LOW);
      analogWrite(pin10, LOW);
    }

    if(potG >= pot80 && potG < pot90) {
      analogWrite(pin1, HIGH);
      analogWrite(pin2, HIGH);
      analogWrite(pin3, HIGH);
      analogWrite(pin4, HIGH);
      analogWrite(pin5, HIGH);
      analogWrite(pin6, HIGH);
      analogWrite(pin7, HIGH);
      analogWrite(pin8, HIGH);
      analogWrite(pin9, LOW);
      analogWrite(pin10, LOW);
    }

    if(potG >= pot90 && potG < pot100) {
      analogWrite(pin1, HIGH);
      analogWrite(pin2, HIGH);
      analogWrite(pin3, HIGH);
      analogWrite(pin4, HIGH);
      analogWrite(pin5, HIGH);
      analogWrite(pin6, HIGH);
      analogWrite(pin7, HIGH);
      analogWrite(pin8, HIGH);
      analogWrite(pin9, HIGH);
      analogWrite(pin10, LOW);
    }

    if(potG == pot100) {
      analogWrite(pin1, HIGH);
      analogWrite(pin2, HIGH);
      analogWrite(pin3, HIGH);
      analogWrite(pin4, HIGH);
      analogWrite(pin5, HIGH);
      analogWrite(pin6, HIGH);
      analogWrite(pin7, HIGH);
      analogWrite(pin8, HIGH);
      analogWrite(pin9, HIGH);
      analogWrite(pin10, HIGH);
    }
  

} 

void maiorForB(void) {
  // Serial.printf("\n Potenciometro B: %i", potB);

  if(potB < pot10) {
      analogWrite(pin1, LOW);
      analogWrite(pin2, LOW);
      analogWrite(pin3, LOW);
      analogWrite(pin4, LOW);
      analogWrite(pin5, LOW);
      analogWrite(pin6, LOW);
      analogWrite(pin7, LOW);
      analogWrite(pin8, LOW);
      analogWrite(pin9, LOW);
      analogWrite(pin10, LOW);
    }

    if(potB >= pot10 && potB < pot20) {
      analogWrite(pin1, HIGH);
      analogWrite(pin2, LOW);
      analogWrite(pin3, LOW);
      analogWrite(pin4, LOW);
      analogWrite(pin5, LOW);
      analogWrite(pin6, LOW);
      analogWrite(pin7, LOW);
      analogWrite(pin8, LOW);
      analogWrite(pin9, LOW);
      analogWrite(pin10, LOW);
    }

    if(potB >= pot20 && potB < pot30) {
      analogWrite(pin1, HIGH);
      analogWrite(pin2, HIGH);
      analogWrite(pin3, LOW);
      analogWrite(pin4, LOW);
      analogWrite(pin5, LOW);
      analogWrite(pin6, LOW);
      analogWrite(pin7, LOW);
      analogWrite(pin8, LOW);
      analogWrite(pin9, LOW);
      analogWrite(pin10, LOW);
    
    }

    if(potB >= pot30 && potB < pot40) {
      analogWrite(pin1, HIGH);
      analogWrite(pin2, HIGH);
      analogWrite(pin3, HIGH);
      analogWrite(pin4, LOW);
      analogWrite(pin5, LOW);
      analogWrite(pin6, LOW);
      analogWrite(pin7, LOW);
      analogWrite(pin8, LOW);
      analogWrite(pin9, LOW);
      analogWrite(pin10, LOW);
    }

    if(potB >= pot40 && potB < pot50) {
      analogWrite(pin1, HIGH);
      analogWrite(pin2, HIGH);
      analogWrite(pin3, HIGH);
      analogWrite(pin4, HIGH);
      analogWrite(pin5, LOW);
      analogWrite(pin6, LOW);
      analogWrite(pin7, LOW);
      analogWrite(pin8, LOW);
      analogWrite(pin9, LOW);
      analogWrite(pin10, LOW);
    }

    if(potB >= pot50 && potB < pot60) {
      analogWrite(pin1, HIGH);
      analogWrite(pin2, HIGH);
      analogWrite(pin3, HIGH);
      analogWrite(pin4, HIGH);
      analogWrite(pin5, HIGH);
      analogWrite(pin6, LOW);
      analogWrite(pin7, LOW);
      analogWrite(pin8, LOW);
      analogWrite(pin9, LOW);
      analogWrite(pin10, LOW);
    }

    if(potB >= pot60 && potB < pot70) {
      analogWrite(pin1, HIGH);
      analogWrite(pin2, HIGH);
      analogWrite(pin3, HIGH);
      analogWrite(pin4, HIGH);
      analogWrite(pin5, HIGH);
      analogWrite(pin6, HIGH);
      analogWrite(pin7, LOW);
      analogWrite(pin8, LOW);
      analogWrite(pin9, LOW);
      analogWrite(pin10, LOW);
    }

    if(potB >= pot70 && potB < pot80) {
      analogWrite(pin1, HIGH);
      analogWrite(pin1, HIGH);
      analogWrite(pin2, HIGH);
      analogWrite(pin3, HIGH);
      analogWrite(pin4, HIGH);
      analogWrite(pin5, HIGH);
      analogWrite(pin6, HIGH);
      analogWrite(pin7, HIGH);
      analogWrite(pin8, LOW);
      analogWrite(pin9, LOW);
      analogWrite(pin10, LOW);
    }

    if(potB >= pot80 && potB < pot90) {
      analogWrite(pin1, HIGH);
      analogWrite(pin2, HIGH);
      analogWrite(pin3, HIGH);
      analogWrite(pin4, HIGH);
      analogWrite(pin5, HIGH);
      analogWrite(pin6, HIGH);
      analogWrite(pin7, HIGH);
      analogWrite(pin8, HIGH);
      analogWrite(pin9, LOW);
      analogWrite(pin10, LOW);
    }

    if(potB >= pot90 && potB < pot100) {
      analogWrite(pin1, HIGH);
      analogWrite(pin2, HIGH);
      analogWrite(pin3, HIGH);
      analogWrite(pin4, HIGH);
      analogWrite(pin5, HIGH);
      analogWrite(pin6, HIGH);
      analogWrite(pin7, HIGH);
      analogWrite(pin8, HIGH);
      analogWrite(pin9, HIGH);
      analogWrite(pin10, LOW);
    }

    if(potB == pot100) {
      analogWrite(pin1, HIGH);
      analogWrite(pin2, HIGH);
      analogWrite(pin3, HIGH);
      analogWrite(pin4, HIGH);
      analogWrite(pin5, HIGH);
      analogWrite(pin6, HIGH);
      analogWrite(pin7, HIGH);
      analogWrite(pin8, HIGH);
      analogWrite(pin9, HIGH);
      analogWrite(pin10, HIGH);
    }
  
  
} 
 
 
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
  char messageBuffer[30];
 
  memcpy(messageBuffer, payload, length);
 
  messageBuffer[length] = '\0';

  if(String(topic) == "Luan/LedPotR") {
    potR = strtol(messageBuffer, NULL, 10);
  }
  if(String(topic) == "Luan/LedPotG") {
    potG = strtol(messageBuffer, NULL, 10);
  }
  if(String(topic) == "Luan/LedPotB") {
    potB = strtol(messageBuffer, NULL, 10);
  }

  if(potR > potG && potR > potB) {
    return maiorForR();
  }

  if(potG > potR && potG > potB) {
    return maiorForG();
  }

  if(potB > potR && potB > potG) {
    return maiorForB();
  }
}
 
 
void reconnectMQTT(void)
{
  while (!MQTT.connected()) {
    Serial.print("\n* Tentando se conectar ao Broker MQTT: ");
    Serial.println(BROKER_MQTT);
    if (MQTT.connect(ID_MQTT)) {
      Serial.println("Conectado com sucesso ao broker MQTT!");
      MQTT.subscribe(TOPIC_1);
      MQTT.subscribe(TOPIC_2);
      MQTT.subscribe(TOPIC_3);
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
  initWiFi();
 
  initMQTT();
}
void loop() {
 
  checkWiFIAndMQTT();
 
  MQTT.loop();
 
  delay(1500);
 
}
