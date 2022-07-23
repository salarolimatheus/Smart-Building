#pragma once
#include "Arduino.h"

/**
* @resumo   - Tipos de comando implementados na Tomada
* @detalhes - Lista de comandos disponíveis para atuar nas Tomadas
*/
enum _TipoComando {
    COMANDO_LIGAR = 0,
    COMANDO_DESLIGAR = 1,
    COMANDO_INVERTER = 2,
    SEM_COMANDO = 3
};

typedef uint8_t TipoComando;

/**
* @resumo   - Representação do comando das Tomadas (Struct)
* @detalhes - Comandos enviados para controlar cada tomada individualmente
*/
struct ComandoTomadas {
    TipoComando tomada0 = SEM_COMANDO;
    TipoComando tomada1 = SEM_COMANDO;
};

/**
* @resumo   Representação da configração da Tomada (Struct)
* @detalhes A Tomada armazena seu estado e indica quanto de corrente passa nela
*/
struct TomadaConfig {
    bool tomadaLigada = true;
    double valorCorrente = 0; // not yet implemented
};
