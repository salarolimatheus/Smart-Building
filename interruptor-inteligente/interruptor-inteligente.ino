#include "src/Wifi/Wifi.h"
#include "PubSubClient.h"

// TROCAR ESSAS LINHAS AQUI ---------
const char* ssid = "Hakuna Matata";
const char* password = "qwerty1234";
// Add your MQTT Broker IP address:
const char* mqtt_server = "192.168.201.96";
const int mqtt_port = 1883;
----------------

#define pinLed 2

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;

void setup() {
    pinMode(pinLed, OUTPUT);
    Serial.begin(115200);
    setup_wifi();
    client.setServer(mqtt_server, mqtt_port);
    client.setCallback(callback);
}

void setup_wifi() {
    delay(10);
    // We start by connecting to a WiFi network
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);

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

void callback(char* topic, byte* message, unsigned int length) {
    Serial.print("Message arrived on topic: ");
    Serial.print(topic);
    Serial.print(". Message: ");
    String messageTemp;

    for (int i = 0; i < length; i++) {
        Serial.print((char)message[i]);
        messageTemp += (char)message[i];
    }
    Serial.println();

    // Feel free to add more if statements to control more GPIOs with MQTT

    // If a message is received on the topic esp32/output, you check if the message is either "on" or "off".
    // Changes the output state according to the message
    if (String(topic) == "tomada-inteligente/switch") {
        if(messageTemp == "ligado") {
            Serial.println("ligado");
            client.publish("tomada/sub", "ligado");
            digitalWrite(pinLed, HIGH);
        } else {
            Serial.println("desligado");
            client.publish("tomada/sub", "desligado");
            digitalWrite(pinLed, LOW);
        }
    } else if (String(topic) == "tomada/timer") {
        Serial.println("ligado");
        digitalWrite(pinLed, HIGH);
        client.publish("tomada/sub", "ligado");
        delay(5000);
        Serial.println("desligado");
        digitalWrite(pinLed, LOW);
        client.publish("tomada/sub", "desligado");
    }
}


void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("ESP8266Client")) {
      Serial.println("connected");
      // Subscribe
      client.subscribe("tomada-inteligente/switch");
      client.subscribe("tomada/timer");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void loop() {
    if (!client.connected()) {
        reconnect();
    }
    client.loop();

    if (millis() - lastMsg > 5000) {
        lastMsg = millis();
        client.publish("esp32/temperature", "25");
        client.publish("esp32/humidity", "88");
    }
}
