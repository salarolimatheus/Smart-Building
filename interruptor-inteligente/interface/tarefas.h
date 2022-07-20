#ifndef TAREFAS_H
#define TAREFAS_H

/**
* @resumo   Definição dos indices das tarefas na aplicação do Interruptor
*/
typedef enum {
    TAREFA_TOUCH_0 = 0,
    TAREFA_TOUCH_2 = 1,
    TAREFA_MQTT_REC_MSG_RECONECT = 2,
    TAREFA_MQTT_ENVIA_TOUCH_0 = 3,
    TAREFA_MQTT_ENVIA_TOUCH_2 = 4,
    NUMERO_TAREFAS
} nomeTarefas;

/**
* @resumo   Mascaras dos eventos das Tarefas
*/
#define MASK_TAREFA_TOUCH_0                 0b00000001
#define MASK_TAREFA_TOUCH_2                 0b00000001
#define MASK_TAREFA_MQTT_REC_MSG_RECONECT   0b00000000
#define MASK_TAREFA_MQTT_ENVIA_TOUCH_0      0b00000001
#define MASK_TAREFA_MQTT_ENVIA_TOUCH_2      0b00000001

#endif
