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

		 void ( * ExcluirValor ) ( void * pvalor ) ;
			   /* Ponteiro para a função de destruição do valor contido em um vertice */

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

		 void ( * ExcluirValor ) ( void * pvalor ) ;
			   /* Ponteiro para a função de destruição do valor contido em um vertice */

   } GRF_tpGrafo ;

   /***** Protótipos das funções encapuladas no módulo *****/

   int BuscarVertice ( void * pValor, LIS_tppLista pLista , int ( * ComparaValor ) ( void * pValorA , void * pValorB ) );

   void DestruirVertice ( void * pVertice );

   int EncontraCaminho ( tpVertice * atual , tpVertice * destino );

   /*****  Código das funções exportadas pelo módulo  *****/

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

	   LIS_CriarLista ( &( ( * ppGrafo ) -> origens ) , NULL ) ;
	   LIS_CriarLista ( &( ( * ppGrafo ) -> vertices ) , DestruirVertice ) ; //ao destruir a lista de vértices tem que destruir o vértice
	   (*ppGrafo)->ExcluirValor=ExcluirValor;
	   (*ppGrafo)->ComparaValor=ComparaValor ;

	   return GRF_CondRetOK;

   }   /* Fim função: GRF  &Criar Grafo */


/***************************************************************************
*
*  Função: GRF  &Criar Vertice
*****/
   
 GRF_tpCondRet GRF_CriaVertice ( GRF_tppGrafo pGrafo , void * pValor ) 
 {

	   int Ret;
	   tpVertice* vertice;

	   if(pGrafo==NULL)
	   {
		   return GRF_CondRetGrafoNaoExiste;
	   } /* if */

	   if(BuscarVertice ( pValor , pGrafo->vertices , pGrafo->ComparaValor ) == 1 ) //Checa se o vertice já existe
	   {
			return GRF_CondRetVerticeJaExiste ;
	   } /* if */


	   vertice = (tpVertice * ) malloc ( sizeof (tpVertice) );//cria vertice
	   if ( vertice == NULL )
	   {
		   return GRF_CondRetFaltouMemoria;
	   } /* if */

	   
	   vertice->pValor = pValor;
	   vertice->ExcluirValor=pGrafo->ExcluirValor;
	   LIS_CriarLista ( &vertice->arestas , NULL ); //NULL pois a lista vai apontar para outros vértices e não queremos que 
													//ao remover uma aresta os vértices que elas apontam sejam removidos também

	   if( vertice->arestas == NULL )
	   {
		   return GRF_CondRetFaltouMemoria;
	   } /* if */

	   Ret = LIS_InserirElementoApos ( pGrafo->vertices , vertice );
	   if( Ret != LIS_CondRetOK )
	   {
		   return GRF_CondRetErroInserirVertice;
	   } /* if */


	   return GRF_CondRetOK;

   }  /* Fim função: GRF  &Criar Vertice */


/***************************************************************************
*
*  Função: GRF &Cria Aresta
*****/

   GRF_tpCondRet GRF_CriaAresta(void * pValorA, void * pValorB, GRF_tpGrafo * pGrafo)
   {

	   LIS_tpCondRet lis_ret;
	   int vertice_ret;
	   tpVertice * verticeA, * verticeB;
	   void * temp;

	   if(pGrafo==NULL)
	   {
		   return GRF_CondRetGrafoNaoExiste;
	   } /* if */

	   /*Verifica se os vertices existem*/

	   vertice_ret=BuscarVertice(pValorA , pGrafo->vertices , pGrafo->ComparaValor );

	   if(vertice_ret==0)  //vertice nao existe
	   {
		   return GRF_CondRetVerticeNaoExiste; 
	   }/* if */

	   LIS_ObterValor ( pGrafo->vertices, &temp ) ;
	   verticeA = ( tpVertice * ) temp ;

	   vertice_ret=BuscarVertice(pValorB ,pGrafo->vertices , pGrafo->ComparaValor );

	   if(vertice_ret==0)  //vertice nao existe
	   {
		   return GRF_CondRetVerticeNaoExiste; 
	   } /* if */

	   LIS_ObterValor ( pGrafo->vertices, &temp ) ;
	   verticeB = ( tpVertice * ) temp ;

	   /*Verifica se aresta já existe*/

	   vertice_ret=BuscarVertice(pValorB, verticeA->arestas , pGrafo->ComparaValor );

	   if(vertice_ret==1)  //aresta já existe
	   {
		   return GRF_CondRetArestaJaExiste; 
	   } /* if */

	   /*Inserir Aresta de a para b e de b para a*/

	   lis_ret= LIS_InserirElementoApos(verticeA->arestas,verticeB);

	   if(lis_ret!=LIS_CondRetOK)
	   {
		   return GRF_CondRetErroInserirAresta;
	   } /* if */

	   lis_ret= LIS_InserirElementoApos(verticeB->arestas,verticeA);

	   if(lis_ret!=LIS_CondRetOK)
	   {
		   return GRF_CondRetErroInserirAresta; 
	   } /* if */

	   return GRF_CondRetOK;

   } /* Fim função: GRF  &Cria Aresta */


