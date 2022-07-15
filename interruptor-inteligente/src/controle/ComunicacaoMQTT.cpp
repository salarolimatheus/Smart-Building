#include "ComunicacaoMQTT.hpp"

#include "../../chaves/Mqtt-keys.h"
#include "../../interface/topicos-mqtt.h"

WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);

void ConfiguraMQTT() {
    mqttClient.setServer(MQTT_SERVER, MQTT_PORT);
    mqttClient.setCallback(callback);

    conectarAoBrokerMQTT();
}

void processarMensagensRecebidasDoMQTT() {
    if (!mqttClient.loop()) {
        conectarAoBrokerMQTT();
        mqttClient.loop();
    }
}

void conectarAoBrokerMQTT() {
    while (!mqttClient.connected()) {
        DBG_PRINT("[MQTT] Tentativa de conexao - ")
        if (mqttClient.connect(MQTT_CLIENT)) {
            DBG_PRINTLN("[MQTT] contectado")
            // Subscribe
            DBG_PRINTLN("[MQTT] subscricoes: ")
            mqttClient.subscribe("interruptor/touch0_enable");
            DBG_PRINTLN("interruptor/touch0_enable")
            mqttClient.subscribe("interruptor/touch2_enable");
            DBG_PRINTLN("interruptor/touch2_enable")
        } else {
            DBG_PRINT(" falhou, rc=")
            DBG_PRINT(mqttClient.state())
            DBG_PRINTLN("tentando em 5 seg")
            delay(500);
        }
    }
}

void callback(char* topic, byte* message, unsigned int length) {
    DBG_PRINT("[MQTT] Mensagem vinda no topico: ")
    DBG_PRINT(topic)
    DBG_PRINT(". payload: ")
    String messageTemp;

    for (int i = 0; i < length; i++) {
        DBG_PRINT((char)message[i])
        messageTemp += (char)message[i];
    }
    DBG_PRINTLN()

    if (String(topic) == "interruptor/touch0_enable") {
        if(messageTemp == "0") {
            DBG_PRINTLN("[MQTT] touch0 desligado")
            // touch0Enabled = false;
        } else {
            DBG_PRINTLN("[MQTT] touch0 ligado")
            // touch0Enabled = true;
        }
    } else if (String(topic) == "interruptor/touch2_enable") {
        if(messageTemp == "0") {
            DBG_PRINTLN("[MQTT] touch2 desligado")
            // touch2Enabled = false;
        } else {
            DBG_PRINTLN("[MQTT] touch2 ligado")
            // touch2Enabled = true;
        }
    }
}


void EnviaDadosTouch0PorMQTT(TouchStatus* touch) {
    char payload[sizeof(TouchStatus)];
    memcpy(payload, touch, sizeof(TouchStatus));
    mqttClient.publish(TOPICO_TOUCH0, (byte*)payload, sizeof(TouchStatus));
    touch->clique = SEM_CLIQUE;
}

void EnviaDadosTouch2PorMQTT(TouchStatus* touch) {
    char payload[sizeof(TouchStatus)];
    memcpy(payload, touch, sizeof(TouchStatus));
    mqttClient.publish(TOPICO_TOUCH2, (byte*)payload, sizeof(TouchStatus));
    touch->clique = SEM_CLIQUE;
}
