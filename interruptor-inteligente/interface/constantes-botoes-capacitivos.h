#ifndef CONSTANTES_BOTOES_CAPACITIVOS_H
#define CONSTANTES_BOTOES_CAPACITIVOS_H

/**
* @resumo   Limiar do valor da capacitância do sensor a ser considerado como um toque
*/
#define LIMIAR_TOUCH            30

/**
* @resumo   Constantes de tempos em milisegundos e microsegundos de valores importantes
*           na lógica dos tipos de cliques (minimo, limite, transicao, etc)
*/
#define TEMPO_MINIMO_MS         40
#define TEMPO_LIMITE_MS         400
#define TEMPO_TRANSICAO_MS      200

#define TEMPO_MINIMO_US         40000
#define TEMPO_LIMITE_US         400000
#define TEMPO_TRANSICAO_US      200000

#define TEMPO_ENTRE_LEITURAS_US 800

#endif
