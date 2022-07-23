#include "Arduino.h"                                //Biblioteca padrão do Arduino
#include "../Debug.hpp"                             //Biblioteca para Testes

#include "../hardware/Wifi/Wifi.h"                  //Camada de Hardware - Utilização do Wifi

/**
* @resumo		Configuração do Wifi
* @detalhes		Inicialização do Wifi e conexão à uma rede local a partir das
*               configurações fornecidas em chaves/Wifi-keys.h
*/
void ConfiguraWifi();
