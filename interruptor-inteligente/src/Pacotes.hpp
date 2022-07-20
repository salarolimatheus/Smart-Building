#pragma once
#include "Arduino.h"

/**
* @resumo   Tipos de cliques implementados no Interruptor
* @detalhes Diferentes cliques podem ser detectados de acordo com a lista oferecida
*/
enum _TipoClique {
    CLIQUE_SIMPLES_WAIT = 0,
    CLIQUE_SIMPLES = 1,
    CLIQUE_DUPLO = 2,
    CLIQUE_LONGO = 3,
    SEM_CLIQUE
};

typedef uint8_t TipoClique;

/**
* @resumo   Representação dos estados do Touch (Struct)
* @detalhes A Touch possui um tempo de clique com um valor de capacitância, dependendo do
*           tipo de clique, o tempo de transição e o tempo do segundo clique são inseridos
*/
struct TouchStatus {
    long tempoCliqueUm;
    long tempoCliqueDois;
    long tempoTransicao;
    uint8_t valorCapacitancia;
    TipoClique clique = SEM_CLIQUE;
};

/**
* @resumo   Representação da configração do Touch (Struct)
* @detalhes A Touch pode ser desabilitade e sua configuração é armazenada na TouchConfig
*/
struct TouchConfig {
    bool touch0Enabled = true;
    bool touch2Enabled = true;
};
