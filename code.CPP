#include <WiFi.h> 
#include <PubSubClient.h>
#include <DHTesp.h>


const int DHT_PIN = 15; 
const int LDR_PIN = 35; 
const int RELAY_PIN = 27; 
const int BUZZER_PIN = 4; 

DHTesp dht;

const char* ssid = "Wokwi-GUEST";
const char* password = "";
const char* mqtt_server = "test.mosquitto.org";

WiFiClient espClient;
PubSubClient client(espClient);

unsigned long lastMsg = 0;

float temp = 0;
float hum = 0;
int lightValue = 0;

void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    String clientId = "ESP32Client-";
    clientId += String(random(0xffff), HEX);
    if (client.connect(clientId.c_str())) {
      Serial.println("Connected");
      client.publish("/ThinkIOT/Publish", "Welcome");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);


  dht.setup(DHT_PIN, DHTesp::DHT22);
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);


  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  unsigned long now = millis();
  if (now - lastMsg > 2000) { 
    lastMsg = now;

    TempAndHumidity data = dht.getTempAndHumidity();
    temp = data.temperature;
    hum = data.humidity;
    lightValue = analogRead(LDR_PIN);

    String tempStr = String(temp, 2);
    client.publish("/ThinkIOT/temp", tempStr.c_str());
    String humStr = String(hum, 1);
    client.publish("/ThinkIOT/hum", humStr.c_str());
    String lightStr = String(lightValue);
    client.publish("/ThinkIOT/light", lightStr.c_str());

    Serial.println("=== Dados Atualizados ===");
    Serial.print("Temperatura: ");
    Serial.println(temp);
    Serial.print("Umidade: ");
    Serial.println(hum);
    Serial.print("Luz: ");
    Serial.println(lightValue);

  
    if (temp > 30) {
      digitalWrite(RELAY_PIN, HIGH); 
      Serial.println("Relé ligado (alta temperatura).");
    } else {
      digitalWrite(RELAY_PIN, LOW); 
      Serial.println("Relé desligado.");
    }

    if (hum < 40) {
      tone(BUZZER_PIN, 1000); 
      Serial.println("Buzzer ligado (baixa umidade).");
    } else {
      noTone(BUZZER_PIN); 
      Serial.println("Buzzer desligado.");
    }
  }
}
