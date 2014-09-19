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
#include "GRAFO.H"


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

   /***** Protótipos das funções encapuladas no módulo *****/

   /*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*
*  Função: GRF &CriaAresta
*****/

   GRF_tpCondRet GRF_CriaAresta(tpVertice* vert_a, tpVertice * vert_b, GRF_tpGrafo * pGrafo)
   {
	   LIS_tpCondRet lis_ret;
	   int vertice_ret;

	   /*Verifica se os vertices existem*/

	   vertice_ret=BuscarVertice(vert_a->id,pGrafo->vertices);

	   if(vertice_ret==0)//vertice nao existe
	   {
		   return GRF_VerticeNaoExiste; 
	   }/*if*/

	   vertice_ret=BuscarVertice(vert_b->id,pGrafo->vertices);

	   if(vertice_ret==0)//vertice nao existe
	   {
		   return GRF_VerticeNaoExiste; 
	   }/*if*/

	   /*Verifica se aresta já existe*/

	   vertice_ret=BuscarVertice(vert_b->id,vert_a->arestas);

	   if(vertice_ret==1)//aresta já existe
	   {
		   return GRF_ArestaJaExiste; 
	   }/*if*/

	   /*Inserir Aresta de a para b e de b para a*/

	   lis_ret= LIS_InserirElementoApos(vert_a->arestas,vert_b);

	   if(lis_ret!=LIS_CondRetOK)
	   {
		   return;//erro
	   }/*if*/

	   lis_ret= LIS_InserirElementoApos(vert_b->arestas,vert_a);

	   if(lis_ret!=LIS_CondRetOK)
	   {
		   return;//erro
	   }/*if*/

	   return GRF_CondRetOK;
   }


   /* Fim função: GRF  &Nome da função *
   
/***************************************************************************
*
*  Função: GRF  &Nome da função
*****/

   GRF_tpCondRet GRF_CriarGrafo ( GRF_tppGrafo * ppGrafo)
   {

	   *ppGrafo= ( GRF_tpGrafo * ) malloc ( sizeof ( GRF_tpGrafo )) ;
	   if ( *ppGrafo == NULL )
	   {
		   return GRF_CondRetFaltouMemoria;
	   } /* if */

	   LIS_CriarLista ( &((*ppGrafo)->origens) , DestruirVertice);
	   LIS_CriarLista ( &((*ppGrafo)->vertices) , DestruirVertice);

	   return GRF_CondRetOK;

   }   /* Fim função: GRF  &Nome da função *
   
   
   
   
   
/*****  Código das funções encapsuladas no módulo  *****/

/***********************************************************************
*
*  $FC Função: GRF  -Nome da função
*
*  $ED Descrição da função
*     
*
***********************************************************************/
  
   void DestruirVertice ( void * pVertice )
   {

	   free(pVertice);

   } /* Fim função: GRF  -Nome da função */

/***********************************************************************
*
*  $FC Função: GRF  -Nome da função
*
*  $ED Descrição da função
*     
*
***********************************************************************/

   int BuscarVertice (int id, LIS_tppLista pLista)
   {

	    void * temp;
		tpVertice * vertice;

		LIS_IrInicioLista(pLista);

		do
		{
			LIS_ObterValor(pLista, &temp);
			vertice=(tpVertice *) temp;

			if (vertice->id == id) 
			{
				return 1;
			} /* if */

		} while (LIS_AvancarElementoCorrente(pLista,1)==LIS_CondRetOK);

		return 0;

   }

  



 /********** Fim do módulo de implementação: GRF Grafo não orientado **********/
