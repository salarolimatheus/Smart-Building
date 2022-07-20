#include "Arduino.h"                                //Biblioteca padrão do Arduino
#include "../Pacotes.hpp"                           //Sistema de gerenciamento de Pacotes
#include "../Debug.hpp"                             //Biblioteca para Testes

/**
* @resumo		Representação dos estados de um Botão Touch
* @detalhes		Os estados são representados no nivel lógico alto e baixo,
*               além das transições de subida e descida (borda crescente e descendende)
*/
enum Estado {
    ON,
    // RELEASE,
    OFF,
    // PUSH,
};

/**
* @resumo		Gestão do Botão Touch0
* @detalhes     Esta função permite identificar e extrair dados das ações realizados
*               com os toques no sensor Touch
* @param(TouchStatus*)      Representação dos estados do Touch (Struct)
* @return       Valor booleano, verdadeiro se existe alguma ação nova relacionada com o
*               Touch e falso caso contrário.
*/
bool GestaoBotaoTouch0 (TouchStatus* touch);

/**
* @resumo		Gestão do Botão Touch2
* @detalhes     Esta função permite identificar e extrair dados das ações realizados
*               com os toques no sensor Touch
* @param(TouchStatus*)      Representação dos estados do Touch (Struct)
* @return       Valor booleano, verdadeiro se existe alguma ação nova relacionada com o
*               Touch e falso caso contrário.
*/
bool GestaoBotaoTouch2 (TouchStatus* touch);
