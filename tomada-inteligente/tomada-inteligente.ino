#include "src/MicroOS.hpp"                          //Sistema de gerenciamento de tarefas
#include "src/Debug.hpp"                            //Biblioteca para Testes

#include "src/controle/ConexaoWifi.hpp"             //Camada de Controle - Conexao com uma rede Wifi
#include "src/controle/ComunicacaoMQTT.hpp"         //Camada de Controle - Envio/Recebimento de dados via MQTT
#include "src/controle/ControleTomada.hpp"          //Camada de Controle - Controle dos estados da Tomada

MicroOS sistema;

//Initial config
void setup() {
    sistema = MicroOS();
    DBG_BEGIN(DEBUG_BAUD_RATE)

    ConfiguraWifi();
    ConfiguraMQTT();
    ConfiguraGPIOs();

    sistema.addTarefa(TAREFA_MQTT_REC_MSG_RECONECT, TAREFA_SINC, 50, MASK_TAREFA_MQTT_REC_MSG_RECONECT);
    sistema.addTarefa(TAREFA_TOMADA_0, TAREFA_ASSINC, 0, MASK_TAREFA_TOMADA_0);
    sistema.addTarefa(TAREFA_TOMADA_1, TAREFA_ASSINC, 0, MASK_TAREFA_TOMADA_1);
}

void loop() {
    static TomadaConfig tomada0, tomada1;
    static ComandoTomadas comandoTomadas;

    if(sistema.verificar(TAREFA_MQTT_REC_MSG_RECONECT)) {
        processarMensagensRecebidasDoMQTT(&comandoTomadas);
        if (comandoTomadas.tomada0 != SEM_COMANDO) {
            sistema.setEvent(TAREFA_TOMADA_0, EVENTO_0);
        }
        if (comandoTomadas.tomada1 != SEM_COMANDO) {
            sistema.setEvent(TAREFA_TOMADA_1, EVENTO_0);
        }
    }

    if(sistema.verificar(TAREFA_TOMADA_0)) {
        ControleDaTomada0(&tomada0, &comandoTomadas.tomada0);
        sistema.clearAllEvents(TAREFA_TOMADA_0);
    }

    if(sistema.verificar(TAREFA_TOMADA_1)) {
        ControleDaTomada1(&tomada1, &comandoTomadas.tomada1);
        sistema.clearAllEvents(TAREFA_TOMADA_1);
    }
}
