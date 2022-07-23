#include "Arduino.h"                                //Biblioteca padrão do Arduino
#include "../Pacotes.hpp"                           //Sistema de gerenciamento de Pacotes
#include "../Debug.hpp"                             //Biblioteca para Testes

#include "../hardware/PubSubClient/PubSubClient.h"  //Camada de Hardware - Utilização do MQTT
#include "../hardware/Wifi/WifiClient.h"            //Camada de Hardware - Utilização do Wifi

/**
* @resumo		Configuração do MQTT
* @detalhes		Inicialização do MQTT a partir das configurações
*               em chaves/Mqtt-keys.h
*/
void ConfiguraMQTT();

/**
* @resumo		Recebimento de mensagens e atualizações de informações
* @detalhes     Esta função permite o recebimento de mensagens dos tópicos subscritos
*               em interface/topicos-mqtt.h e a atualização das configurações dos
*               sensores Touch do Interruptor.
* @param(ComandoTomadas*)      Representação da configração da Tomada (Struct)
*/
void processarMensagensRecebidasDoMQTT(ComandoTomadas* comandoTomadas);

/**
* @resumo		Conexão à um broker MQTT
* @detalhes     Esta função permite a conexão com um broker MQTT e a subscrição dos
*               tópicos definidos em interface/topicos-mqtt.h
*/
void conectarAoBrokerMQTT();

/**
* @resumo		Função Interna - não utilizar
* @detalhes     Esta função tem como objetivo subscrever aos tópico definidos
*/
void subscricaoAosTopicosMQTT();
/**
* @resumo		Função Interna - não utilizar
* @detalhes     Esta função é uma função callback para o recebimento de mensagens MQTT
*/
void callback(char* topic, byte* message, unsigned int length);
