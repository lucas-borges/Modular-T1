/***************************************************************************
*  $MCI Módulo de implementação: GRF Grafo não orientado
*
*  Arquivo gerado:              GRAFO.c
*  Letras identificadoras:      grf
*
*  Projeto: INF 1301 Automatização dos testes de módulos C
*  Gestor:  DI/PUC-Rio
*  Autores: cs  -  Clara Szwarcman
*			gs  -  Guilherme Simas
*			lb  -  Lucas Borges
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*	  1		 csgslb 03/set/2014 início desenvolvimento
*
*
***************************************************************************/

#include   <stdio.h>
#include   <string.h>
#include   <memory.h>
#include   <malloc.h>

#include "LISTA.H"


/***********************************************************************
*
*  $TC Tipo de dados: GRF Vértice
*
*
***********************************************************************/

   typedef struct tagVertice {

         int id ;
               /* Ponteiro para o valor contido no elemento */

         int visitado;
               /* Ponteiro para o elemento predecessor */

         LIS_tppLista arestas ;
               /* Ponteiro para o elemento sucessor */

   } tpVertice ;

   /***********************************************************************
*
*  $TC Tipo de dados: GRF Descritor da cabeça de grafo
*
*
***********************************************************************/

   typedef struct GRF_tagGrafo {

         LIS_tppLista vertices;

		 LIS_tppLista origens;

   } GRF_tpGrafo ;