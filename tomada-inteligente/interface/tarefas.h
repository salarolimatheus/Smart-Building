#ifndef TAREFAS_H
#define TAREFAS_H

/**
* @resumo   Definição dos indices das tarefas na aplicação do Interruptor
*/
typedef enum {
    TAREFA_TOMADA_0 = 0,
    TAREFA_TOMADA_1 = 1,
    TAREFA_MQTT_REC_MSG_RECONECT = 2,
    NUMERO_TAREFAS
} nomeTarefas;

/**
* @resumo   Mascaras dos eventos das Tarefas
*/
#define MASK_TAREFA_TOMADA_0                0b00000001
#define MASK_TAREFA_TOMADA_1                0b00000001
#define MASK_TAREFA_MQTT_REC_MSG_RECONECT   0b00000000

#endif
