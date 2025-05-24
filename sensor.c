// Projeto: Módulo Diagnóstico de Manutenção - Mottu



#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>


const char *SSID = "Wokwi-GUEST";
const char *PASSWORD = "";


const char *BROKER_MQTT = "broker.hivemq.com";
const int BROKER_PORT = 1883;
const char *TOPIC_PUBLISH_TEMP = "fiap/iot/temperatura";


const int PIN_TEMP = 34;  
const int PIN_LED = 2;    
const int TAMANHO = 100;

WiFiClient espClient;
PubSubClient MQTT(espClient);


void initWiFi() {
  Serial.print("Conectando a rede: ");
  Serial.println(SSID);
  WiFi.begin(SSID, PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWi-Fi conectado com sucesso!");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
}


void initMQTT() {
  MQTT.setServer(BROKER_MQTT, BROKER_PORT);
}


void reconnectWiFi() {
  if (WiFi.status() != WL_CONNECTED) {
    WiFi.begin(SSID, PASSWORD);
    while (WiFi.status() != WL_CONNECTED) {
      delay(100);
    }
  }
}


void reconnectMQTT() {
  while (!MQTT.connected()) {
    if (MQTT.connect("esp32_temp_client")) {
      Serial.println("MQTT conectado!");
    } else {
      Serial.print(".");
      delay(1000);
    }
  }
}


float lerTemperatura() {
  int leitura = analogRead(PIN_TEMP);
  float tensao = leitura * 3.3 / 4095.0; 
  float temperatura = tensao * 100.0;    
  return temperatura;
}

void setup() {
  Serial.begin(115200);
  pinMode(PIN_LED, OUTPUT);  
  digitalWrite(PIN_LED, LOW); 
  initWiFi();
  initMQTT();
}

void loop() {
  reconnectWiFi();
  reconnectMQTT();
  MQTT.loop();

  float temperatura = lerTemperatura();

  Serial.print("Temperatura: ");
  Serial.print(temperatura);
  Serial.print(" °C - ");

  if (temperatura >= 90.0 && temperatura <= 100.0) {
    Serial.println("Temperatura normal ✅");
    digitalWrite(PIN_LED, LOW); 
  } else if (temperatura > 105.0) {
    Serial.println("⚠️ ALERTA: Temperatura alta!");
    digitalWrite(PIN_LED, HIGH); 
  } else {
    Serial.println("Temperatura fora da faixa ideal.");
    digitalWrite(PIN_LED, LOW); 
  }

  StaticJsonDocument<TAMANHO> doc;
  doc["temperatura"] = temperatura;

  char mensagem[TAMANHO];
  serializeJson(doc, mensagem);
  MQTT.publish(TOPIC_PUBLISH_TEMP, mensagem);

  delay(2000); 
}