/***************************************************************************
*
*  Função: GRF  &Remove Aresta
*****/
   
   GRF_tpCondRet GRF_RemoveAresta(void * pValorA, void * pValorB, GRF_tpGrafo * pGrafo)
   {

	   int vertice_ret;
	   tpVertice * verticeA, *verticeB, *verticeC;
	   void * temp;
	   
	   if(pGrafo==NULL)
	   {
		   return GRF_CondRetGrafoNaoExiste;
	   } /* if */

	    /*Verifica se os vertices existem*/

	   vertice_ret=BuscarVertice(pValorA, pGrafo->vertices , pGrafo->ComparaValor );

	   if(vertice_ret==0)//vertice nao existe
	   {
		   return GRF_CondRetVerticeNaoExiste; 
	   }/* if */

	   LIS_ObterValor ( pGrafo->vertices, &temp ) ;
	   verticeA = ( tpVertice * ) temp ;

	   vertice_ret=BuscarVertice(pValorB, pGrafo->vertices , pGrafo->ComparaValor );

	   if(vertice_ret==0)//vertice nao existe
	   {
		   return GRF_CondRetVerticeNaoExiste; 
	   } /* if */

	   LIS_ObterValor ( pGrafo->vertices, &temp ) ;
	   verticeB = ( tpVertice * ) temp ;
	   
	   /*Verifica se aresta existe*/

	   vertice_ret=BuscarVertice(pValorB, verticeA->arestas , pGrafo->ComparaValor );

	   if(vertice_ret==0) //aresta nao existe
	   {
		   return GRF_CondRetArestaNaoExiste;
	   } /* if */
	   
	   LIS_ExcluirElemento(verticeA->arestas);
	   
	   vertice_ret=BuscarVertice(pValorA, verticeB->arestas , pGrafo->ComparaValor );
	   
	   LIS_ObterValor ( pGrafo->vertices, &temp ) ;
	   verticeC = ( tpVertice * ) temp ;
	   
	   LIS_ExcluirElemento(verticeB->arestas);
	   
	   return GRF_CondRetOK;

   }  /* Fim função: GRF  &Remove Aresta */

   
/***************************************************************************
*
*  Função: GRF  &Destroi grafo
*****/
   
   void GRF_DestroiGrafo (GRF_tppGrafo pGrafo)
   {

	   if(pGrafo==NULL)
	   {
		   return ;
	   } /* if */

	   LIS_DestruirLista(pGrafo->origens);
	   LIS_DestruirLista(pGrafo->vertices);
	   free(pGrafo);

   } /* Fim função: GRF  &Destroi grafo */
   

/***************************************************************************
*
*  Função: GRF  &Esvaziar Grafo
*****/

   GRF_tpCondRet GRF_EsvaziaGrafo ( GRF_tppGrafo pGrafo )
   {
	   
	   if ( pGrafo == NULL )
	   {
		   return GRF_CondRetGrafoNaoExiste ;
	   } /* if */

	   LIS_EsvaziarLista ( pGrafo->origens ) ;
	   LIS_EsvaziarLista ( pGrafo->vertices ) ;
	   
	   return GRF_CondRetOK ;

   } /* Fim função: GRF  &Existe Vértice */


/***************************************************************************
*
*  Função: GRF  &CriaVerticeOrigem
*****/
   
 GRF_tpCondRet GRF_CriaVerticeOrigem ( GRF_tppGrafo pGrafo , void * pValor ) 
 {

	   int Ret;
	   GRF_tpCondRet ret_grafo;
	   tpVertice* vertice;
	   void * temp;

	   if(pGrafo==NULL)
	   {
		   return GRF_CondRetGrafoNaoExiste;
	   } /* if */

	   if(BuscarVertice ( pValor , pGrafo->origens , pGrafo->ComparaValor ) == 1 ) //Checa se o vértice já é origem
	   {
		   return GRF_CondRetVerticeJaExiste;
	   } /* if */

	   if(BuscarVertice ( pValor , pGrafo->vertices , pGrafo->ComparaValor ) == 0 ) //Checa se o vertice já existe
	   {
		   ret_grafo=GRF_CriaVertice ( pGrafo ,pValor );

		   if(ret_grafo!=GRF_CondRetOK)
		   {
			   return ret_grafo;
		   } /* if */

		   LIS_ObterValor(pGrafo->vertices,&temp);
		   vertice=(tpVertice*)temp;
		 
	   } else {
		   LIS_ObterValor(pGrafo->vertices,&temp);
		   vertice=(tpVertice*)temp;
	   } /* if */

	   Ret=LIS_InserirElementoApos(pGrafo->origens,vertice); 

	   if( Ret != LIS_CondRetOK )
	   {
				return GRF_CondRetErroInserirVertice; 
	   } /* if */

	   return GRF_CondRetOK;

   }  /* Fim função: GRF  &Criar Vertice Origem*/

  
