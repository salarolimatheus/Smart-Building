#include "MicroOS.hpp"
#include "Debug.hpp"

MicroOS::MicroOS() {

}

bool MicroOS::addTarefa(uint8_t indiceTarefa, bool tarefaSincrona, uint16_t periodoIncremento, uint8_t eventMask) {
    if (indiceTarefa > NUMERO_TAREFAS) {
        return false;
    }

    this->tarefas[indiceTarefa].ehTarefaSincrona = tarefaSincrona;
    this->tarefas[indiceTarefa].periodoIncremento = periodoIncremento;
    this->tarefas[indiceTarefa].events = 0x00;
    this->tarefas[indiceTarefa].eventMask = eventMask;
    return true;
}

bool MicroOS::addTarefa(uint8_t indiceTarefa, bool tarefaSincrona, uint16_t periodoIncremento, uint8_t eventMask, uint8_t events) {
    if (indiceTarefa > NUMERO_TAREFAS) {
        return false;
    }

    this->tarefas[indiceTarefa].ehTarefaSincrona = tarefaSincrona;
    this->tarefas[indiceTarefa].periodoIncremento = periodoIncremento;
    this->tarefas[indiceTarefa].events = events;
    this->tarefas[indiceTarefa].eventMask = eventMask;
    return true;
}


void MicroOS::iniciar() {
    this->tempoAtual = millis();

    for (uint8_t index = 0; index < NUMERO_TAREFAS; index++) {
        this->tarefas[index].periodo = this->tempoAtual + this->tarefas[index].periodoIncremento;
    }
}
bool MicroOS::verificar(uint8_t indiceTarefa) {
    if (indiceTarefa > NUMERO_TAREFAS) {
        return false;
    }

    if (this->tarefas[indiceTarefa].events != this->tarefas[indiceTarefa].eventMask) {
        return false;
    }

    if (this->tarefas[indiceTarefa].ehTarefaSincrona) {
        this->tempoAtual = millis();
        if (this->tempoAtual < this->tarefas[indiceTarefa].periodo) {
            return false;
        }
        this->tarefas[indiceTarefa].periodo += this->tarefas[indiceTarefa].periodoIncremento;
    }
    return true;
}

void MicroOS::setEvent(uint8_t indiceTarefa, Evento evento) {
    if (this->tarefas[indiceTarefa].eventMask == 0x00) {
        return;
    }

    this->tarefas[indiceTarefa].events |= evento;
}

void MicroOS::clearEvent(uint8_t indiceTarefa, Evento evento) {
    if (this->tarefas[indiceTarefa].eventMask == 0x00) {
        return;
    }
    this->tarefas[indiceTarefa].events &= ~evento;
}

void MicroOS::clearAllEvents(uint8_t indiceTarefa) {
    this->tarefas[indiceTarefa].events = 0x00;
}
