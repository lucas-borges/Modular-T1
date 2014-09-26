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

		 int ( * ComparaValor ) ( void * pValorA , void * pValorB ) ;
			   /* Ponteiro para funçao que compara duas chaves, retornando 0 se iguais e 1 se diferentes */

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

   GRF_tpCondRet GRF_CriaAresta(void * pValorA, void * pValorB, GRF_tpGrafo * pGrafo)
   {
	   LIS_tpCondRet lis_ret;
	   int vertice_ret;
	   tpVertice * verticeA, * verticeB;
	   void * temp;

	   /*Verifica se os vertices existem*/

	   vertice_ret=BuscarVertice(pValorA , pGrafo->vertices , pGrafo->ComparaValor );

	   if(vertice_ret==0)//vertice nao existe
	   {
		   return GRF_VerticeNaoExiste; 
	   }/*if*/

	   LIS_ObterValor ( pGrafo->vertices, &temp ) ;
	   verticeA = ( tpVertice * ) temp ;

	   vertice_ret=BuscarVertice(pValorB ,pGrafo->vertices , pGrafo->ComparaValor );

	   if(vertice_ret==0)//vertice nao existe
	   {
		   return GRF_VerticeNaoExiste; 
	   }/*if*/

	   LIS_ObterValor ( pGrafo->vertices, &temp ) ;
	   verticeB = ( tpVertice * ) temp ;

	   /*Verifica se aresta já existe*/

	   vertice_ret=BuscarVertice(pValorB, verticeA->arestas , pGrafo->ComparaValor );

	   if(vertice_ret==1)//aresta já existe
	   {
		   return GRF_ArestaJaExiste; 
	   }/*if*/

	   /*Inserir Aresta de a para b e de b para a*/

	   
	   lis_ret= LIS_InserirElementoApos(verticeA->arestas,verticeB);

	   if(lis_ret!=LIS_CondRetOK)
	   {
		   return;//erro
	   }/*if*/

	   lis_ret= LIS_InserirElementoApos(verticeB->arestas,verticeA);

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
   
   GRF_tpCondRet GRF_RemoveAresta(void * pValorA, void * pValorB, GRF_tpGrafo * pGrafo)
   {
	   int vertice_ret;
	   tpVertice * verticeA, *verticeB;

	    /*Verifica se os vertices existem*/

	   vertice_ret=BuscarVertice(pValorA, pGrafo->vertices , pGrafo->ComparaValor );

	   if(vertice_ret==0)//vertice nao existe
	   {
		   return GRF_VerticeNaoExiste; 
	   }/*if*/

	   LIS_ObterValor ( pGrafo->vertices, &temp ) ;
	   verticeA = ( tpVertice * ) temp ;

	   vertice_ret=BuscarVertice(pValorB, pGrafo->vertices , pGrafo->ComparaValor );

	   if(vertice_ret==0)//vertice nao existe
	   {
		   return GRF_VerticeNaoExiste; 
	   }/*if*/

	   LIS_ObterValor ( pGrafo->vertices, &temp ) ;
	   verticeB = ( tpVertice * ) temp ;

	   /*Verifica se aresta já existe*/

	   vertice_ret=BuscarVertice(pValorB, verticeA->arestas , pGrafo->ComparaValor );

	   if(vertice_ret==0)//aresta nao existe
	   {
		   return GRF_ArestaNaoExiste;
	   }/*if*/

	   LIS_ExcluirElemento(verticeA->arestas);

	   BuscarVertice(pValorA, verticeB->arestas , pGrafo->ComparaValor );

	   LIS_ExcluirElemento(verticeB->arestas);

	   return GRF_CondRetOK;
   }

   /* Fim função: GRF  &RemoveAresta *

/***************************************************************************
*
*  Função: GRF  &Criar grafo
*****/

   GRF_tpCondRet GRF_CriarGrafo ( GRF_tppGrafo * ppGrafo , int ( * ComparaValor ) ( void * pValorA , void * pValorB ) , void ( * ExcluirValor ) ( void * pValor ) )
   {

	   *ppGrafo= ( GRF_tpGrafo * ) malloc ( sizeof ( GRF_tpGrafo )) ;
	   if ( *ppGrafo == NULL )
	   {
		   return GRF_CondRetFaltouMemoria;
	   } /* if */

	   LIS_CriarLista ( &( ( * ppGrafo ) -> origens ) , ExcluirValor ) ;
	   LIS_CriarLista ( &( ( * ppGrafo ) -> vertices ) , ExcluirValor ) ;
	   (*ppGrafo)->ComparaValor=ComparaValor ;

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

	   if(BuscarVertice ( pValor , Grafo->vertices , pGrafo->ComparaValor ) == 1 )//Checa se o vertice já existe
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

   int BuscarVertice ( void * pValor, LIS_tppLista pLista , int ( * ComparaValor ) ( void * pValorA , void * pValorB ) )
   {

	    void * temp;
		tpVertice * vertice;
		LIS_IrInicioLista(pLista);

		do
		{
			LIS_ObterValor ( pLista, &temp ) ;
			vertice = ( tpVertice * ) temp ;

			if ( ComparaValor ( pValor , vertice->pValor ) == 0 ) 
			{
				return 1;
			} /* if */

		} while ( LIS_AvancarElementoCorrente ( pLista , 1 ) == LIS_CondRetOK ) ;

		return 0 ;

   } /* Fim função: GRF  -Buscar Vértice */

  



 /********** Fim do módulo de implementação: GRF Grafo não orientado **********/