/***************************************************************************
*
*  Função: GRF  &Existe Caminho
*****/

   GRF_tpCondRet GRF_ExisteCaminho ( GRF_tppGrafo pGrafo , void * verticeOrigem , void * verticeDestino )
   {

	   tpVertice * origem , * destino , * aux ;
	   void * temp;
	   
	   if ( pGrafo == NULL )
	   {
		   return GRF_CondRetGrafoNaoExiste ;
	   } /* if */

	   if ( BuscarVertice ( verticeOrigem , pGrafo->vertices , pGrafo->ComparaValor ) == 0 )
	   {
		   return GRF_CondRetVerticeNaoExiste ;
	   } /* if */

	   if ( LIS_ObterValor ( pGrafo->vertices , &temp ) != LIS_CondRetOK )
	   {
		   return GRF_CondRetErroAoObterValor ;
	   } /* if */

	   origem = ( tpVertice * ) temp ;


	   if ( BuscarVertice ( verticeDestino , pGrafo->vertices , pGrafo->ComparaValor ) == 0 )
	   {
		   return GRF_CondRetVerticeNaoExiste ;
	   } /* if */

	   if ( LIS_ObterValor ( pGrafo->vertices , &temp ) != LIS_CondRetOK )
	   {
		   return GRF_CondRetErroAoObterValor ;
	   } /* if */

	   destino = ( tpVertice * ) temp ;

	   if ( LIS_IrInicioLista ( pGrafo->vertices ) != LIS_CondRetOK )
	   {
		   return GRF_CondRetErroAoObterValor ;
	   } /* if */

	    
	   do 
	   {			
			
		    LIS_ObterValor ( pGrafo->vertices , &temp ) ;
			aux = ( tpVertice * ) temp ;
			aux->visitado = 0 ;

	   } while ( LIS_AvancarElementoCorrente ( pGrafo->vertices , 1 ) == LIS_CondRetOK ) ;

	   LIS_IrInicioLista ( origem->arestas ) ;
	   
	   if ( EncontraCaminho ( origem , destino ) == 0 )
	   {
		   return GRF_CondRetVerticesDesconexos ;
	   } /* if */

	   return GRF_CondRetOK;

   }   /* Fim função: GRF  &Existe Caminho */

/***************************************************************************
*
*  Função: GRF  &Existe Vértice
*****/

   GRF_tpCondRet GRF_ExisteVertice ( GRF_tppGrafo pGrafo , void * pValor )
   {

	   if ( pGrafo == NULL )
	   {
		   return GRF_CondRetGrafoNaoExiste;
	   }
	   
	   if (BuscarVertice(pValor, pGrafo->vertices, pGrafo->ComparaValor)==1)
	   {
		   return GRF_CondRetVerticeJaExiste;
	   } /* if */

	   return GRF_CondRetVerticeNaoExiste;

   } /* Fim função: GRF  &Existe Vértice */


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
		tpVertice* ptemp = (tpVertice*) pVertice;

	    LIS_DestruirLista(ptemp->arestas);
		ptemp->ExcluirValor(ptemp->pValor);
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
		LIS_tpCondRet lis_ret;
		LIS_IrInicioLista(pLista);

		do
		{
			lis_ret=LIS_ObterValor ( pLista, &temp ) ;

			if(lis_ret!=LIS_CondRetOK)
			{
				return 0;
			}
			vertice = ( tpVertice * ) temp ;

			if ( ComparaValor ( pValor , vertice->pValor ) == 0 ) 
			{
				return 1;
			} /* if */


		} while ( LIS_AvancarElementoCorrente ( pLista , 1 ) == LIS_CondRetOK ) ;

		return 0 ;

   } /* Fim função: GRF  -Buscar Vértice */

  /***********************************************************************
*
*  $FC Função: GRF  -Encontra Caminho
*
*  $ED Descrição da função
*     
*
***********************************************************************/
  
   int EncontraCaminho ( tpVertice * atual , tpVertice * destino )
   {
	   void * temp ;
	   tpVertice * proximo ;

	     
	   if ( atual->visitado == 1 )
	   {
		   return 0 ;
	   } /* if */
	   
	   atual->visitado = 1 ;


	   if ( atual->pValor == destino->pValor )
	   {
		   return 1;
	   } /* if */

	   if(LIS_IrInicioLista(atual->arestas)!=LIS_CondRetOK)
	   {
		   return 0;
	   } /* if */
	   
	   do
	   {
		   LIS_ObterValor (atual->arestas , &temp );   
		   proximo = ( tpVertice * ) temp ;

		
		   if ( EncontraCaminho ( proximo , destino ) == 1 )
		   {
			   return 1 ;
		   }/* if */

	   } while(LIS_AvancarElementoCorrente ( atual->arestas , 1 )==LIS_CondRetOK);

	   return 0 ;
	  

   } /* Fim função: GRF  -Encontra caminho */



 /********** Fim do módulo de implementação: GRF Grafo não orientado **********/
