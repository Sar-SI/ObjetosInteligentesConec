#include <WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>

// ————— Configurações Wi-Fi —————
const char* SSIDName    = "Wokwi-GUEST";
const char* SSIDPass    = "";

// ————— Pinos dos sensores —————
#define DHTPIN1        15
#define DHTPIN2        4
#define DHTTYPE        DHT22

DHT dht1(DHTPIN1, DHTTYPE);
DHT dht2(DHTPIN2, DHTTYPE);

// ————— Configurações MQTT —————
const char* BrokerURL      = "broker.hivemq.com";
const int   BrokerPort     = 1883;
const char* MQTTClientName = "mqtt-TrabalhoObjetos";
WiFiClient    wifiClient;
PubSubClient  clienteMQTT(wifiClient);

// ————— Tópicos MQTT —————
const char* Topico1_Temp   = "TrabalhoObjetos/Sensor1/Temperatura";
const char* Topico1_Umi    = "TrabalhoObjetos/Sensor1/Umidade";
const char* Topico2_Temp   = "TrabalhoObjetos/Sensor2/Temperatura";
const char* Topico2_Umi    = "TrabalhoObjetos/Sensor2/Umidade";

void reconnectMQTT() {
  while (!clienteMQTT.connected()) {
    Serial.print("[MQTT] Conectando… ");
    if (clienteMQTT.connect(MQTTClientName)) {
      Serial.println("OK");
    } else {
      Serial.print("falha rc=");
      Serial.print(clienteMQTT.state());
      Serial.println(", retry em 5s");
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  // inicia DHTs
  dht1.begin();
  dht2.begin();

  // conecta Wi-Fi
  WiFi.begin(SSIDName, SSIDPass);
  Serial.print("[WiFi] Conectando");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\n[WiFi] OK! IP: " + WiFi.localIP().toString());

  // configura MQTT
  clienteMQTT.setServer(BrokerURL, BrokerPort);
}

void loop() {
  if (!clienteMQTT.connected()) reconnectMQTT();
  clienteMQTT.loop();

  // sensor 1
  float t1 = dht1.readTemperature();
  float h1 = dht1.readHumidity();
  if (!isnan(t1) && !isnan(h1)) {
    char buf[16];
    dtostrf(t1, 4, 2, buf);
    clienteMQTT.publish(Topico1_Temp, buf);
    Serial.printf("[S1] Temp: %s °C → %s\n", buf, Topico1_Temp);

    dtostrf(h1, 4, 2, buf);
    clienteMQTT.publish(Topico1_Umi, buf);
    Serial.printf("[S1] Umi: %s %% → %s\n", buf, Topico1_Umi);
  } else {
    Serial.println("[S1] Erro na leitura");
  }

  // sensor 2
  float t2 = dht2.readTemperature();
  float h2 = dht2.readHumidity();
  if (!isnan(t2) && !isnan(h2)) {
    char buf[16];
    dtostrf(t2, 4, 2, buf);
    clienteMQTT.publish(Topico2_Temp, buf);
    Serial.printf("[S2] Temp: %s °C → %s\n", buf, Topico2_Temp);

    dtostrf(h2, 4, 2, buf);
    clienteMQTT.publish(Topico2_Umi, buf);
    Serial.printf("[S2] Umi: %s %% → %s\n", buf, Topico2_Umi);
  } else {
    Serial.println("[S2] Erro na leitura");
  }

  Serial.println("--- aguardando 15s ---\n");
  delay(15000);
}
