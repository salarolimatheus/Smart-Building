#include "ControleTomada.hpp"

#include "../../interface/portas-saida-tomada.h"

void ConfiguraGPIOs() {
    pinMode(PIN_TOMADA_0, OUTPUT);
    pinMode(PIN_TOMADA_1, OUTPUT);
}

bool ControleDaTomada0(TomadaConfig* tomada, TipoComando* comando) {
    if (*comando == COMANDO_LIGAR) {
        digitalWrite(PIN_TOMADA_0, HIGH);
        tomada-> tomadaLigada = true;
        DBG_PRINTLN("[CT] tomada0 Ligada")
    } else if (*comando == COMANDO_DESLIGAR) {
        digitalWrite(PIN_TOMADA_0, LOW);
        tomada-> tomadaLigada = false;
        DBG_PRINTLN("[CT] tomada0 Desligada")
    } if (*comando == COMANDO_INVERTER) {
        bool status = !digitalRead(PIN_TOMADA_0);
        tomada-> tomadaLigada = status;
        digitalWrite(PIN_TOMADA_0, status);
        DBG_PRINTLN("[CT] tomada0 Toggle")
    } else {
        *comando = SEM_COMANDO;
        return false;
    }
    *comando = SEM_COMANDO;
    return true;
}
bool ControleDaTomada1(TomadaConfig* tomada, TipoComando* comando) {
    if (*comando == COMANDO_LIGAR) {
        digitalWrite(PIN_TOMADA_1, HIGH);
        tomada-> tomadaLigada = true;
        DBG_PRINTLN("[CT] tomada1 Ligada")
    } else if (*comando == COMANDO_DESLIGAR) {
        digitalWrite(PIN_TOMADA_1, LOW);
        tomada-> tomadaLigada = false;
        DBG_PRINTLN("[CT] tomada1 Desligada")
    } if (*comando == COMANDO_INVERTER) {
        bool status = !digitalRead(PIN_TOMADA_1);
        tomada-> tomadaLigada = status;
        digitalWrite(PIN_TOMADA_1, status);
        DBG_PRINTLN("[CT] tomada1 Toggle")
    } else {
        *comando = SEM_COMANDO;
        return false;
    }
    *comando = SEM_COMANDO;
    return true;
}
