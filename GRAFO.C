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

         void * pValor ;
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

		// void  ( ExcluirValor * ) ( void * pvalor ) ;
			   /* Ponteiro para a função de destruição do valor contido em um vertice */

   } GRF_tpGrafo ;

   /***** Protótipos das funções encapuladas no módulo *****/

   int BuscarVertice (void * pValor , LIS_tppLista pLista);

   void DestruirVertice ( void * pVertice );

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

	   vertice_ret=BuscarVertice(vert_a->pValor,pGrafo->vertices);

	   if(vertice_ret==0)//vertice nao existe
	   {
		   return GRF_VerticeNaoExiste; 
	   }/*if*/

	   vertice_ret=BuscarVertice(vert_b->pValor,pGrafo->vertices);

	   if(vertice_ret==0)//vertice nao existe
	   {
		   return GRF_VerticeNaoExiste; 
	   }/*if*/

	   /*Verifica se aresta já existe*/

	   vertice_ret=BuscarVertice(vert_b->pValor,vert_a->arestas);

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
*  Função: GRF  &RemoveAresta
*****/
   
   GRF_tpCondRet GRF_RemoveAresta(tpVertice* vert_a, tpVertice * vert_b, GRF_tpGrafo * pGrafo)
   {
	   int vertice_ret;

	    /*Verifica se os vertices existem*/

	   vertice_ret=BuscarVertice(vert_a->pValor,pGrafo->vertices);

	   if(vertice_ret==0)//vertice nao existe
	   {
		   return GRF_VerticeNaoExiste; 
	   }/*if*/

	   vertice_ret=BuscarVertice(vert_b->pValor,pGrafo->vertices);

	   if(vertice_ret==0)//vertice nao existe
	   {
		   return GRF_VerticeNaoExiste; 
	   }/*if*/

	   /*Verifica se aresta já existe*/

	   vertice_ret=BuscarVertice(vert_b->pValor,vert_a->arestas);

	   if(vertice_ret==0)//aresta nao existe
	   {
		   return GRF_ArestaNaoExiste;
	   }/*if*/

	   LIS_ExcluirElemento(vert_a->arestas);

	   BuscarVertice(vert_a->pValor,vert_b->arestas);

	   LIS_ExcluirElemento(vert_a->arestas);

	   return GRF_CondRetOK;
   }

   /* Fim função: GRF  &RemoveAresta *

/***************************************************************************
*
*  Função: GRF  &Criar grafo
*****/

   GRF_tpCondRet GRF_CriarGrafo ( GRF_tppGrafo * ppGrafo , void ( ExcluirValor * ) ( void * pValor ) )
   {

	   *ppGrafo= ( GRF_tpGrafo * ) malloc ( sizeof ( GRF_tpGrafo )) ;
	   if ( *ppGrafo == NULL )
	   {
		   return GRF_CondRetFaltouMemoria;
	   } /* if */

	   LIS_CriarLista ( &((*ppGrafo)->origens) , ExcluirValor);
	   LIS_CriarLista ( &((*ppGrafo)->vertices) , ExcluirValor);
	   //( *ppGrafo ) -> ExcluirValor = ExcluirValor ;

	   return GRF_CondRetOK;


   }   /* Fim função: GRF  &Criar Grafo *
   
/***************************************************************************
*
*  Função: GRF  &CriaVertice
*****/
   
 GRF_tpCondRet GRF_CriaVertice ( GRF_tpGrafo * Grafo , void * pValor ) 
   {
	   int Ret;
	   tpVertice* vertice;

	   if(Grafo==NULL)
	   {
		   return GRF_CondRetGrafoNaoExiste;
	   }

	   if(BuscarVertice ( pValor , Grafo->vertices ) == 1 )//Checa se o vertice já existe
	   {
			return GRF_VerticeJaExiste ;
	   }

	   vertice = (tpVertice * ) malloc ( sizeof (tpVertice) );//cria vertice
	   if ( vertice == NULL )
	   {
		   return GRF_CondRetFaltouMemoria;
	   }
	   
	   vertice->pValor = pValor;
	   LIS_CriarLista ( &vertice->arestas , free );//funcao free pois nao existem outras estruturas nessa lista, somente ponteiros
	   
	   if( vertice->arestas == NULL )
	   {
		   return GRF_CondRetFaltouMemoria;
	   }

	   Ret = LIS_InserirElementoApos ( Grafo->vertices , vertice );
	   if( Ret != LIS_CondRetOK )
	   {
		   return GRF_CondRetErro;//nao sei que erro colocar aqui
	   }

	   return GRF_CondRetOK;
   }
   
   /* Fim função: GRF  &Criar Vertice *
   
/***************************************************************************
*
*  Função: GRF  &Destroi grafo
*****/
   
   GRF_tpCondRet GRF_DestroiGrafo (GRF_tppGrafo pGrafo)
   {

	   LIS_DestruirLista(pGrafo->origens);
	   LIS_DestruirLista(pGrafo->vertices);
	   free(pGrafo);

	   return GRF_CondRetOK;

   } /* Fim função: GRF  &Destroi grafo */
   

   
/*****  Código das funções encapsuladas no módulo  *****/

/***********************************************************************
*
*  $FC Função: GRF  -Destruir vértice
*
*  $ED Descrição da função
*     
*
***********************************************************************/
  
   void DestruirVertice ( void * pVertice )
   {

		LIS_DestruirLista(((tpVertice*)pVertice)->arestas);
		free(pVertice);

   } /* Fim função: GRF  -Destruir vértice */

/***********************************************************************
*
*  $FC Função: GRF  -Buscar Vértice
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

		return 0 ;

   } /* Fim função: GRF  -Buscar Vértice */

  



 /********** Fim do módulo de implementação: GRF Grafo não orientado **********/
