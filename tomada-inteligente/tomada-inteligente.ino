#include "src/Wifi/Wifi.h"
#include "PubSubClient.h"

// TROCAR ESSAS LINHAS AQUI ---------
const char* ssid = "TUG";
const char* password = "7500015000";
// Add your MQTT Broker IP address:
const char* mqtt_server = "sb-docker.duckdns.org";
const int mqtt_port = 49000;
// ----------------

#define pinRele1 12
#define pinRele2 14

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;

volatile long tempoRele1 = 0;
volatile long tempoRele2 = 0;
volatile boolean tempoRele1Enabled = 0;
volatile boolean tempoRele2Enabled = 0;

//Initial config
void setup() {
    pinMode(pinRele1, OUTPUT);
    pinMode(pinRele2, OUTPUT);
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

    String topico = String(topic);
    // Feel free to add more if statements to control more GPIOs with MQTT
    if (topico == "tomada/rele1_status") {
        if(messageTemp == "on") {
            Serial.println("ligado");
            digitalWrite(pinRele1, HIGH);
        } else {
            Serial.println("desligado");
            digitalWrite(pinRele1, LOW);
        }
        tempoRele1Enabled = false;
    } else if (topico == "tomada/rele2_status") {
        if(messageTemp == "on") {
            Serial.println("ligado");
            digitalWrite(pinRele2, HIGH);
        } else {
            Serial.println("desligado");
            digitalWrite(pinRele2, LOW);
        }
        tempoRele2Enabled = false;
      } else if (topico == "tomada/rele1_toggle") {
              if(digitalRead(pinRele1) == HIGH){
                client.publish("tomada/rele1_restatus", "off");
                digitalWrite(pinRele1, LOW);
              }
              else{
                client.publish("tomada/rele1_restatus", "on");
                digitalWrite(pinRele1, HIGH);
              }
          tempoRele1Enabled = false;
    } else if (topico == "tomada/rele1_timer") {
        // "on,5000" => comando = on; tempo = 5000;
        String comando = messageTemp.substring(0, messageTemp.indexOf(','));
        tempoRele1 = millis() + messageTemp.substring(messageTemp.indexOf(',') + 1, messageTemp.length()).toInt();
        tempoRele1Enabled = true;

        if (comando == "ligado") {
            digitalWrite(pinRele1, HIGH);
            client.publish("tomada/rele1_restatus", "on");
        } else {
            digitalWrite(pinRele1, LOW);
            client.publish("tomada/rele1_restatus", "off");
        }
    } else if (topico == "tomada/rele2_timer") {
        String comando = messageTemp.substring(0, messageTemp.indexOf(','));
        tempoRele2 = millis() + messageTemp.substring(messageTemp.indexOf(',') + 1, messageTemp.length()).toInt();
        tempoRele2Enabled = true;

        if (comando == "ligado") {
            digitalWrite(pinRele2, HIGH);
            client.publish("tomada/rele2_restatus", "on");
        } else {
            digitalWrite(pinRele2, LOW);
            client.publish("tomada/rele2_restatus", "off");

        }
    }
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("ESP32_Tomada")) {
      Serial.println("connected");
      // Subscribe
      client.subscribe("tomada/rele1_status");
      client.subscribe("tomada/rele2_status");
      client.subscribe("tomada/rele1_timer");
      client.subscribe("tomada/rele2_timer");
      client.subscribe("tomada/rele1_toggle");
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

    if (tempoRele1Enabled) {
        if (millis() >= tempoRele1) {
            digitalWrite(pinRele1, !digitalRead(pinRele1));
            if(digitalRead(pinRele1) == LOW) {
                client.publish("tomada/rele1_restatus", "off");
            } else {
                client.publish("tomada/rele1_restatus", "on");
            }
            tempoRele1Enabled = false;
        }
    }

    if (tempoRele2Enabled) {
        if (millis() >= tempoRele2) {
            digitalWrite(pinRele2, !digitalRead(pinRele2));
            if(digitalRead(pinRele2) == LOW) {
                client.publish("tomada/rele2_restatus", "off");
            } else {
                client.publish("tomada/rele2_restatus", "on");
            }
            tempoRele2Enabled = false;
        }
    }

}
