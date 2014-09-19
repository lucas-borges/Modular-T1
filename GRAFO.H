/***************************************************************************
*
*  $MCD Módulo de definição: GRF Grafo não orientado
*
*  Arquivo gerado:              GRAFO.h
*  Letras identificadoras:      GRF
*
*  Projeto: INF 1301 Automatização dos testes de módulos C
*  Gestor:  DI/PUC-Rio
*  Autores: cs  -  Clara Szwarcman
*			gs  -  Guilherme Simas
*			lb  -  Lucas Borges
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*     1      csgslb 16/abr/2003 início desenvolvimento
*
*  $ED Descrição do módulo
*     Implementa grafos não orientados utilizando listas 
*	  genéricas duplamente encadeadas.
*     Podem existir n listas em operação simultaneamente.
*     O grafo possui uma cabeça encapsulando o seu estado.
*
*
*
*************************************************************************/


/***** Declarações exportadas pelo módulo *****/

/* Tipo referência para uma lista */

typedef struct GRF_tagGrafo * GRF_tppGrafo ;


/***********************************************************************
*
*  $TC Tipo de dados: GRF Condições de retorno
*
*
*  $ED Descrição do tipo
*     Condições de retorno das funções da lista
*
***********************************************************************/

   typedef enum {

         GRF_CondRetOK ,
               /* Concluiu corretamente */

         LIS_CondRetListaVazia ,
               /* A lista não contém elementos */

         LIS_CondRetFimLista ,
               /* Foi atingido o fim de lista */

         LIS_CondRetListaNaoExiste ,
               /* A lista não existe */

         LIS_CondRetFaltouMemoria ,
               /* Faltou memória ao tentar criar um elemento de lista */
		 
   } GRF_tpCondRet ;


/***********************************************************************
*
*  $FC Função: GRF  &Nome função
*
*  $ED Descrição da função
*    
*
*  $EP Parâmetros
*     
*
*  $FV Valor retornado
*     
*
***********************************************************************/




   
/********** Fim do módulo de definição: GRF Grafo não orientado **********/