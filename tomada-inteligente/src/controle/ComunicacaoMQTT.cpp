#include "ComunicacaoMQTT.hpp"

#include "../../chaves/Mqtt-keys.h"
#include "../../interface/topicos-mqtt.h"

WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);

volatile ComandoTomadas comandosRecebidos;
volatile bool novoDado;

void ConfiguraMQTT() {
    mqttClient.setServer(MQTT_SERVER, MQTT_PORT);
    mqttClient.setCallback(callback);

    conectarAoBrokerMQTT();
}

void processarMensagensRecebidasDoMQTT(ComandoTomadas* comandoTomadas) {
    if (!mqttClient.loop()) {
        conectarAoBrokerMQTT();
        mqttClient.loop();
    }

    if(novoDado == true) {
        comandoTomadas->tomada0 = comandosRecebidos.tomada0;
        comandoTomadas->tomada1 = comandosRecebidos.tomada1;
        comandosRecebidos.tomada0 = SEM_COMANDO;
        comandosRecebidos.tomada1 = SEM_COMANDO;
        novoDado = false;
    }
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
    DBG_PRINTLN("[MQTT] topico: comando/tomada0")
    mqttClient.subscribe(TOPICO_COMANDO_TOMADA0);
    DBG_PRINTLN("[MQTT] topico: comando/tomada1")
    mqttClient.subscribe(TOPICO_COMANDO_TOMADA1);
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

    if (topico == TOPICO_COMANDO_TOMADA0) {
        novoDado = true;
        if(messageTemp == "2") {
            comandosRecebidos.tomada0 = COMANDO_INVERTER;
            DBG_PRINTLN("[MQTT] tomada0: COMANDO_INVERTER")
        } else if(messageTemp == "1") {
            comandosRecebidos.tomada0 = COMANDO_LIGAR;
            DBG_PRINTLN("[MQTT] tomada0: COMANDO_LIGAR")
        } else {
            comandosRecebidos.tomada0 = COMANDO_DESLIGAR;
            DBG_PRINTLN("[MQTT] tomada0: COMANDO_DESLIGAR")
        }
    } else if (topico == TOPICO_COMANDO_TOMADA1) {
        novoDado = true;
        if(messageTemp == "2") {
            comandosRecebidos.tomada1 = COMANDO_INVERTER;
            DBG_PRINTLN("[MQTT] tomada1: COMANDO_INVERTER")
        } else if(messageTemp == "1") {
            comandosRecebidos.tomada1 = COMANDO_LIGAR;
            DBG_PRINTLN("[MQTT] tomada1: COMANDO_LIGAR")
        } else {
            comandosRecebidos.tomada1 = COMANDO_DESLIGAR;
            DBG_PRINTLN("[MQTT] tomada1: COMANDO_DESLIGAR")
        }
    }
}
