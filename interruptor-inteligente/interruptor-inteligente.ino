#include "src/Wifi/Wifi.h"
#include "PubSubClient.h"

// TROCAR ESSAS LINHAS AQUI ---------
const char* ssid = "Hakuna Matata";
const char* password = "qwerty1234";
// Add your MQTT Broker IP address:
const char* mqtt_server = "192.168.194.96";
const int mqtt_port = 1883;
// ----------------
WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;

enum Estado {
    ON,
    RELEASE,
    OFF,
    PUSH
};

#define TEMPO_PERIODO_TOUCH 40
#define tempoMinimo     100
#define tempoTouchLongo 400
const int threshold = 30;

volatile boolean touch0Enabled = true;
volatile boolean touch2Enabled = true;

void setup() {
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
void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("ESP8266Client")) {
      Serial.println("connected");
      // Subscribe
      client.subscribe("interruptor/touch0_enable");
      client.subscribe("interruptor/touch2_enable");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
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

    if (String(topic) == "interruptor/touch0_enable") {
        if(messageTemp == "0") {
            Serial.println("touch0 desligado");
            touch0Enabled = false;
        } else {
            Serial.println("touch0 ligado");
            touch0Enabled = true;
        }
    } else if (String(topic) == "interruptor/touch2_enable") {
        if(messageTemp == "0") {
            Serial.println("touch2 desligado");
            touch2Enabled = false;
        } else {
            Serial.println("touch2 ligado");
            touch2Enabled = true;
        }
    }
}

void loop() {
    static Estado estadoTouch0 = OFF;
    static Estado estadoTouch2 = OFF;

    static long periodoTarefaTouch0 = millis() + TEMPO_PERIODO_TOUCH;
    static long periodoTarefaTouch2 = millis() + TEMPO_PERIODO_TOUCH;

    static long tempoApertoTouch0 = 0;
    static long lastTempoApertoTouch0 = 0;

    static long tempoApertoTouch2 = 0;
    static long lastTempoApertoTouch2 = 0;

    if (!client.connected()) {
        reconnect();
    }
    client.loop();

    if ((millis() >= periodoTarefaTouch0) && touch0Enabled) {
        uint32_t valorTouch0 = 0;
        for (uint8_t i = 0; i < 4; i++) {
            valorTouch0 = valorTouch0 + touchRead(T0);
            delay(4);
        }
        valorTouch0 = (valorTouch0>>2);

        switch (estadoTouch0) {
            case OFF:
                if(valorTouch0 < threshold) {
                    estadoTouch0 = PUSH;
                    client.publish("interruptor/touch0_status", "push");
                }
            break;
            case PUSH:
                estadoTouch0 = ON;
                tempoApertoTouch0 = millis();
                client.publish("interruptor/touch0_status", "on");
            break;
            case ON:
                if(valorTouch0 >= threshold) {
                    estadoTouch0 = RELEASE;
                    client.publish("interruptor/touch0_status", "release");
                }
            break;
            case RELEASE:
                estadoTouch0 = OFF;
                lastTempoApertoTouch0 = millis() - tempoApertoTouch0;
                client.publish("interruptor/touch0_status", "off");
            break;
        }
        periodoTarefaTouch0 = millis() + TEMPO_PERIODO_TOUCH;
    }
    if ((millis() >= periodoTarefaTouch2) && touch2Enabled) {
        uint32_t valorTouch2 = 0;
        for (uint8_t i = 0; i < 4; i++) {
            valorTouch2 = valorTouch2 + touchRead(T2);
            delay(4);
        }
        valorTouch2 = (valorTouch2>>2);

        switch (estadoTouch2) {
            case OFF:
                if(valorTouch2 < threshold) {
                    estadoTouch2 = PUSH;
                    client.publish("interruptor/touch2_status", "push");
                }
            break;
            case PUSH:
                estadoTouch2 = ON;
                tempoApertoTouch2 = millis();
                client.publish("interruptor/touch2_status", "on");
            break;
            case ON:
                if(valorTouch2 >= threshold) {
                    estadoTouch2 = RELEASE;
                    client.publish("interruptor/touch2_status", "release");
                }
            break;
            case RELEASE:
                estadoTouch2 = OFF;
                lastTempoApertoTouch2 = millis() - tempoApertoTouch2;
                client.publish("interruptor/touch2_status", "off");
            break;
        }
        periodoTarefaTouch2 = millis() + TEMPO_PERIODO_TOUCH;
    }

    if (lastTempoApertoTouch0 > tempoMinimo) {
        if (lastTempoApertoTouch0 > tempoTouchLongo) {
            client.publish("interruptor/touch0_click", "longo");
            client.publish("tomada/rele1_status", "off");
            client.publish("tomada/rele1_restatus", "off");
        }
        else {
            client.publish("interruptor/touch0_click", "curto");
            client.publish("tomada/rele1_status", "on");
            client.publish("tomada/rele1_restatus", "on");
        }
        lastTempoApertoTouch0 = 0;
    }
    if (lastTempoApertoTouch2 > tempoMinimo) {
        if (lastTempoApertoTouch2 > tempoTouchLongo) {
            client.publish("interruptor/touch2_click", "longo");
            client.publish("tomada/rele2_status", "off");
            client.publish("tomada/rele2_restatus", "off");
        }
        else {
            client.publish("interruptor/touch2_click", "curto");
            client.publish("tomada/rele2_status", "on");
            client.publish("tomada/rele2_restatus", "on");
        }
        lastTempoApertoTouch2 = 0;
    }
}
