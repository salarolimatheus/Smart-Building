#include "ComunicacaoMQTT.hpp"

#include "../../chaves/Mqtt-keys.h"
#include "../../interface/topicos-mqtt.h"

WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);

static bool touch0Enabled = true;
static bool touch2Enabled = true;

void ConfiguraMQTT() {
    mqttClient.setServer(MQTT_SERVER, MQTT_PORT);
    mqttClient.setCallback(callback);

    conectarAoBrokerMQTT();
}

void processarMensagensRecebidasDoMQTT(TouchConfig* config) {
    if (!mqttClient.loop()) {
        conectarAoBrokerMQTT();
        mqttClient.loop();
    }

    config->touch0Enabled = touch0Enabled;
    config->touch2Enabled = touch2Enabled;
}

void conectarAoBrokerMQTT() {
    while (!mqttClient.connected()) {
        DBG_PRINT("[MQTT] Tentativa de conexao - ")
        if (mqttClient.connect(MQTT_CLIENT)) {
            DBG_PRINTLN("[MQTT] contectado")
            // Subscribe
            subscricaoAosTopicosMQTT();
        } else {
            DBG_PRINT(" falhou, rc=")
            DBG_PRINT(mqttClient.state())
            DBG_PRINTLN("tentando em 5 seg")
            delay(500);
        }
    }
}

void subscricaoAosTopicosMQTT() {
    DBG_PRINTLN("[MQTT] subscricoes: ")
    mqttClient.subscribe(TOPICO_ENABLE_TOUCH0);
    DBG_PRINTLN("[MQTT] topico: interruptor/touch0_enable")
    mqttClient.subscribe(TOPICO_ENABLE_TOUCH2);
    DBG_PRINTLN("[MQTT] topico: interruptor/touch2_enable")
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

    String topico = String(topic);

    if (topico == TOPICO_ENABLE_TOUCH0) {
        if(messageTemp == "0") {
            DBG_PRINTLN("[MQTT] touch0 desligado")
            touch0Enabled = false;
        } else {
            DBG_PRINTLN("[MQTT] touch0 ligado")
            touch0Enabled = true;
        }
    } else if (topico == TOPICO_ENABLE_TOUCH2) {
        if(messageTemp == "0") {
            DBG_PRINTLN("[MQTT] touch2 desligado")
            touch2Enabled = false;
        } else {
            DBG_PRINTLN("[MQTT] touch2 ligado")
            touch2Enabled = true;
        }
    }
}


void EnviaDadosTouch0PorMQTT(TouchStatus* touch) {
    char payload[sizeof(TouchStatus)];
    memcpy(payload, touch, sizeof(TouchStatus));
    mqttClient.publish(TOPICO_TOUCH0, (byte*)payload, sizeof(TouchStatus));
    if (touch->clique == CLIQUE_SIMPLES) {
    mqttClient.publish("tomada/rele1_restatus", "on");
  }
  else if (touch->clique == CLIQUE_LONGO){
    mqttClient.publish("tomada/rele1_restatus", "off");
  }
    touch->clique = SEM_CLIQUE;
}

void EnviaDadosTouch2PorMQTT(TouchStatus* touch) {
    char payload[sizeof(TouchStatus)];
    memcpy(payload, touch, sizeof(TouchStatus));
    mqttClient.publish(TOPICO_TOUCH2, (byte*)payload, sizeof(TouchStatus));
    if (touch->clique == CLIQUE_SIMPLES) {
    mqttClient.publish("tomada/rele2_restatus", "on");
  }
  else if (touch->clique == CLIQUE_LONGO){
    mqttClient.publish("tomada/rele2_restatus", "off");
  }
    touch->clique = SEM_CLIQUE;
}
