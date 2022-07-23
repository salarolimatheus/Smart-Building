#include "Arduino.h"                                //Biblioteca padrão do Arduino
#include "../Pacotes.hpp"                           //Sistema de gerenciamento de Pacotes
#include "../Debug.hpp"                             //Biblioteca para Testes

/**
* @resumo		Configuração de Entradas e Saídas
* @detalhes		Inicialização dos I/O do do Microcontrolador
*/
void ConfiguraGPIOs();

/**
* @resumo		Contorole da Tomada 0
* @detalhes     Esta função permite receber comandos e atualizar o estada da tomada
* @param(TomadaConfig*)     Tomada a ter o estado modificado
* @param(TipoComando*)      Comando para modificar a Tomada
* @return       Valor booleano, verdadeiro se algum comando foi recebido e se o status
*               foi atualizado com sucesso, falso caso contrário.
*/
bool ControleDaTomada0(TomadaConfig* tomada, TipoComando* comando);

/**
* @resumo		Contorole da Tomada 1
* @detalhes     Esta função permite receber comandos e atualizar o estada da tomada
* @param(TomadaConfig*)     Tomada a ter o estado modificado
* @param(TipoComando*)      Comando para modificar a Tomada
* @return       Valor booleano, verdadeiro se algum comando foi recebido e se o status
*               foi atualizado com sucesso, falso caso contrário.
*/
bool ControleDaTomada1(TomadaConfig* tomada, TipoComando* comando);
