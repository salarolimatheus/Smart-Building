#pragma once
#include "Arduino.h"
#include "../Pacotes.hpp"
#include "../Debug.hpp"

#include "../hardware/PubSubClient/PubSubClient.h"
#include "../hardware/Wifi/WifiClient.h"

void ConfiguraMQTT();

void processarMensagensRecebidasDoMQTT(TouchConfig* config);

void conectarAoBrokerMQTT();
void callback(char* topic, byte* message, unsigned int length);

void EnviaDadosTouch0PorMQTT(TouchStatus* touch);
void EnviaDadosTouch2PorMQTT(TouchStatus* touch);
