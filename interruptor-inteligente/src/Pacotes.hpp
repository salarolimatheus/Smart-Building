#pragma once
#include "Arduino.h"

enum _TipoClique {
    CLIQUE_SIMPLES_WAIT = 0,
    CLIQUE_SIMPLES = 1,
    CLIQUE_DUPLO = 2,
    CLIQUE_LONGO = 3,
    SEM_CLIQUE
};

typedef uint8_t TipoClique;

struct TouchStatus {
    long tempoCliqueUm;
    long tempoCliqueDois;
    long tempoTransicao;
    uint8_t valorCapacitancia;
    TipoClique clique;
};
#define TAMANHO_TOUCHSTATUS 14
