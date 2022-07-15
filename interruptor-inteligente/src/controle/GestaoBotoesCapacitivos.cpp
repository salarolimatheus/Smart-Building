#include "GestaoBotoesCapacitivos.hpp"

#include "../../interface/constantes-botoes-capacitivos.h"

void ConfiguraTouchs(TouchStatus* touch0, TouchStatus* touch2){
    touch0->clique = SEM_CLIQUE;
    touch2->clique = SEM_CLIQUE;
}

bool GestaoBotaoTouch0 (TouchStatus* touch) {
    static Estado estadoTouch = OFF;
    static long tempoNoPUSH = millis();
    static long tempoNoRELEASE = millis();

    static long tempoClique = 0;
    static long tempoEsperaTouch = TEMPO_TRANSICAO_MS;

    uint32_t valorTouch = 0;
    for (uint8_t i = 0; i < 4; i++) {
        valorTouch = valorTouch + touchRead(T0);
        delayMicroseconds(TEMPO_ENTRE_LEITURAS_US);
    }
    valorTouch = (valorTouch>>2);

    switch (estadoTouch) {
        case OFF:
            if(touch->clique == CLIQUE_SIMPLES_WAIT) {
                tempoEsperaTouch = millis() - tempoNoRELEASE;
                if (tempoEsperaTouch > TEMPO_TRANSICAO_MS) {
                    touch->clique = CLIQUE_SIMPLES;
                    return true;
                }
            }

            if(valorTouch < LIMIAR_TOUCH) {
                estadoTouch = ON;
                tempoNoPUSH = millis();
                touch->valorCapacitancia = valorTouch;
                tempoEsperaTouch = tempoNoPUSH - tempoNoRELEASE;

                if (tempoEsperaTouch >= TEMPO_TRANSICAO_MS) {
                    touch->clique = CLIQUE_SIMPLES;
                } else {
                    touch->clique = CLIQUE_DUPLO;
                }
            }
            break;
        case ON:
            if(valorTouch >= LIMIAR_TOUCH) {
                estadoTouch = OFF;

                tempoNoRELEASE = millis();
                tempoClique = tempoNoRELEASE - tempoNoPUSH;

                if (touch->clique == CLIQUE_DUPLO) {
                    touch->tempoCliqueDois = tempoClique;
                    touch->tempoTransicao = tempoEsperaTouch;
                    return true;
                } else {
                    if (tempoClique >= TEMPO_LIMITE_MS) {
                        touch->tempoCliqueUm = tempoClique;
                        touch->clique = CLIQUE_LONGO;
                        return true;
                    } else if (tempoClique > TEMPO_MINIMO_MS) {
                        touch->tempoCliqueUm = tempoClique;
                        touch->clique = CLIQUE_SIMPLES_WAIT;
                    }
                }
            }
            break;
    }
    return false;
}

bool GestaoBotaoTouch2 (TouchStatus* touch) {
    static Estado estadoTouch = OFF;
    static long tempoNoPUSH = millis();
    static long tempoNoRELEASE = millis();

    static long tempoClique = 0;
    static long tempoEsperaTouch = TEMPO_TRANSICAO_MS;

    uint32_t valorTouch = 0;
    for (uint8_t i = 0; i < 4; i++) {
        valorTouch = valorTouch + touchRead(T2);
        delayMicroseconds(TEMPO_ENTRE_LEITURAS_US);
    }
    valorTouch = (valorTouch>>2);

    switch (estadoTouch) {
        case OFF:
            if(touch->clique == CLIQUE_SIMPLES_WAIT) {
                tempoEsperaTouch = millis() - tempoNoRELEASE;
                if (tempoEsperaTouch > TEMPO_TRANSICAO_MS) {
                    touch->clique = CLIQUE_SIMPLES;
                    return true;
                }
            }

            if(valorTouch < LIMIAR_TOUCH) {
                estadoTouch = ON;
                tempoNoPUSH = millis();
                touch->valorCapacitancia = valorTouch;
                tempoEsperaTouch = tempoNoPUSH - tempoNoRELEASE;

                if (tempoEsperaTouch >= TEMPO_TRANSICAO_MS) {
                    touch->clique = CLIQUE_SIMPLES;
                } else {
                    touch->clique = CLIQUE_DUPLO;
                }
            }
            break;
        case ON:
            if(valorTouch >= LIMIAR_TOUCH) {
                estadoTouch = OFF;

                tempoNoRELEASE = millis();
                tempoClique = tempoNoRELEASE - tempoNoPUSH;

                if (touch->clique == CLIQUE_DUPLO) {
                    touch->tempoCliqueDois = tempoClique;
                    touch->tempoTransicao = tempoEsperaTouch;
                    return true;
                } else {
                    if (tempoClique >= TEMPO_LIMITE_MS) {
                        touch->tempoCliqueUm = tempoClique;
                        touch->clique = CLIQUE_LONGO;
                        return true;
                    } else if (tempoClique > TEMPO_MINIMO_MS) {
                        touch->tempoCliqueUm = tempoClique;
                        touch->clique = CLIQUE_SIMPLES_WAIT;
                    }
                }
            }
            break;
    }
    return false;
}
