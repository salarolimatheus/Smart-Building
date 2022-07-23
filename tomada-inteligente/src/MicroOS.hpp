#ifndef MicroOS_hpp
#define MicroOS_hpp

#include "Arduino.h"
#include "../interface/tarefas.h"

/**
* @resumo   Tipo de Tarefa (Síncrona ou Assíncrona)
* @detalhes Seleção do tipo de tarefa a ser executada no MicroOS
*/
typedef enum {
    TAREFA_SINC = true,
    TAREFA_ASSINC = false
} TipoTarefa;

/**
* @resumo   Eventos para acionamento de tarefas
* @detalhes Ao todo, existem oito eventos que podem ser utilizados em conjunto para a
*           ativação de uma tarefa
*/
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

/**
* @resumo   Representação de uma Tarefa (Struct)
* @detalhes A tarefa possui o tipo de sincronização, o tempo absoluto, o periodo da tarefa
*           (incremento), os eventos da tarefa e a mascara de eventos (utilizada para
*           disparar a tarefa se o valor de events é igual a de eventMask)
*/
struct Tarefa {
    bool ehTarefaSincrona;
    uint32_t periodo;
    uint16_t periodoIncremento;
    uint8_t events;
    uint8_t eventMask;
};

/**
* @resumo   Classe para representar um micro Sistema Operacional
* @detalhes A classe cuida da ativação automática das tarefas de acordo com as
*           configurações realizadas (tipo de sincronização, periodo e evento)
*/
class MicroOS {
private:
    uint32_t tempoAtual;
    Tarefa tarefas[NUMERO_TAREFAS];

public:
    /**
    * @resumo		Inicilização da Classe MicroOS
    */
    MicroOS();

    /**
    * @resumo		Adicionar uma tarefa no micro sistema operacional
    * @detalhes     Esta função permite adicionar tarefas no gerenciamento do OS
    * @param(indiceTarefa)      Indice da Tarefa a ser adicionada, ela reescreve os dados
    * @param(tarefaSincrona)    Informa a sincronização da tarefa, usar enum TipoTarefa
    * @param(periodoIncremento) Valor em milisegundos do período da Tarefa
    * @param(eventMask)		    Padrão de eventos para acionar a Tarefa
    * @param(events)            Valor inicial dos eventos da Tarefa
    * @return       Valor booleano, verdadeiro se a tarefa foi adicionada, falso se o
    *               indice está fora dos limites informados.
    */
    bool addTarefa(uint8_t indiceTarefa, bool tarefaSincrona, uint16_t periodoIncremento, uint8_t eventMask);
    bool addTarefa(uint8_t indiceTarefa, bool tarefaSincrona, uint16_t periodoIncremento, uint8_t eventMask, uint8_t events);

    /**
    * @resumo		Inicia o gerenciamento das Tarefas
    * @detalhes		A função calcula os tempos e períodos de cada Tarefa para execução
    */
    void iniciar();

    /**
    * @brief		Verifica se a Tarefa está pronta para ser acionada
    * @resumo		Essa função verifica se as condições de tempo e/ou de eventos da
    *               Tarefa foram atingidas para a execução da mesma
    * @param(indiceTarefa)      Indice da Tarefa a ser verificada
    * @return		Valor booleano, verdadeiro se a Tarefa está apta a ser executada, caso
    *               contrário, a função retorna falso.
    */
    bool verificar(uint8_t indiceTarefa);

    /**
    * @brief		Ativa um Evento de uma Tarefa
    * @details		A função ativa um evento selecionado de uma Tarefa escolhida
    * @param(indiceTarefa)      Indice da Tarefa a ser utilizada
    * @param(evento)            Valor binário do tipo Evento representando os eventos
    */
    void setEvent(uint8_t indiceTarefa, Evento evento);

    /**
    * @brief		Desativa um Evento de uma Tarefa
    * @details		A função desativa um evento selecionado de uma Tarefa escolhida
    * @param(indiceTarefa)      Indice da Tarefa a ser utilizada
    * @param(evento)            Valor binário do tipo Evento representando os eventos
    */
    void clearEvent(uint8_t indiceTarefa, Evento evento);

    /**
    * @brief		Desativa todos os Evento de uma Tarefa
    * @details		A função desativa todos os Eventos de uma Tarefa escolhida
    * @param(indiceTarefa)      Indice da Tarefa a ser utilizada
    */
    void clearAllEvents(uint8_t indiceTarefa);
};

#endif
