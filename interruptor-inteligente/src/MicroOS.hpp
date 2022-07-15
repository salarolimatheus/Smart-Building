#ifndef MicroOS_hpp
#define MicroOS_hpp

#include "Arduino.h"
#include "../interface/tarefas.h"

typedef enum {
    TAREFA_SINC = true,
    TAREFA_ASSINC = false
} TipoTarefa;

typedef enum {
    EVENTO_0 = 0b00000001,
    EVENTO_1 = 0b00000010,
    EVENTO_2 = 0b00000100,
    EVENTO_3 = 0b00001000,
    EVENTO_4 = 0b00010000,
    EVENTO_5 = 0b00100000,
    EVENTO_6 = 0b01000000,
    EVENTO_7 = 0b10000000
} Evento;

struct Tarefa {
    bool ehTarefaSincrona;
    uint32_t periodo;
    uint16_t periodoIncremento;
    uint8_t events;
    uint8_t eventMask;
};

class MicroOS {
private:
    uint32_t tempoAtual;
    Tarefa tarefas[NUMERO_TAREFAS];

public:
    MicroOS();

    bool addTarefa(uint8_t indiceTarefa, bool tarefaSincrona, uint16_t periodoIncremento, uint8_t eventMask);
    bool addTarefa(uint8_t indiceTarefa, bool tarefaSincrona, uint16_t periodoIncremento, uint8_t eventMask, uint8_t events);

    void iniciar();
    bool verificar(uint8_t indiceTarefa);

    void setEvent(uint8_t indiceTarefa, Evento evento);
    void clearEvent(uint8_t indiceTarefa, Evento evento);
    void clearAllEvents(uint8_t indiceTarefa);
};

#endif
