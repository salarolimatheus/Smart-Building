#include "src/MicroOS.hpp"                          //Sistema de gerenciamento de tarefas
#include "src/Pacotes.hpp"                          //Sistema de gerenciamento de Pacotes
#include "src/Debug.hpp"                            //Biblioteca para Testes

#include "src/controle/ConexaoWifi.hpp"             //Camada de Controle - Conexao com uma rede Wifi
#include "src/controle/ComunicacaoMQTT.hpp"         //Camada de Controle - Envio/Recebimento de dados via MQTT
#include "src/controle/GestaoBotoesCapacitivos.hpp" //Camada de Controle - Gerencia sistema botoes capacitivos

MicroOS sistema;
TouchStatus touch0, touch2;

void setup() {
    sistema = MicroOS();
    DBG_BEGIN(DEBUG_BAUD_RATE)

    ConfiguraWifi();
    ConfiguraMQTT();
    ConfiguraTouchs(&touch0, &touch2);

    sistema.addTarefa(TAREFA_TOUCH_0, TAREFA_SINC, 10, MASK_TAREFA_TOUCH_0, MASK_TAREFA_TOUCH_0);
    sistema.addTarefa(TAREFA_TOUCH_2, TAREFA_SINC, 10, MASK_TAREFA_TOUCH_2, MASK_TAREFA_TOUCH_2);
    sistema.addTarefa(TAREFA_MQTT_REC_MSG_RECONECT, TAREFA_SINC, 50, MASK_TAREFA_MQTT_REC_MSG_RECONECT);
    sistema.addTarefa(TAREFA_MQTT_ENVIA_TOUCH_0, TAREFA_ASSINC, 0, MASK_TAREFA_MQTT_ENVIA_TOUCH_0);
    sistema.addTarefa(TAREFA_MQTT_ENVIA_TOUCH_2, TAREFA_ASSINC, 0, MASK_TAREFA_MQTT_ENVIA_TOUCH_2);

    sistema.iniciar();
}

void loop() {
    if(sistema.verificar(TAREFA_MQTT_REC_MSG_RECONECT)) {
        processarMensagensRecebidasDoMQTT();
    }

    if(sistema.verificar(TAREFA_TOUCH_0)) {
        bool dadoCompleto = GestaoBotaoTouch0(&touch0);
        if (dadoCompleto == true) {
            sistema.setEvent(TAREFA_MQTT_ENVIA_TOUCH_0, EVENTO_0);
        }
    }

    if(sistema.verificar(TAREFA_MQTT_ENVIA_TOUCH_0)) {
        DBG_TIQUE("TAREFA_MQTT_ENVIA_TOUCH_0")
        EnviaDadosTouch0PorMQTT(&touch0);
        sistema.clearAllEvents(TAREFA_MQTT_ENVIA_TOUCH_0);
        DBG_TAQUE()
    }

    if(sistema.verificar(TAREFA_TOUCH_2)) {
        bool dadoCompleto = GestaoBotaoTouch2(&touch2);
        if (dadoCompleto == true) {
            sistema.setEvent(TAREFA_MQTT_ENVIA_TOUCH_2, EVENTO_0);
        }
    }

    if(sistema.verificar(TAREFA_MQTT_ENVIA_TOUCH_2)) {
        DBG_TIQUE("TAREFA_MQTT_ENVIA_TOUCH_2")
        EnviaDadosTouch2PorMQTT(&touch2);
        sistema.clearAllEvents(TAREFA_MQTT_ENVIA_TOUCH_2);
        DBG_TAQUE()
    }
}
